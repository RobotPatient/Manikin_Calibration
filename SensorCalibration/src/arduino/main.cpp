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

ads7138 *fingerPositionSensor;
nau7802 *loadCell;

unsigned int i = 0;
unsigned int n = 50;
float referenceValues[50], vingerposition[50];

void setup()
{
  SerialPC::setupSerial();
  heartbeat::setupLEDs();
  sensorcom::wireSetup();
  fingerPositionSensor = new ads7138(&sensorcom::WireSensorA, ADS7138_ADDR);
  loadCell = new nau7802(&sensorcom::WireSensorB);
  fingerPositionSensor->resetStatus();
  SerialPC::waitForSerial();
  // loadCell->calibrateInternal();
  // loadCell->calibrateExternal();

  SerialPC::printColum();
}

void loop()
{
  heartbeat::updateHeartBeat();
  if (heartbeat::runPolling())
  {
    loadCell->readLoadCell();
    fingerPositionSensor->readValues();
    // TODO: write to memory? (sd card needed on hardware stuffs)
    if (Serial)
    {
      referenceValues[i] = loadCell->getValue();
      vingerposition[i] = fingerPositionSensor->getValue(0);
      Serial.print(i++);
      loadCell->printValue(SEPERATION_CHAR);
      fingerPositionSensor->printValues(SEPERATION_CHAR);
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
