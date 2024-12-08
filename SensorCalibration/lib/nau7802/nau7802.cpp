#include "nau7802.hpp"

nau7802::nau7802(TwoWire *wire) : _wire{wire}
{
    loadCell = new NAU7802();
    if (loadCell->begin(*_wire, true) == false)
    {
        Serial.println("No Load Cell Found");
        return;
    }
    // loadCell->reset();
    // loadCell->setLDO();
}

nau7802::~nau7802()
{
    // loadCell->powerDown();
    _wire->end();
}

int32_t nau7802::readLoadCell(bool calibratedRead)
{
    if (loadCell->available())
    {
        if (calibratedRead)
        {
            _value = loadCell->getWeight(true, 64);
        }
        else
        {
            _value = loadCell->getReading();
        }
        return _value;
    }
    return 0;
}

void nau7802::printZeroOffset()
{
    Serial.print(";\t");
    Serial.print(loadCell->getZeroOffset());
}

void nau7802::calibrateInternal()
{
    loadCell->setSampleRate((uint8_t)320);

    if (!loadCell->calibrateAFE(NAU7802_CALMOD_INTERNAL))
    {
        Serial.println("NAU: Calibration Fail");
    }
    loadCell->calculateZeroOffset(128);
    Serial.print("New Offset: ");
    Serial.println(loadCell->getZeroOffset());
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
    while (Serial.available())
    {
        Serial.read(); // Clear anything in RX buffer
    }
    while (Serial.available() == 0)
    {
        // Wait for user to press key
    }

    // Perform an external offset - this sets the NAU7802's internal offset register
    loadCell->calibrateAFE(NAU7802_CALMOD_OFFSET); // Calibrate using external offset

    Serial.print(F("New NAU7802 offset register: "));
    Serial.println(loadCell->getChannel1Offset());
    // Serial.print(F("New zero offset: "));
    // Serial.println(loadCell->getZeroOffset());
    // TODO: Save offset to NVM

    Serial.println(F("Place known weight on scale. Press a key when weight is in place and stable."));
    waitForUserKeyPress();

    Serial.print(F("Please enter the weight, without units, currently sitting on the scale (for example '4.25'): "));
    waitForUserKeyPress();

    // Read user input
    float weightOnScale = Serial.parseFloat();
    Serial.println(weightOnScale);

    // Tell the library how much weight is currently on it
    // We are sampling slowly, so we need to increase the timeout too
    loadCell->calculateCalibrationFactor(weightOnScale, 64, 3000); // 64 samples at 40SPS. Use a timeout of 3 seconds
    Serial.print(F("Weight on scale: "));
    Serial.println(weightOnScale, 2);
    Serial.print(F("New library calibration factor: "));
    Serial.println(loadCell->getCalibrationFactor(), 2);
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
