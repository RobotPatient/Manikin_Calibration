#ifndef HEARTBEAT_HPP
#define HEARTBEAT_HPP

#include <Arduino.h>

namespace heartbeat
{
    struct LED
    {
        unsigned long previousMillis = 0;        // will store last time LED was updated
        const unsigned long interval_High = 500; // interval at which to blink (milliseconds)
        const unsigned long interval_Low = 50;   // interval at which to blink (milliseconds)
        int ledstate = LOW;
    } LED;

    struct polling
    {
        unsigned long previousMillis = 0;
        const unsigned long intervalUpdate = 1000;
    } polling;

    void setupLEDs()
    {
        pinMode(ledHb, OUTPUT);
        digitalWrite(ledHb, HIGH);
    }
    void ledOn()
    {
        digitalWrite(ledHb, HIGH);
    }
    void ledOff()
    {
        digitalWrite(ledHb, LOW);
    }

    void updateHeartBeat()
    {
        unsigned long currentMillis = millis();
        if (LED.ledstate == LOW && currentMillis - LED.previousMillis >= LED.interval_High)
        {
            LED.ledstate = HIGH;
            digitalWrite(ledHb, LED.ledstate);
            LED.previousMillis = currentMillis;
        }
        else if (LED.ledstate == HIGH && currentMillis - LED.previousMillis >= LED.interval_Low)
        {
            LED.ledstate = LOW;
            digitalWrite(ledHb, LED.ledstate);
            LED.previousMillis = currentMillis;
        }
    }

    bool runPolling()
    {
        unsigned long currentMillis = millis();
        bool result = currentMillis - polling.previousMillis >= polling.intervalUpdate;
        if (result)
        {
            polling.previousMillis = currentMillis;
        }
        return result;
    }

} // namespace LEDheartbeat

#endif