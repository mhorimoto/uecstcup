#include <stdio.h>
#include <SPI.h>
#include <Ethernet2.h>
#include <EthernetUdp2.h> // UDP library from: bjoern@cs.stanford.edu 12/30/2008
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include "Adafruit_MCP9600.h"

uint8_t mcusr_mirror __attribute__ ((section (".noinit")));
void get_mcusr(void)	 \
  __attribute__((naked)) \
  __attribute__((section(".init3")));
void get_mcusr(void) {
  mcusr_mirror = MCUSR;
  MCUSR = 0;
  wdt_disable();
}


const char VERSION[16] PROGMEM = "THCP Ver:A00P0";

char uecsid[6], uecstext[180],strIP[16],linebuf[65];
byte lineptr = 0;

/////////////////////////////////////
// Hardware Define
/////////////////////////////////////
Adafruit_MCP9600 mcp[8];
int mcp96_addr[]={0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67};
float thermocouple[8];

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
char lcdtext[4][17];

byte macaddr[6];
IPAddress localIP,broadcastIP,subnetmaskIP,remoteIP;
EthernetUDP Udp16520; //,Udp16529;

volatile int period1sec = 0;
volatile int period10sec = 0;
volatile int period60sec = 0;

void setup(void) {
  int i;
  const char *ids PROGMEM = "%s:%02X%02X%02X%02X%02X%02X";
  extern void init_mcp(void);
  extern void lcdout(int,int,int);
  
  lcd.init();
  lcd.backlight();
  configure_wdt();
  pinMode(2,INPUT_PULLUP);
  EEPROM.get(0x00,uecsid);
  EEPROM.get(0x06,macaddr);
  for(i=0;i<16;i++) {
    lcdtext[0][i] = pgm_read_byte(&(VERSION[i]));
  }
  lcdtext[0][i] = 0;
  sprintf(lcdtext[1],ids,"ID",
	  uecsid[0],uecsid[1],uecsid[2],uecsid[3],uecsid[4],uecsid[5]);
  lcdout(0,1,1);
  Serial.begin(115200);
  Serial.println(lcdtext[0]);
  delay(1500);
  Ethernet.init(10);
  if (Ethernet.begin(macaddr)==0) {
    sprintf(lcdtext[1],"NFL");
  } else {
    localIP = Ethernet.localIP();
    subnetmaskIP = Ethernet.subnetMask();
    for(i=0;i<4;i++) {
      broadcastIP[i] = ~subnetmaskIP[i]|localIP[i];
    }
    sprintf(lcdtext[2],ids,"HW",
	    macaddr[0],macaddr[1],macaddr[2],macaddr[3],macaddr[4],macaddr[5]);
    sprintf(strIP,"%d.%d.%d.%d",localIP[0],localIP[1],localIP[2],localIP[3]);
    sprintf(lcdtext[3],"%s",strIP);
    sprintf(lcdtext[0],"%d.%d.%d.%d",broadcastIP[0],broadcastIP[1],broadcastIP[2],broadcastIP[3]);
    lcdout(2,3,1);
    Udp16520.begin(16520);
  }
  wdt_reset();
  delay(1000);
  init_mcp();
  delay(2000);
  //
  // Setup Timer1 Interrupt
  //
  TCCR1A  = 0;
  TCCR1B  = 0;
  TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);  //CTCmode //prescaler to 1024
  OCR1A   = 15625-1;
  TIMSK1 |= (1 << OCIE1A);
  //
  // Opening Messages
  //
  Serial.println(lcdtext[1]);
  Serial.println(lcdtext[2]);
  Serial.println(lcdtext[3]);
  Serial.println(lcdtext[0]);
}

/////////////////////////////////
// Reset Function goto Address 0
/////////////////////////////////
void(*resetFunc)(void) = 0;

/////////////////////////////////
//
void loop() {
  int i,ia,ta,tb;
  byte room,region,priority;
  int  order,interval;
  int  inchar ;
  static byte s = 0;
  char name[7],dname[10],val[6];
  extern void lcdout(int,int,int);
  extern int setParam(char *);
  extern void dumpLowCore(void);
  
  const char *xmlDT PROGMEM = "<?xml version=\"1.0\"?><UECS ver=\"1.00-E10\"><DATA type=\"%s.mIC\" room=\"%d\" region=\"%d\" order=\"%d\" priority=\"%d\">%s</DATA><IP>%s</IP></UECS>";
  const char *thdisp PROGMEM = "%3d %3d %3d %3d";
  const char *ids PROGMEM = "%s:%02X%02X%02X%02X%02X%02X";


  wdt_reset();
  //////////////////////////////////////////////////////////////
  // Green Button Operations
  //////////////////////////////////////////////////////////////
  if ( digitalRead(2) == LOW ) {
    if ( s == 0 ) {
      s = 1;
      for(i=0;i<16;i++) {
	lcdtext[0][i] = pgm_read_byte(&(VERSION[i]));
      }
      lcdtext[0][i] = 0;
      sprintf(lcdtext[1],ids,"ID",
	      uecsid[0],uecsid[1],uecsid[2],uecsid[3],uecsid[4],uecsid[5]);
    } else {
      s = 0;
      sprintf(lcdtext[0],ids,"HW",
	      macaddr[0],macaddr[1],macaddr[2],macaddr[3],macaddr[4],macaddr[5]);
      sprintf(strIP,"%d.%d.%d.%d",localIP[0],localIP[1],localIP[2],localIP[3]);
      sprintf(lcdtext[1],"%s",strIP);
    }
    lcdout(0,1,1);
    delay(150);
  }
  //////////////////////////////////////////////////////////////
  if ( Serial.available() > 0 ) {
    inchar = Serial.read();
    if (( inchar == 0x13 )||( inchar == 0x0a)||( lineptr > 63)) {
      if ( !strcmp(linebuf,"d") ) {
	dumpLowCore();
      } else if ( !strncmp(linebuf,"s ",2 )) {
	if ( setParam(linebuf) != 0 ) {
	  Serial.println(F("BAD"));
	} else {
	  Serial.println(F("OK"));
	}
      } else if ( !strcmp(linebuf,"reset" )) {
	resetFunc();
      } else {
	Serial.print(linebuf);
	Serial.println(F(" ?"));
      }
      lineptr = 0;
    } else {
      linebuf[lineptr] = (char)inchar;
      lineptr++;
    }
    linebuf[lineptr] = (char)NULL;
  }
  // 10 sec interval
  if (period10sec==1) {
    wdt_reset();
    period10sec = 0;
    for(i=1;i<9;i++) {
      ia = i*0x10;
      EEPROM.get(ia+0x01,room);
      EEPROM.get(ia+0x02,region);
      EEPROM.get(ia+0x03,order);
      EEPROM.get(ia+0x05,priority);
      EEPROM.get(ia+0x06,interval);
      EEPROM.get(ia+0x08,name);
      ta = (int)thermocouple[(i-1)];
      tb = (int)((thermocouple[(i-1)]-ta)*100);
      lcdout(0,1,0);
      sprintf(dname,"%s.%d",name,i);
      sprintf(val,"%d.%02d",ta,tb);
      sprintf(uecstext,xmlDT,dname,room,region,order,priority,val,strIP);
      // <?xml version="1.0"?><UECS ver="1.00-E10"><DATA type="TCTemp.2.mIC" room="1" region="1" order="1" priority="15">25.87</DATA><IP>192.168.38.126</IP></UECS>

      Udp16520.beginPacket(broadcastIP,16520);
      Udp16520.write(uecstext);
      Udp16520.endPacket();
    }
  }
  // 1 min interval
  if (period60sec==1) {
    wdt_reset();
    period60sec = 0;
  }
  // 1 sec interval
  if (period1sec==1) {
    period1sec = 0;
    EEPROM.get(0x91,room);
    EEPROM.get(0x92,region);
    EEPROM.get(0x93,order);
    EEPROM.get(0x95,priority);
    sprintf(uecstext,xmlDT,"cnd",room,region,order,priority,"0",strIP);
    Udp16520.beginPacket(broadcastIP,16520);
    Udp16520.write(uecstext);
    Udp16520.endPacket();
    for(i=0;i<8;i++) {
      thermocouple[i] = mcp[i].readThermocouple();
    }
    sprintf(lcdtext[0],thdisp,
	    (int)thermocouple[0],(int)thermocouple[1],(int)thermocouple[2],(int)thermocouple[3]);
    sprintf(lcdtext[1],thdisp,
	    (int)thermocouple[4],(int)thermocouple[5],(int)thermocouple[6],(int)thermocouple[7]);
  }
  wdt_reset();
}

ISR(TIMER1_COMPA_vect) {
  static byte cnt10,cnt60;
  cnt10++;
  cnt60++;
  period1sec = 1;
  if (cnt10 >= 10) {
    cnt10 = 0;
    period10sec = 1;
  }
  if (cnt60 >= 60) {
    cnt60 = 0;
    period60sec = 1;
  }
}


void configure_wdt(void) {
  cli();                           // disable interrupts for changing the registers
  MCUSR = 0;                       // reset status register flags
                                   // Put timer in interrupt-only mode:
  WDTCSR |= 0b00011000;            // Set WDCE (5th from left) and WDE (4th from left) to enter config mode,
                                   // using bitwise OR assignment (leaves other bits unchanged).
  WDTCSR =  0b00001000 | 0b100001; // clr WDIE: interrupt enabled
                                   // set WDE: reset disabled
                                   // and set delay interval (right side of bar) to 8 seconds
  sei();                           // re-enable interrupts
                                   // reminder of the definitions for the time before firing
                                   // delay interval patterns:
                                   //  16 ms:     0b000000
                                   //  500 ms:    0b000101
                                   //  1 second:  0b000110
                                   //  2 seconds: 0b000111
                                   //  4 seconds: 0b100000
                                   //  8 seconds: 0b100001
}

