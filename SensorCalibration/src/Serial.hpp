#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <Arduino.h>

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

  void printRegression(linearValue myValue, float r2, float se)
  {
    if (!Serial)
    {
      return;
    }
    Serial.print("alpha: ");
    Serial.print(myValue.b1);
    Serial.print("; beta: ");
    Serial.print(myValue.b0);
    Serial.print("; R2: ");
    Serial.print(r2);
    Serial.print("; Standard Error: ");
    Serial.println(se);
  }

} // namespace SerialPC

#endif