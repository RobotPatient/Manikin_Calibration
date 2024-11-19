#include "nau7802.hpp"

nau7802::nau7802(TwoWire *wire) : _wire{wire}
{
    loadCell = new NAU7802();
    if (loadCell->begin(*_wire, true) == false)
    {
        Serial.println("No Load Cell Found");
    }
}

nau7802::~nau7802()
{
    //loadCell->powerDown();
    _wire->end();
}

uint32_t nau7802::readLoadCell()
{
    if (loadCell->available())
    {
        _value = loadCell->getReading();
        return _value;
    }
    return 0;
}

void nau7802::printValue(const char *seperationCharacter)
{
    Serial.print(seperationCharacter);
    Serial.print(_value);
}
