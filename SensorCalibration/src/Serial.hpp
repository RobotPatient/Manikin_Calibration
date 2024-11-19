#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <Arduino.h>

namespace SerialPC
{
  void setupSerial()
  {
    delay(1500);
    Serial.begin(115200);
    delay(1500);
  }

  void waitForSerial()
  {
    while (!Serial)
    {
      ;
    }

    delay(1500);
  }

  void printColum()
  {
    Serial.println("Nr;LoadCell;CH1;CH2;CH3;CH4;CH5;CH6;CH7;CH8");
  }

  void printColumSingle()
  {
    Serial.print("Nr;LoadCell;"); // excpect another colum
  }

} // namespace SerialPC

#endif