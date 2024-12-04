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

    /*!
     * @brief Reads out load cell value and puts it in _value.
     * given value is the weight (when calibrated) So no calulation is nessesary (since weight is already a force, to get the mass devide by g constant)
     * @return _value. Measured weight on the load cell
     */
    int32_t readLoadCell(bool calibratedRead = true);
    void printValue(const char *seperationCharacter = ";");
    void printZeroOffset();
    void calibrateInternal();
    void calibrateExternal();
};

#endif