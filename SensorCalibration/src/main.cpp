#include <Arduino.h>
#include <Wire.h>
#include <wiring_private.h>

#include "ads7138.hpp"
#include "nau7802.hpp"
#include "Sensorhub_definitions.hpp"
#include "Heartbeat.hpp"
#include "Serial.hpp"
#include "SensorComs.hpp"

// #define AMOUNT 50 // Log AMOUNT of datapoints in time, comment when coninious logging
// #define SINGLE    // Log single channel, comment when logging all channels
#define CHANNEL 0 // select channel to log

ads7138 *ads;
nau7802 *nau;

unsigned i = 0;

void setup()
{
  SerialPC::setupSerial();
  LEDheartbeat::setupLEDs();
  sensorcom::wireSetup();
  ads = new ads7138(&sensorcom::WireSensorA, ADS7138_ADDR);
  nau = new nau7802(&sensorcom::WireSensorB);
  ads->resetStatus();
  SerialPC::waitForSerial();
  // nau->calibrateInternal();
  nau->calibrateExternal();

#ifdef SINGLE
  SerialPC::printColumSingle();
  Serial.print("CH");
  Serial.println(CHANNEL);
#else
  SerialPC::printColum();
#endif
}

void loop()
{
  LEDheartbeat::updateHeartBeat();
#ifdef AMOUNT
  if (i <= AMOUNT)
  {
#endif
    nau->readLoadCell();
    ads->readValues();
    Serial.print(i++);
    nau->printValue(SEPERATION_CHAR);
#ifdef SINGLE
    ads->printValue(CHANNEL, SEPERATION_CHAR);
#else
  ads->printValues(SEPERATION_CHAR);
#endif
    // nau->printZeroOffset();
    Serial.println();
    delay(1000);
#ifdef LOG_AMOUNT
  }
#endif
}
