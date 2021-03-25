/////////////////////////////////////////
// -*- mode : C++ -*-
// Lab用8ch熱電対センサノード
//
//[概要]
//  UECS電文で熱電対で観測した温度データを通知する。
//   CCMTYPE: TCTemp.N.xXX  N=1..8
//   UECSID:  10100C000008
//   VENDOR:  HOLLY
//
//[履歴]
//
#include <SPI.h>
#include <Ethernet2.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
