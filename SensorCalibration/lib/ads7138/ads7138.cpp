#include "ads7138.hpp"
#include "ads7138_definitions.hpp"

ads7138::ads7138(TwoWire *wire, const byte deviceAddress, const size_t size) : _wire{wire}, _deviceAddress{deviceAddress}, _size{size}
{
    _sensorData = new int[_size];
}

ads7138::~ads7138()
{
    delete[] _sensorData;
    _wire->end();
}

void ads7138::resetStatus()
{
    writeToRegister(SYSTEM_STATUS, RESET_SYS_STAT);
}

uint8_t ads7138::writeToRegister(byte registerAddr, byte command)
{
    _wire->beginTransmission(_deviceAddress);
    _wire->write(SINGLE_WRITE);
    _wire->write(registerAddr);
    _wire->write(command);
    return _wire->endTransmission();
}

int ads7138::readChannel(byte channel)
{
    writeToRegister(CHANNEL_SEL, channel);
    _wire->requestFrom(_deviceAddress, CHANNEL_BYTE_LENGHT);

    if (_wire->available() > CHANNEL_BYTE_LENGHT)
    {
        return 0;
    }

    _value = 0;
    _value = _wire->read();                 // Receive high byte
    _value = (_value << 8) | _wire->read(); // Receive low byte and combine with high byte
    return _value;
}

void ads7138::readValues()
{
    for (int channel = 0; channel < (int)_size; ++channel)
    {
        _sensorData[channel] = readChannel(channel);
    }
}

void ads7138::printValues(const char *seperationCharacter)
{
    for (int channel = 0; channel < (int)_size; ++channel)
    {
        printValue(channel, seperationCharacter);
    }
}

void ads7138::printValue(int channel, const char *seperationCharacter)
{
    Serial.print(seperationCharacter);
    Serial.print(_sensorData[channel]);
}