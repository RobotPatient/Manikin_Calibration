#include <Arduino.h>
#include <Wire.h>
#include <wiring_private.h>

#include "Heartbeat.hpp"
#include "LinearRegression.hpp"
#include "SensorComs.hpp"
#include "Sensorhub_definitions.hpp"
#include "Serial.hpp"
#include "ads7138_definitions.hpp"
#include "ads7138.hpp"
#include "nau7802.hpp"
#include "matrix.hpp"

ads7138 *fingerPositionSensor;
nau7802 *loadCell;

unsigned int sampleNumber = 0;
unsigned int sampleSize;
unsigned int positionIndexGlobal = 0;
double referenceValues[MAX_SAMPLE], vingerposition[ADS_CHANNEL_AMOUNT][MAX_SAMPLE];
int32_t sOffset = 0x0000;
float sCalFactor = 0.0f;
char receivedBytes[255];
char receivedBytes2[255];
matrix<float, 3, 3> test;

void setup()
{
  SerialPC::setupSerial();
  heartbeat::setupLEDs();
  sensorcom::wireSetup();
  fingerPositionSensor = new ads7138(&sensorcom::WireSensorA, ADS7138_ADDR);
  loadCell = new nau7802(&sensorcom::WireSensorB);
  fingerPositionSensor->resetStatus();
  SerialPC::waitForSerial();
  // Serial.println("Serial Connected!\n");
  SerialPC::setupReset();

  SerialPC::readValues(sOffset, sCalFactor, sampleSize);
  loadCell->setCalibrationValues(sOffset, sCalFactor, 0);
  loadCell->calibrateInternal();
  // loadCell->calibrateExternal();

  // loadCell->setCalibrationValues(136054, 436.32, 0);

  SerialPC::printColum();
}

void loop()
{
  heartbeat::updateHeartBeat();
  // if (heartbeat::runPolling())
  if (Serial.available() > 0) // Only measure when character is send
  {
    String command = SerialPC::readCommand();
    // fsm->handleState(command);
    SerialPC::resetByCommand(command);
    Serial.read(); // consume character

    loadCell->readLoadCell();
    fingerPositionSensor->readValues();

    referenceValues[sampleNumber] = loadCell->getValue();
    for (int positionIndex = 0; positionIndex < 8; positionIndex++)
    {
      vingerposition[positieToChannel[positionIndex]][sampleNumber] = fingerPositionSensor->getValue(positieToChannel[positionIndex]);
    }
    Serial.print(sampleNumber++);
    loadCell->printValue(SEPERATION_CHAR);
    fingerPositionSensor->printValues(SEPERATION_CHAR);
    Serial.println();
    Serial.flush();

    if (sampleNumber == sampleSize) // if there are n samples, calculate the regression values
    {

      LinearRegression fingerPositionRegression = LinearRegression(vingerposition[positieToChannel[positionIndexGlobal]], referenceValues, sampleSize);
      struct linearValue myValue = fingerPositionRegression.calcAlphaBeta();
      float r2 = fingerPositionRegression.calcR2();
      float se = fingerPositionRegression.calcStandardError();
      SerialPC::printRegression(myValue, r2, se, positieToChannel[positionIndexGlobal++]);
      Serial.println();
      Serial.flush();
      sampleNumber = 0;
    }
  }
}
