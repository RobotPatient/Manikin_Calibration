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

ads7138 *fingerPositionSensor;
nau7802 *loadCell;

unsigned int i = 0;
unsigned int sampleSize;
float referenceValues[MAX_SAMPLE], vingerposition[ADS_CHANNEL_AMOUNT][MAX_SAMPLE];
int32_t sOffset = 0x0000;
float sCalFactor = 0.0f;
char receivedBytes[255];
char receivedBytes2[255];

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

void setup()
{
  SerialPC::setupSerial();
  heartbeat::setupLEDs();
  sensorcom::wireSetup();
  fingerPositionSensor = new ads7138(&sensorcom::WireSensorA, ADS7138_ADDR);
  loadCell = new nau7802(&sensorcom::WireSensorB);
  fingerPositionSensor->resetStatus();
  SerialPC::waitForSerial();

  readValues(sOffset, sCalFactor, sampleSize);
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
    Serial.read(); // consume character

    loadCell->readLoadCell();
    fingerPositionSensor->readValues();
    // TODO: write to memory? (sd card needed on hardware stuffs)
    if (Serial)
    {
      referenceValues[i] = loadCell->getValue();
      for (int channel = 0; channel < 8; channel++)
      {
        vingerposition[channel][i] = fingerPositionSensor->getValue(channel);
      }
      Serial.print(i++);
      loadCell->printValue(SEPERATION_CHAR);
      fingerPositionSensor->printValues(SEPERATION_CHAR);
      Serial.println();
      Serial.flush();
    }

    if (i == sampleSize) // if there are n samples, calculate the regression values
    {
      for (int channel = 0; channel < 8; channel++)
      {
        LinearRegression fingerPositionRegression = LinearRegression(referenceValues, vingerposition[channel], sampleSize);
        struct linearValue myValue = fingerPositionRegression.calcAlphaBeta();
        float r2 = fingerPositionRegression.calcR2();
        float se = fingerPositionRegression.calcStandardError();
        SerialPC::printRegression(myValue, r2, se, channel);
      }
      Serial.println();
      Serial.flush();
    }
  }
}
