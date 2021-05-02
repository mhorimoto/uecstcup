熱電対センサ UECS NODE
=====================

熱電対8chを接続して温度計測を行い、結果をUECS電文で送信するだけの装置。

- Version: A00
- Release: 02-May-2021
- Develop: HOLLY&Co.,Ltd.

## 必要なH/W

- Arduino UNO R3 互換機上等。ピン位置など物理形状は本家と同じにする
- M302K 自社製シールド基板
- MCP9600 熱電対アンプ × 8pcs
- W5500 NIC
- I2C I/F LCD 1602 (16桁2行)
- AC100/220V to DC5V/1.5A 電源
- プッシュスイッチ
- 電源用トグルスイッチ

## M302K以外の配線

プッシュスイッチにつながる配線をDI2に接続する。

MCP9600はI2Cアドレスを8ch分区別するために仕様書の通りの抵抗を取り付ける。

## ソフトウェアのインストール

### EEPROMの初期値

MACアドレスやUECSID,熱電対タイプやROOM,REGIONなどの位置情報の初期値を設定する。

このプログラムは、lowcore サブディレクトリの配下にある。この lowcore.ino を最初にインストールして初期値を作成する。  
詳細は、 [lowcore/README.md](lowcore/README.md) を参照の事。

また、初期化の内容は、 [EEPROM_MAP.md](EEPROM_MAP.md) に記されている。

### 主プログラムのインストール

主プログラムは、main サブディレクトリの配下に全て含まれている。
それを Arduino IDE などでコンパイルしてCPUにupload(install)する。

## 使い方

使い方は、取扱説明書を [main/MANUAL.md](main/MANUAL.md) に記すので、そちらを参照する。

## 著作権

This software is released under the MIT License, see [LICENSE.txt](LICENSE.txt).  
(このソフトウェアは、MITライセンスのもとで公開されている。[LICENSE-ja.txt](LICENSE-ja.txt)を見よ。)



