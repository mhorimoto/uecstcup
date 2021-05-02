void init_mcp(void) {
  int i;
  extern Adafruit_MCP9600 mcp[8];
  lcd.clear();
  lcd.print(F("MCP9600 INIT"));
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("1 2 3 4 5 6 7 8"));
  /* Initialise the driver with I2C_ADDRESS and the default I2C bus. */
  for(i=0;i<8;i++) {
    lcd.setCursor((i*2),1);
    if (! mcp[i].begin(0x60+i)) {
      lcd.print(F("X"));
    } else {
      mcp[i].setADCresolution(MCP9600_ADCRESOLUTION_18);
      switch(EEPROM.read((i+1)*0x10)) {
      case 'K':
	mcp[i].setThermocoupleType(MCP9600_TYPE_K);
	break;
      case 'J':
	mcp[i].setThermocoupleType(MCP9600_TYPE_J);
	break;
      case 'T':
	mcp[i].setThermocoupleType(MCP9600_TYPE_T);
	break;
      case 'N':
	mcp[i].setThermocoupleType(MCP9600_TYPE_N);
	break;
      case 'S':
	mcp[i].setThermocoupleType(MCP9600_TYPE_S);
	break;
      case 'E':
	mcp[i].setThermocoupleType(MCP9600_TYPE_E);
	break;
      case 'B':
	mcp[i].setThermocoupleType(MCP9600_TYPE_B);
	break;
      case 'R':
	mcp[i].setThermocoupleType(MCP9600_TYPE_R);
	break;
      }
      switch (mcp[i].getThermocoupleType()) {
      case MCP9600_TYPE_K:  lcd.print(F("K")); break;
      case MCP9600_TYPE_J:  lcd.print(F("J")); break;
      case MCP9600_TYPE_T:  lcd.print(F("T")); break;
      case MCP9600_TYPE_N:  lcd.print(F("N")); break;
      case MCP9600_TYPE_S:  lcd.print(F("S")); break;
      case MCP9600_TYPE_E:  lcd.print(F("E")); break;
      case MCP9600_TYPE_B:  lcd.print(F("B")); break;
      case MCP9600_TYPE_R:  lcd.print(F("R")); break;
      }
      mcp[i].setFilterCoefficient(3);
    }
  }
}
