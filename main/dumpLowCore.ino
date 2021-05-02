void dumpLowCore(void) {
  int x,y;
  char dbuf[30],ccname[8];
  const char *temp PROGMEM = "%d:%c,%d,%d,%d,%d,%d,%s";
  Serial.println(F("DUMP"));
  for(y=0x10;y<0xa0;y+=0x10) {
    EEPROM.get(y+8,ccname);
    sprintf(dbuf,temp,(y/0x10),(char)EEPROM[y],(byte)EEPROM[y+1],(byte)EEPROM[y+2],(unsigned int)EEPROM[y+3],
	    (byte)EEPROM[y+5],(unsigned int)EEPROM[y+6],ccname);
    Serial.println(dbuf);
  }
}

