#ifndef NAU7802_HPP
#define NAU7802_HPP

#include <Arduino.h>
#include <SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h>

class nau7802
{
private:
    NAU7802 *loadCell;
    TwoWire *_wire;
    int32_t _value;

public:
    nau7802(TwoWire *wire);
    ~nau7802();
    int32_t readLoadCell();
    void printValue(const char *seperationCharacter = ";");
    void printZeroOffset();
    void calibrateInternal();
    void calibrateExternal();
};

#endif