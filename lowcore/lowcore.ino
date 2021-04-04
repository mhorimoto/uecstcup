///////////////////////////////////////////////////////
// -*- mode : C++ -*-
// EEPROM editor for uecstcup
//
//[概要]
//  uecstcupで使用するEEPROM領域の初期化を行うプログラム
//
///////////////////////////////////////////////////////

#include <stdio.h>
#include <EEPROM.h>

void setup(void) {
  unsigned int i,j,r,a;
  byte t;
  char c,name[8],z[4];
  byte uecsid[6]={0x10,0x10,0x0c,0x00,0x00,0x08},uecsrd[6];
  byte macadd[6]={0x02,0xa2,0x73,0x08,0xff,0xff};
  byte data[16] ={'K',1,1,1,0,15,10,0,'T','C','T','e','m','p',0,0};
  byte cndd[16] ={'c',1,1,1,0,29,1, 0,'c','n','d',0  ,0  ,0  ,0,0};
  Serial.begin(115200);
  Serial.println("EEPROM SETTING");
  EEPROM.get(0x0,uecsrd);
  for(i=0;i<6;i++) {
    if (uecsrd[i]!=uecsid[i]) {
      r = 1;
      break;
    } else {
      r = 0;
      r = 1;
    }
  }
  if (r==0) {
    Serial.println("FINE DID");
    Serial.println("HEXDATA:");
    for(j=0;j<9;j++) {
      sprintf(z,"0x%03X:",j*0x10);
      Serial.print(z);
      for(i=0;i<16;i++) {
	sprintf(z,"%02X",EEPROM.read(i+(j*0x10)));
	Serial.print(z);
	if (i<15) Serial.print(",");
      }
      Serial.println();
    }
    Serial.end();
    while(1) {
      r = 1;
      r = 2;
    }
  }
  EEPROM.put(0x0,uecsid);
  Serial.println("WRITE DONE");
  Serial.print("UECSID:");
  for(i=0;i<6;i++) {
    Serial.print(EEPROM.read(i),HEX);
    Serial.print(",");
  }
  Serial.println("");
  Serial.print("ENTER SERIAL NUMBER:");
  r = 0;
  j = 0;
  while(r!=0x0d) {
    if (Serial.available()>0) {
      r =Serial.read();
      if ((r>=0x30)&&(r<=0x39)) {
	r -= 0x30;
	Serial.print(r,DEC);
	j *= 10;
	j += r;
      }
    }
  }
  Serial.println("");
  Serial.print("DATA:");Serial.println(j,DEC);
  t = (j >> 8) & 0xff;
  macadd[4] = t;
  macadd[5] = (byte)(j & 0xff);
  Serial.print("MAC ADDRESS=");
  for(i=0;i<6;i++) {
    Serial.print(macadd[i],HEX);
    if (i<5) Serial.print(":");
  }
  Serial.println(); 
  EEPROM.put(0x6,macadd);
  Serial.print("MAC=");
  for(i=0;i<6;i++) {
    Serial.print(EEPROM.read(6+i),HEX);
    if (i<5) Serial.print(":");
  }
  Serial.println("");
  for(i=0;i<8;i++) {
    EEPROM.put((i*0x10)+0x10,data);
    a = (i*0x10)+0x10;
    Serial.print("0x");
    Serial.print(a,HEX);
    EEPROM.put(a,data);
    Serial.println("DATA WROTE");
  }
  EEPROM.put(0x90,cndd);
  Serial.println("CND WROTE");
  
  Serial.println("HEXDATA:");
  for(j=0;j<9;j++) {
    for(i=0;i<16;i++) {
      Serial.print(EEPROM.read(i+(j*0x10)),HEX);
      if (i<15) Serial.print(",");
    }
    Serial.println();
  }
  for(i=1;i<10;i++) {
    Serial.print(i,HEX);
    Serial.print(": ");
    Serial.print("TYPE=");
    Serial.write((char)EEPROM[i*0x10]);
    Serial.print(" ROOM=");
    Serial.print((byte)EEPROM[i*0x10+1]);
    Serial.print(" REGION=");
    Serial.print((byte)EEPROM[i*0x10+2]);
    Serial.print(" ORDER=");
    EEPROM.get(i*0x10+3,r);
    Serial.print(r,DEC);
    Serial.print(" PRIORITY=");
    Serial.print((byte)EEPROM[i*0x10+5]);
    Serial.print(" INTERVAL=");
    EEPROM.get(i*0x10+6,r);
    Serial.print(r,DEC);
    Serial.print(" CCMTYPE=");
    EEPROM.get(i*0x10+8,name);
    Serial.println(name);
  }
  Serial.end();
}


void loop(void) {
}
