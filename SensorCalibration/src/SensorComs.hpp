#ifndef SENSORCOMS_HPP
#define SENSORCOMS_HPP

#include <Wire.h>
#include <wiring_private.h>

#include "Sensorhub_definitions.hpp"

namespace sensorcom
{
  TwoWire WireSensorA(&sercom1, W1_SDA, W1_SCL); // Sensor Port A
  TwoWire WireSensorB(&sercom4, W2_SDA, W2_SCL); // Sensor Port B

  void wireSetup()
  {
    Wire.begin();
    WireSensorA.begin();
    WireSensorB.begin();

    pinPeripheral(W1_SCL, PIO_SERCOM_ALT);
    pinPeripheral(W1_SDA, PIO_SERCOM_ALT);
    pinPeripheral(W2_SCL, PIO_SERCOM);
    pinPeripheral(W2_SDA, PIO_SERCOM);
  }

} // namespace sensorcom

#endif