#include "nau7802.hpp"

nau7802::nau7802(TwoWire *wire) : _wire{wire}
{
    _loadCell = new NAU7802();
    if (_loadCell->begin(*_wire, true) == false)
    {
        Serial.println(F("No Load Cell Found"));
        return;
    }
    // _loadCell->reset();
    // _loadCell->setLDO();
}

nau7802::~nau7802()
{
    // _loadCell->powerDown();
    _wire->end();
}

int32_t nau7802::readLoadCell(bool calibratedRead)
{
    if (!_loadCell->available())
    {
        return 0;
    }

    if (calibratedRead)
    {
        _value = _loadCell->getWeight(true, 64);
    }
    else
    {
        _value = _loadCell->getReading();
    }

    return _value;
}

int32_t nau7802::getValue()
{
    return _value;
}

void nau7802::printZeroOffset()
{
    Serial.print(";\t");
    Serial.print(_loadCell->getZeroOffset());
}

void nau7802::calibrateInternal()
{
    _loadCell->setSampleRate((uint8_t)320);

    if (!_loadCell->calibrateAFE(NAU7802_CALMOD_INTERNAL))
    {
        Serial.println(F("NAU: Calibration Fail"));
    }
    _loadCell->calculateZeroOffset(128);
    Serial.print(F("New Offset: "));
    Serial.println(_loadCell->getZeroOffset());
}

void nau7802::printValue(const char *seperationCharacter)
{
    Serial.print(seperationCharacter);
    Serial.print(_value);
}

void nau7802::calibrateExternal()
{
    Serial.println(F("Scale calibration"));
    Serial.println(F("Setup scale with no weight on it. Press a key when ready."));
    waitForUserKeyPress();

    // Perform an external offset - this sets the NAU7802's internal offset register
    _loadCell->calibrateAFE(NAU7802_CALMOD_OFFSET); // Calibrate using external offset

    _offset = _loadCell->getZeroOffset();
    //_offset = _loadCell->getChannel1Offset();
    Serial.print(F("New NAU7802 offset: "));
    Serial.println(_offset);
    // TODO: Save offset to NVM

    Serial.println(F("Place known weight on scale. Press a key when weight is in place and stable."));
    waitForUserKeyPress();

    Serial.print(F("Please enter the weight, in grams (g), currently sitting on the scale (for example '4.25'): "));
    waitForUserKeyPress();

    // Read user input
    float weightOnScale = Serial.parseFloat();
    Serial.println(weightOnScale);

    // Tell the library how much weight is currently on it
    // We are sampling slowly, so we need to increase the timeout too
    _loadCell->calculateCalibrationFactor(weightOnScale, 64, 3000); // 64 samples at 40SPS. Use a timeout of 3 seconds
    _gain = _loadCell->getCalibrationFactor();
    // _gain = _loadCell->getChannel1Gain();
    Serial.print(F("Weight on scale: "));
    Serial.println(weightOnScale, 2);
    Serial.print(F("New library calibration factor: "));
    Serial.println(_gain, 2);
    // TODO: Save factor to NVM
}

void nau7802::waitForUserKeyPress()
{
    while (Serial.available())
    {
        Serial.read(); // Clear anything in RX buffer
    }
    while (Serial.available() == 0)
    {
        // Wait for user to press key
    }
}

void nau7802::setCalibrationValues(int32_t newOffset, uint8_t newGain)
{
    _offset = newOffset;
    _gain = newGain;
    _loadCell->setZeroOffset(_offset);
    _loadCell->setGain(_gain);
}
