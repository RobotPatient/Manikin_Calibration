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
  void resetByCommand(String command)
  {
    if (command == "RESET")
    {
      wdt_reEnable(); // Enable watchdog timer
      while (1)
      {
      } // Wait for reset
    }
  }

  String readCommand()
  {
    if (Serial.available() <= 0)
    {
      return "\0";
    }
    return Serial.readStringUntil('\n');
  }

  void readValues(int32_t &intValue, float &floatValue, unsigned int &value)
  {
    String input;

    // Lees de tweede float waarde tot aan de newline
    input = Serial.readStringUntil(' ');
    floatValue = input.toFloat();

    // Lees de eerste int32_t waarde tot aan de spatie
    input = Serial.readStringUntil(' ');
    intValue = input.toInt();

    // Lees de eerste int32_t waarde tot aan de spatie
    input = Serial.readStringUntil('\n');
    value = input.toInt();

    Serial.print(floatValue);
    Serial.print(" ");
    Serial.print(intValue);
    Serial.print(" ");
    Serial.println(value);
  }

} // namespace SerialPC

#endif