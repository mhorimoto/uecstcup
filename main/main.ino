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


const char *VERSION = "D0008 ";
const signed long ccmver = 0x69010 + 6;

char uecsid[6], uecstext[256],strIP[16];
//byte cnd_room,cnd_region,cnd_priority,ccm_room[8],ccm_region[8],ccm_priority[8];
//int  cnd_order,ccm_order[8];

/////////////////////////////////////
// Hardware Define
/////////////////////////////////////
Adafruit_MCP9600 mcp[8];
int mcp96_addr[]={0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67};
float thermocouple[8];

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
char lcdtext[13][17];

byte macaddr[6];
IPAddress localIP,broadcastIP,subnetmaskIP,remoteIP;
EthernetUDP Udp16520,Udp16529;
EthernetUDP ntp;

volatile int dispID = 0;
volatile int dispEnable = 0;
volatile int period1sec = 0;
volatile int period10sec = 0;
volatile int period60sec = 0;

/////////
// NTP
/////////
#define NTPSERVER_NAME_LENGTH 32
#define NTPSERVER_NAME  0xfe0
#define NTPLOCAL_PORT   8123
//const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
//byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
//char ntpServer[NTPSERVER_NAME_LENGTH];
//char dod[11],tod[9];      // Date of Date,Time of Date
//int  ntprc;


void setup(void) {
  int i;
  extern void init_mcp(void);
  lcd.init();
  lcd.backlight();
  EEPROM.get(0x00,uecsid);
  EEPROM.get(0x06,macaddr);
  sprintf(lcdtext[0],"THCP Ver:%6s",VERSION);
  sprintf(lcdtext[1],"ID:%02X%02X%02X%02X%02X%02X",
	  uecsid[0],uecsid[1],uecsid[2],uecsid[3],uecsid[4],uecsid[5]);
  Ethernet.init(10);
  if (Ethernet.begin(macaddr)==0) {
    sprintf(lcdtext[2],"NFL");
  } else {
    localIP = Ethernet.localIP();
    subnetmaskIP = Ethernet.subnetMask();
    for(i=0;i<4;i++) {
      broadcastIP[i] = ~subnetmaskIP[i]|localIP[i];
    }
    sprintf(lcdtext[2],"HW:%02X%02X%02X%02X%02X%02X",
	    macaddr[0],macaddr[1],macaddr[2],macaddr[3],macaddr[4],macaddr[5]);
    sprintf(strIP,"%d.%d.%d.%d",localIP[0],localIP[1],localIP[2],localIP[3]);
    sprintf(lcdtext[3],"%s",strIP);
    sprintf(lcdtext[4],"%d.%d.%d.%d",broadcastIP[0],broadcastIP[1],broadcastIP[2],broadcastIP[3]);
    Udp16520.begin(16520);
    Udp16529.begin(16529);
  }
  lcd.setCursor(0,0);
  lcd.print(lcdtext[0]);
  lcd.setCursor(0,1);
  lcd.print(lcdtext[1]);
  init_mcp();
  delay(3000);
  //
  // Setup Timer1 Interrupt
  //
  TCCR1A  = 0;
  TCCR1B  = 0;
  TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);  //CTCmode //prescaler to 1024
  OCR1A   = 15625-1;
  TIMSK1 |= (1 << OCIE1A);

}

void loop() {
  int i,ia,ta,tb;
  byte room,region,priority;
  int  order,interval;
  char name[7];

  // 10 sec interval
  if (period10sec==1) {
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
      sprintf(uecstext,"<?xml version=\"1.0\"?><UECS ver=\"1.00-E10\"><DATA type=\"%s.%d.mIC\" room=\"%d\" region=\"%d\" order=\"%d\" priority=\"%d\">%d.%02d</DATA><IP>%s</IP></UECS>",name,i,room,region,order,priority,ta,tb,strIP);
      Udp16520.beginPacket(broadcastIP,16520);
    //    Udp16520.write(lcdtext[dispID+1]);
      Udp16520.write(uecstext);
      Udp16520.endPacket();
    //    Serial.begin(115200);
    //    Serial.println("10sec");
    //    Serial.end();
    }
  }
  // 1 min interval
  if (period60sec==1) {
    period60sec = 0;
    //    Serial.begin(115200);
    //    Serial.println("60sec");
    //    Serial.end();
  }
  // 1 sec interval
  if (dispEnable==1) {
    dispEnable=0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(lcdtext[dispID]);
    if (dispID==12) {
      dispID = -1;
    }
    lcd.setCursor(0,1);
    lcd.print(lcdtext[dispID+1]);
    sprintf(uecstext,"<?xml version=\"1.0\"?><UECS ver=\"1.00-E10\"><DATA type=\"cnd.mIC\" room=\"%d\" region=\"%d\" order=\"%d\" priority=\"29\">0</DATA><IP>%s</IP></UECS>",1,1,1,strIP);
    Udp16520.beginPacket(broadcastIP,16520);
    //    Udp16520.write(lcdtext[dispID+1]);
    Udp16520.write(uecstext);
    Udp16520.endPacket();
  } else {
    for(i=0;i<8;i++) {
      thermocouple[i] = mcp[i].readThermocouple();
      ta = (int)thermocouple[i];
      tb = (int)((thermocouple[i]-ta)*100);
      sprintf(lcdtext[5+i],"%d:%d.%02d",i+1,ta,tb);
    }
  }
}

ISR(TIMER1_COMPA_vect) {
  static byte cnt10,cnt60;
  dispEnable = 1;
  if (dispID >= 12) {
    dispID = 0;
  } else {
    dispID++;
  }
  cnt10++;
  cnt60++;
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
