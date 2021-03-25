#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include "Adafruit_MCP9600.h"

Adafruit_MCP9600 mcp[8];

void setup()
{
  int i;
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  Serial.println("MCP9600 HW test");

  /* Initialise the driver with I2C_ADDRESS and the default I2C bus. */
  for(i=0;i<8;i++) {
    Serial.print("No.");
    Serial.print(i,DEC);
    if (! mcp[i].begin(0x60+i)) {
      Serial.println(" Sensor not found. Check wiring!");
    } else {
      mcp[i].setADCresolution(MCP9600_ADCRESOLUTION_18);
      Serial.println("Found MCP9600!");
      Serial.print("ADC resolution set to ");
      switch (mcp[i].getADCresolution()) {
      case MCP9600_ADCRESOLUTION_18:   Serial.print("18"); break;
      case MCP9600_ADCRESOLUTION_16:   Serial.print("16"); break;
      case MCP9600_ADCRESOLUTION_14:   Serial.print("14"); break;
      case MCP9600_ADCRESOLUTION_12:   Serial.print("12"); break;
      }
      Serial.println(" bits");
      mcp[i].setThermocoupleType(MCP9600_TYPE_K);
      Serial.print("Thermocouple type set to ");
      switch (mcp[i].getThermocoupleType()) {
      case MCP9600_TYPE_K:  Serial.print("K"); break;
      case MCP9600_TYPE_J:  Serial.print("J"); break;
      case MCP9600_TYPE_T:  Serial.print("T"); break;
      case MCP9600_TYPE_N:  Serial.print("N"); break;
      case MCP9600_TYPE_S:  Serial.print("S"); break;
      case MCP9600_TYPE_E:  Serial.print("E"); break;
      case MCP9600_TYPE_B:  Serial.print("B"); break;
      case MCP9600_TYPE_R:  Serial.print("R"); break;
      }
      Serial.println(" type");
      mcp[i].setFilterCoefficient(3);
      Serial.print("Filter coefficient value set to: ");
      Serial.println(mcp[i].getFilterCoefficient());
    }
  }


  //  mcp.setAlertTemperature(1, 30);
  //  Serial.print("Alert #1 temperature set to ");
  //  Serial.println(mcp.getAlertTemperature(1));
  //  mcp.configureAlert(1, true, true);  // alert 1 enabled, rising temp

  //  mcp.enable(true);

  Serial.println(F("------------------------------"));
}

void loop()
{
  int i;
  for(i=0;i<8;i++) {
    Serial.print(i+1,DEC);
    Serial.print("   Hot Junction: "); Serial.print(mcp[i].readThermocouple());
    Serial.print("   Cold Junction: "); Serial.print(mcp[i].readAmbient());
    Serial.print("   ADC: "); Serial.print(mcp[i].readADC() * 2);
    Serial.println(" uV");
  }
  Serial.println(F("------------------------------"));
  delay(1000);
}
