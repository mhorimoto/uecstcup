EEPROM ASSIGNMENT MAP
=====================


| ADDR  | Description             | Type    | Example,Remarks |
|-------|-------------------------|---------|-----------------|
| 0x000 | UECSID                  | byte[6] | 10100C000008    |
| 0x006 | MAC_Address             | byte[6] | 02A27308xxyy    |
| 0x010 | Thermocouple-1 Type     | char    | K,J,T,N,S,E,B,R |
| 0x011 | Thermocouple-1 Room     | byte    | 0-128           |
| 0x012 | Thermocouple-1 Region   | int     | 0-30000         |
| 0x014 | Thermocouple-1 Order    | int     | 0-30000         |
| 0x016 | Thermocouple-1 Priority | byte    | 0-30            |
| 0x017 | Thermocouple-1 Interval | int     | seconds         |
| 0x019 | Thermocouple-1 Name     | char[6] | 6characters     |
| 0x01f | Delimiter               | byte    | NULL            |
| 0x020 | Thermocouple-2 Type     | char    | K,J,T,N,S,E,B,R |
| 0x021 | Thermocouple-2 Room     | byte    | 0-128           |
| 0x022 | Thermocouple-2 Region   | int     | 0-30000         |
| 0x024 | Thermocouple-2 Order    | int     | 0-30000         |
| 0x026 | Thermocouple-2 Priority | byte    | 0-30            |
| 0x027 | Thermocouple-2 Interval | int     | seconds         |
| 0x029 | Thermocouple-2 Name     | char[6] | 6characters     |
| 0x02f | Delimiter               | byte    | NULL            |
| 0x030 | Thermocouple-3 Type     | char    | K,J,T,N,S,E,B,R |
| 0x031 | Thermocouple-3 Room     | byte    | 0-128           |
| 0x032 | Thermocouple-3 Region   | int     | 0-30000         |
| 0x034 | Thermocouple-3 Order    | int     | 0-30000         |
| 0x036 | Thermocouple-3 Priority | byte    | 0-30            |
| 0x037 | Thermocouple-3 Interval | int     | seconds         |
| 0x039 | Thermocouple-2 Name     | char[6] | 6characters     |
| 0x03f | Delimiter               | byte    | NULL            |
| 0x040 | Thermocouple-4 Type     | char    | K,J,T,N,S,E,B,R |
| 0x041 | Thermocouple-4 Room     | byte    | 0-128           |
| 0x042 | Thermocouple-4 Region   | int     | 0-30000         |
| 0x044 | Thermocouple-4 Order    | int     | 0-30000         |
| 0x046 | Thermocouple-4 Priority | byte    | 0-30            |
| 0x047 | Thermocouple-4 Interval | int     | seconds         |
| 0x049 | Thermocouple-2 Name     | char[6] | 6characters     |
| 0x04f | Delimiter               | byte    | NULL            |
| 0x050 | Thermocouple-5 Type     | char    | K,J,T,N,S,E,B,R |
| 0x051 | Thermocouple-5 Room     | byte    | 0-128           |
| 0x052 | Thermocouple-5 Region   | int     | 0-30000         |
| 0x054 | Thermocouple-5 Order    | int     | 0-30000         |
| 0x056 | Thermocouple-5 Priority | byte    | 0-30            |
| 0x057 | Thermocouple-5 Interval | int     | seconds         |
| 0x059 | Thermocouple-2 Name     | char[6] | 6characters     |
| 0x05f | Delimiter               | byte    | NULL            |
| 0x060 | Thermocouple-6 Type     | char    | K,J,T,N,S,E,B,R |
| 0x061 | Thermocouple-6 Room     | byte    | 0-128           |
| 0x062 | Thermocouple-6 Region   | int     | 0-30000         |
| 0x064 | Thermocouple-6 Order    | int     | 0-30000         |
| 0x066 | Thermocouple-6 Priority | byte    | 0-30            |
| 0x067 | Thermocouple-6 Interval | int     | seconds         |
| 0x069 | Thermocouple-2 Name     | char[6] | 6characters     |
| 0x06f | Delimiter               | byte    | NULL            |
| 0x070 | Thermocouple-7 Type     | char    | K,J,T,N,S,E,B,R |
| 0x071 | Thermocouple-7 Room     | byte    | 0-128           |
| 0x072 | Thermocouple-7 Region   | int     | 0-30000         |
| 0x074 | Thermocouple-7 Order    | int     | 0-30000         |
| 0x076 | Thermocouple-7 Priority | byte    | 0-30            |
| 0x077 | Thermocouple-7 Interval | int     | seconds         |
| 0x079 | Thermocouple-2 Name     | char[6] | 6characters     |
| 0x07f | Delimiter               | byte    | NULL            |
| 0x080 | Thermocouple-8 Type     | char    | K,J,T,N,S,E,B,R |
| 0x081 | Thermocouple-8 Room     | byte    | 0-128           |
| 0x082 | Thermocouple-8 Region   | int     | 0-30000         |
| 0x084 | Thermocouple-8 Order    | int     | 0-30000         |
| 0x086 | Thermocouple-8 Priority | byte    | 0-30            |
| 0x087 | Thermocouple-8 Interval | int     | seconds         |
| 0x089 | Thermocouple-2 Name     | char[6] | 6characters     |
| 0x08f | Delimiter               | byte    | NULL            |


## UECSID

6バイト固定値で、

    0x10,0x10,0x0C,0x00,0x00,0x08


## MAC Address

当社のMACアドレスは、locally administeredで構成される。本機の場合には、

    02:A2:73:08:xx:xx (xx:ユニークな連番)
    0x02,0xa2,0x73,0x08,0xXX,0xXX


## Thermocouple-N Type

熱電対のタイプ
 - K型
 - J型
 - T型
 - N型
 - S型
 - E型
 - B型
 - R型
これらをどれかをアルファベット1文字で指定する。


## Thermocouple-N Room

## Thermocouple-N Region

## Thermocouple-N Order

## Thermocouple-N Priority

## Thermocouple-N Interval

## Thermocouple-N Name
