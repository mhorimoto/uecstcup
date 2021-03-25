EEPROM ASSIGNMENT MAP

| ADDR  | Description             | Type    | Example,Remarks |
|-------|-------------------------|---------|-----------------|
| 0x000 | UECSID                  | byte[6] | 10100C000009    |
| 0x006 | MAC_Address             | byte[6] |                 |
| 0x010 | Thermocouple-1 Type     | char    | K,J,T,N,S,E,B,R |
| 0x011 | Thermocouple-1 Room     | byte    | 0-128           |
| 0x012 | Thermocouple-1 Region   | int     | 0-30000         |
| 0x014 | Thermocouple-1 Order    | int     | 0-30000         |
| 0x016 | Thermocouple-1 Priority | byte    | 0-30            |
| 0x017 | Thermocouple-1 Interval | int     | seconds         |
