EEPROM ASSIGNMENT MAP
=====================


| ADDR  | Description             | Type    | Example,Remarks |
|-------|-------------------------|---------|-----------------|
| 0x000 | UECSID                  | byte[6] | 10100C000008    |
| 0x006 | MAC_Address             | byte[6] | 02A27308xxyy    |
| 0x010 | Thermocouple-1 Type     | char    | K,J,T,N,S,E,B,R |
| 0x011 | Thermocouple-1 Room     | byte    | 0-127           |
| 0x012 | Thermocouple-1 Region   | byte    | 0-127           |
| 0x013 | Thermocouple-1 Order    | int     | 0-30000         |
| 0x015 | Thermocouple-1 Priority | byte    | 0-30            |
| 0x016 | Thermocouple-1 Interval | int     | seconds         |
| 0x018 | Thermocouple-1 Name     | char[7] | 7characters     |
| 0x01f | Delimiter               | byte    | NULL            |
| 0x020 | Thermocouple-2 Type     | char    | K,J,T,N,S,E,B,R |
| 0x021 | Thermocouple-2 Room     | byte    | 0-127           |
| 0x022 | Thermocouple-2 Region   | byte    | 0-127           |
| 0x023 | Thermocouple-2 Order    | int     | 0-30000         |
| 0x025 | Thermocouple-2 Priority | byte    | 0-30            |
| 0x026 | Thermocouple-2 Interval | int     | seconds         |
| 0x028 | Thermocouple-2 Name     | char[7] | 7characters     |
| 0x02f | Delimiter               | byte    | NULL            |
|   :   |         :               |   :     |                 |
| 0x0N0 | Thermocouple-N Type     | char    | K,J,T,N,S,E,B,R |
| 0x0N1 | Thermocouple-N Room     | byte    | 0-127           |
| 0x0N2 | Thermocouple-N Region   | byte    | 0-127           |
| 0x0N3 | Thermocouple-N Order    | int     | 0-30000         |
| 0x0N5 | Thermocouple-N Priority | byte    | 0-30            |
| 0x0N6 | Thermocouple-N Interval | int     | seconds         |
| 0x0N8 | Thermocouple-N Name     | char[7] | 7characters     |
| 0x0Nf | Delimiter               | byte    | NULL            |
|   :   |         :               |   :     |                 |
| 0x080 | Thermocouple-8 Type     | char    | K,J,T,N,S,E,B,R |
| 0x081 | Thermocouple-8 Room     | byte    | 0-127           |
| 0x082 | Thermocouple-8 Region   | byte    | 0-127           |
| 0x083 | Thermocouple-8 Order    | int     | 0-30000         |
| 0x085 | Thermocouple-8 Priority | byte    | 0-30            |
| 0x086 | Thermocouple-8 Interval | int     | seconds         |
| 0x088 | Thermocouple-8 Name     | char[7] | 7characters     |
| 0x08f | Delimiter               | byte    | NULL            |
|   :   |         :               |   :     |                 |
| 0x090 | cnd Type (dummy)        | char    | c               |
| 0x091 | cnd Room                | byte    | 0-127           |
| 0x092 | cnd Region              | byte    | 0-127           |
| 0x093 | cnd Order               | int     | 0-30000         |
| 0x095 | cnd Priority            | byte    | 29 (0-30)       |
| 0x096 | cnd Interval            | int     | 1 seconds       |
| 0x098 | cnd Name                | char[7] | cnd             |
| 0x09f | Delimiter               | byte    | NULL            |


## UECSID

6????????????????????????

    0x10,0x10,0x0C,0x00,0x00,0x08


## MAC Address

?????????MAC??????????????????locally administered?????????????????????????????????????????????

    02:A2:73:08:xx:xx (xx:?????????????????????)
    0x02,0xa2,0x73,0x08,0xXX,0xXX


## Thermocouple-N Type

?????????????????????

 - K???
 - J???
 - T???
 - N???
 - S???
 - E???
 - B???
 - R???
 
?????????????????????????????????????????????1????????????????????????


## Thermocouple-N Room

????????????

??????(???)?????????????????????????????????
0???127????????????????????????0?????????????????????

## Thermocouple-N Region

????????????

????????????????????????????????????????????????
0???127????????????????????????0????????????????????????

## Thermocouple-N Order

????????????

??????????????????????????????????????????  
0???30000????????????????????????0??????????????????????????????????????????

## Thermocouple-N Priority

????????????

???????????????????????????????????????????????????????????????????????????  
0???30????????????????????????

## Thermocouple-N Interval

?????????????????????????????????

A-1S-0,A-10S-0,A-1M-0??????????????????????????????????????????

## Thermocouple-N Name

CCM??????????????????

????????????????????????????????????????????????  
?????????UECS???????????????19???????????????????????????????????????7????????????????????????  
???????????????

     TCTemp

????????????7???????????????????????????????????????NULL(0)???????????????  
??????????????????TCTemp?????????????????????????????????????????????????????????????????????????????????

     TCTemp.1.mXX
     TCTemp.2.mXX
     TCTemp.:.mXX
     TCTemp.7.mXX
     TCTemp.8.mXX

# ?????????????????????????????????

??????EEPROM????????????????????????????????????????????????lowcore?????????????????????????????????????????????
???????????????MAC???????????????xxyy?????????????????????????????????????????????????????????
