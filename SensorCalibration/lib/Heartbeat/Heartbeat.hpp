#ifndef HEARTBEAT_HPP
#define HEARTBEAT_HPP

#include <Arduino.h>

namespace LEDheartbeat
{
    unsigned long previousMillisHB = 0; // will store last time LED was updated
    const long intervalHB_High = 500;   // interval at which to blink (milliseconds)
    const long intervalHB_Low = 50;     // interval at which to blink (milliseconds)
    int ledstate = LOW;

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
        if(ledstate == LOW && currentMillis - previousMillisHB >= intervalHB_High){
            ledstate = HIGH;
            digitalWrite(ledHb, ledstate);
            previousMillisHB = currentMillis;
        } else if (ledstate == HIGH && currentMillis - previousMillisHB >= intervalHB_Low){
            ledstate = LOW;
            digitalWrite(ledHb, ledstate);
            previousMillisHB = currentMillis;
        }
    }

} // namespace LEDheartbeat

#endif