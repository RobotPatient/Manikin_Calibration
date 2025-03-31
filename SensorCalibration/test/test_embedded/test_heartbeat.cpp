#include <Arduino.h>
#include <unity.h>

#include "Heartbeat.hpp"
#include "Sensorhub_definitions.hpp"

void test_Heartbeat_LED_Off(void)
{
  heartbeat::ledOff();
  TEST_ASSERT_EQUAL(LOW, digitalRead(ledHb));
}

void test_Heartbeat_LED_On(void)
{
  heartbeat::ledOn();
  TEST_ASSERT_EQUAL(HIGH, digitalRead(ledHb));
}

void setup()
{
  Serial.begin(BAUDRATE);
  heartbeat::setupLEDs();
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(test_Heartbeat_LED_Off);
  RUN_TEST(test_Heartbeat_LED_On);
  UNITY_END();
}

void loop() {}