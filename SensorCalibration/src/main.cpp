#include <Arduino.h>
#include <Wire.h>
#include <wiring_private.h>

#include "ads7138.hpp"
#include "nau7802.hpp"
#include "Sensorhub_definitions.hpp"
#include "Heartbeat.hpp"
#include "Serial.hpp"
#include "SensorComs.hpp"

ads7138 *ads;
nau7802 *nau;

unsigned i = 0;

void setup()
{
  SerialPC::setupSerial();
  heartbeat::setupLEDs();
  sensorcom::wireSetup();
  ads = new ads7138(&sensorcom::WireSensorA, ADS7138_ADDR);
  nau = new nau7802(&sensorcom::WireSensorB);
  ads->resetStatus();
  SerialPC::waitForSerial();
  // nau->calibrateInternal();
  nau->calibrateExternal();

  SerialPC::printColum();
}

void loop()
{
  heartbeat::updateHeartBeat();
  if (heartbeat::runPolling())
  {
    nau->readLoadCell();
    ads->readValues();
    Serial.print(i++);
    nau->printValue(SEPERATION_CHAR);
    ads->printValues(SEPERATION_CHAR);
    Serial.println();
  }
}
