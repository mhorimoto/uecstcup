int setParam(char *pbuf) {
  char ttype,ptype,*bufptr;
  byte index,room, region, priority;
  unsigned int k,order;
  extern Adafruit_MCP9600 mcp[];
  extern void dumpLowCore(void);
  
  // Command character 's' skip
  bufptr = strtok(pbuf," ,");
  // Get and calculate Index
  bufptr = strtok(NULL," ,");
  index = (byte)(String(bufptr).toInt());
  if ((index<1)||(index>9)) return(-1);
  index *= 0x10;
  // Thermocouple Type
  bufptr = strtok(NULL," ,");    // T-Type
  if (index==0x90) {
    ttype = 'c';
  } else {
    ttype = *bufptr;
    bitClear(ttype,5);             // Upper convert
    switch(ttype) {
    case 'K':
    case 'J':
    case 'T':
    case 'N':
    case 'S':
    case 'E':
    case 'B':
    case 'R':
      break;
    default:
      return(-1);
    }
  }
  bufptr = strtok(NULL," ,");    // Room
  k = String(bufptr).toInt();
  if ((k<0)||(k>127)) return(-1);
  room = (byte)k;

  bufptr = strtok(NULL," ,");    // Region
  k = String(bufptr).toInt();
  if ((k<0)||(k>127)) return(-1);
  region = (byte)k;

  bufptr = strtok(NULL," ,");    // Order
  k = String(bufptr).toInt();
  if ((k<0)||(k>30000)) return(-1);
  order = k;

  bufptr = strtok(NULL," ,");    // Priority
  k = String(bufptr).toInt();
  if ((k<0)||(k>30)) return(-1);
  priority = (byte)k;

  //
  // Write to EEPROM
  //
  if (index<0x90) { // For Thermalcouple sensor only.
    ptype = EEPROM[index];
    k = (index/0x10)-1;
    if (ptype!=ttype) {
      switch(ttype) {
      case 'K':
	mcp[k].setThermocoupleType(MCP9600_TYPE_K);
	break;
      case 'J':
	mcp[k].setThermocoupleType(MCP9600_TYPE_J);
	break;
      case 'T':
	mcp[k].setThermocoupleType(MCP9600_TYPE_T);
	break;
      case 'N':
	mcp[k].setThermocoupleType(MCP9600_TYPE_N);
	break;
      case 'S':
	mcp[k].setThermocoupleType(MCP9600_TYPE_S);
	break;
      case 'E':
	mcp[k].setThermocoupleType(MCP9600_TYPE_E);
	break;
      case 'B':
	mcp[k].setThermocoupleType(MCP9600_TYPE_B);
	break;
      case 'R':
	mcp[k].setThermocoupleType(MCP9600_TYPE_R);
	break;
      }
      ptype = 1;  // need MCP9600 reset
    } else {
      ptype = 0;
    }
    EEPROM.update(index,ttype);  // Thermocouple Type
  }
  EEPROM.update(index+1,room);
  EEPROM.update(index+2,region);
  EEPROM.update(index+5,priority);
  EEPROM.get(index+3,k); // Order needs "read and write operation".
  if ( k != order ) {
    EEPROM.put(index+3,order);
  }
  Serial.print(F("WRITE AND "));
  dumpLowCore();
  return(0);
}
