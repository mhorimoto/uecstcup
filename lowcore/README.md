EEPROM初期化プログラム
=====================

本初期化プログラムが行う初期データは以下の通り。

|    Description             | Initial Value                 |
|----------------------------|-------------------------------|
|    UECSID                  | 0x10,0x10,0x0C,0x00,0x00,0x08 |
|    MAC_Address             | 0x02,0xA2,0x73,0x08,0xXX,0xYY |
|    Thermocouple-N_Type     | 'K'                           |
|    Thermocouple-N_Room     | 1                             |
|    Thermocouple-N_Region   | 1                             |
|    Thermocouple-N_Order    | 1                             |
|    Thermocouple-N_Priority | 15                            |
|    Thermocouple-N_Interval | 10                            |
|    Thermocouple-N_Name     | 'TCTemp',NULL                 |
|    Delimiter               | NULL                          |


N:1〜8まで繰り返す。

このプログラムは、製造時にArduino UNOに1度だけインストールして実行するプログラムである。

起動後、MACアドレスの下2桁のためにシリアル番号を聞いてくるのでそれに答える。
重複の確認は出来ないので、入力時にちゃんと台帳などで確認管理をする必要がある。
