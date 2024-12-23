#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <Arduino.h>
#include <wdt_samd21.h>

namespace SerialPC
{
  void setupSerial() { Serial.begin(BAUDRATE); }

  void waitForSerial()
  {
    while (!Serial)
    {
      ;
    }
  }

  void printColum()
  {
    if (!Serial)
    {
      return;
    }
    Serial.println(F("Nr;LoadCell;CH1;CH2;CH3;CH4;CH5;CH6;CH7;CH8"));
  }

  void printColumSingle()
  {
    if (!Serial)
    {
      return;
    }
    Serial.print(F("Nr;LoadCell;")); // excpect another colum
  }

  void printRegression(linearValue myValue, float r2, float se, int channel)
  {
    if (!Serial)
    {
      return;
    }
    Serial.print("C ");
    Serial.print(channel);
    Serial.print(" ");
    Serial.print(myValue.b1);
    Serial.print(" ");
    Serial.print(myValue.b0);
    Serial.print(" ");
    Serial.print(r2);
    Serial.print(" ");
    Serial.print(se);
    Serial.print(" ");
  }
  void setupReset()
  {
    wdt_init(WDT_CONFIG_PER_64);
    wdt_disable();
  }
  void resetByCommand()
  {
    if (Serial.available())
    {
      String command = Serial.readStringUntil('\n');
      if (command == "RESET")
      {
        wdt_reEnable(); // Enable watchdog timer
        while (1)
        {
        } // Wait for reset
      }
    }
  }

} // namespace SerialPC

#endif