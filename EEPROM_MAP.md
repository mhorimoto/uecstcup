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

部屋番号

部屋(棟)を識別するための番号。
0〜127の整数値を取る。0は、全棟向け。

## Thermocouple-N Region

## Thermocouple-N Order

## Thermocouple-N Priority

## Thermocouple-N Interval

## Thermocouple-N Name
