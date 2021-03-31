///////////////////////////////////////////////////////
// -*- mode : C++ -*-
// EEPROM initilizer for uecstcup
//
//[概要]
//  EEPROM領域の出荷時初期化を行うプログラム
//
///////////////////////////////////////////////////////

#include <stdio.h>
#include <EEPROM.h>

void setup(void) {
  unsigned int i,j,r;
  byte data[16] ={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

  Serial.begin(115200);
  Serial.println("EEPROM INITIALIZE");
  for(i=0;i<9;i++) {
    EEPROM.put(i*0x10,data);
  }
  Serial.println("DONE");
  Serial.end();
}


void loop(void) {
}
