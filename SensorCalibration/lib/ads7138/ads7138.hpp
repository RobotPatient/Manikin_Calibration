#ifndef ADS7138_HPP
#define ADS7138_HPP

#include <Arduino.h>
#include <Wire.h>

class ads7138
{
private:
    TwoWire *_wire;
    const byte _deviceAddress;
    const size_t _size;
    int *_sensorData, _value;

public:
    ads7138(TwoWire *wire, const byte deviceAddress, const size_t size = 8);
    ~ads7138();
    void resetStatus();
    void writeToRegister(byte registerAddr, byte command);
    int readChannel(byte channel);
    void readValues();
    void printValues(const char *seperationCharacter = ";");
    void printValue(int channel, const char *seperationCharacter = ";");
};

#endif