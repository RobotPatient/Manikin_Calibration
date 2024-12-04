#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <Arduino.h>

namespace SerialPC
{
  void setupSerial()
  {
    Serial.begin(BAUDRATE);
  }

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

} // namespace SerialPC

#endif