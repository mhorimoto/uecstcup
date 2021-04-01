#include <stdio.h>
#include <SPI.h>
#include <Ethernet2.h>
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


const char *VERSION = "D0004 ";
const signed long ccmver = 0x69010 + 1;
char uecsid[6];

/////////////////////////////////////
// Hardware Define
/////////////////////////////////////
Adafruit_MCP9600 mcp[8];
int mcp96_addr[]={0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67};

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
char lcdtext[16][17];

byte macaddr[6];

float thermocouple[8];

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
const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
char ntpServer[NTPSERVER_NAME_LENGTH];
//char dod[11],tod[9];      // Date of Date,Time of Date
int  ntprc;
EthernetUDP ntp;


void setup(void) {
  extern void init_mcp(void);
  lcd.init();
  lcd.backlight();
  EEPROM.get(0x00,uecsid);
  EEPROM.get(0x06,macaddr);
  sprintf(lcdtext[0],"THCP Ver:%6s",VERSION);
  sprintf(lcdtext[1],"ID:%02X%02X%02X%02X%02X%02X",
	  uecsid[0],uecsid[1],uecsid[2],uecsid[3],uecsid[4],uecsid[5]);
  if (Ethernet.begin(macaddr)==0) {
    sprintf(lcdtext[2],"Ethernet fail");
  } else {
    sprintf(lcdtext[2],"HW:%02X%02X%02X%02X%02X%02X",
	    macaddr[0],macaddr[1],macaddr[2],macaddr[3],macaddr[4],macaddr[5]);
    sprintf(lcdtext[3],"%d.%d.%d.%d",Ethernet.localIP()[0],Ethernet.localIP()[1],
	    Ethernet.localIP()[2],Ethernet.localIP()[3]);
  }
  lcd.setCursor(0,0);
  lcd.print(lcdtext[0]);
  lcd.setCursor(0,1);
  lcd.print(lcdtext[1]);
  init_mcp();
  delay(5600);
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
  int i,ta,tb;
  if (dispEnable==1) {
    dispEnable=0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(lcdtext[dispID]);
    if (dispID==11) {
      dispID = -1;
    }
    lcd.setCursor(0,1);
    lcd.print(lcdtext[dispID+1]);
  } else {
    for(i=0;i<8;i++) {
      thermocouple[i] = mcp[i].readThermocouple();
      ta = (int)thermocouple[i];
      tb = (int)((thermocouple[i]-ta)*100);
      sprintf(lcdtext[4+i],"%d:%d.%02d C",i+1,ta,tb);
    }
  }
}

ISR(TIMER1_COMPA_vect) {
  dispEnable = 1;
  if (dispID>=11) {
    dispID = 0;
  } else {
    dispID++;
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
