#include <Arduino.h>
#include <Wire.h>
#include <wiring_private.h>

#include "Heartbeat.hpp"
#include "LinearRegression.hpp"
#include "SensorComs.hpp"
#include "Sensorhub_definitions.hpp"
#include "Serial.hpp"
#include "ads7138.hpp"
#include "nau7802.hpp"

ads7138 *ads;
nau7802 *nau;

unsigned int i = 0;
unsigned int n = 50;
float referenceValues[50], vingerposition[50];

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
  // nau->calibrateExternal();

  SerialPC::printColum();
}

void loop()
{
  heartbeat::updateHeartBeat();
  if (heartbeat::runPolling())
  {
    nau->readLoadCell();
    ads->readValues();
    // TODO: write to memory? (sd card needed on hardware stuffs)
    if (Serial)
    {
      referenceValues[i] = nau->getValue();
      vingerposition[i] = ads->getValue(0);
      Serial.print(i++);
      nau->printValue(SEPERATION_CHAR);
      ads->printValues(SEPERATION_CHAR);
      Serial.println();
    }

    if (i == n) // if there are n samples, calculate the regression values
    {
      LinearRegression fingerPositionRegression = LinearRegression(referenceValues, vingerposition, n);
      struct linearValue myValue = fingerPositionRegression.calcAlphaBeta();
      float r2 = fingerPositionRegression.calcR2();
      float se = fingerPositionRegression.calcStandardError();
      SerialPC::printRegression(myValue, r2, se);
    }
  }
}
