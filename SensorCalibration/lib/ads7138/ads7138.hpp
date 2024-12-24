#ifndef ADS7138_HPP
#define ADS7138_HPP

#include <Arduino.h>
#include <Wire.h>

/*!
 * @brief Wrapper class for the ads7138 ADC, Uses TwoWire. gets 8 values from the fingerpositioning sensor
 */
class ads7138
{
private:
    TwoWire *_wire;
    const byte _deviceAddress;
    const size_t _size;
    int *_sensorData, _value;

public:
    /*!
     * @brief Constructor for the class
     * @param wire Pointer to the TwoWire class. Should already be configured with the right pin configuration
     * @param deviceAddress The device adress of the ads7138
     * @param size Standard size of 8. Creates an array for temporary storage of each incoming measurement
     */
    ads7138(TwoWire *wire, const byte deviceAddress, const size_t size = 8);

    /*!
     * @brief Deletes _sensorData[] and ends the TwoWire
     */
    ~ads7138();

    /*!
     * @brief sends reset command to ads7138. Used after starting up before measuring
     */
    void resetStatus();

    /*!
     * @brief Writes a byte to a specific adress of the ads7138
     * @param registerAddr The register the byte/command is written to
     * @param command The byte/command that will be written
     * @return returns 0 if succesfull, see TwoWire::endTransmission() for all error codes
     */
    uint8_t writeToRegister(byte registerAddr, byte command);

    /*!
     * @brief Request a specific channel to send data
     * @param channel The channel which needs to be read out
     * @return returns raw value of given channel
     */

    int readChannel(byte channel);

    /*!
     * @brief Reads out all channel and puts it in _value[]
     */
    void readValues();

    /*!
     * @brief Get the value of a given channel from the previous measured moment
     * @param channel Channel number
     * @return int value of the given channel
     */
    int getValue(int channel);

    /*!
     * @brief Prints out channel value from _value[channel] to the UART with Serial. Expects Serial to be setup
     * @param channel channel to print to UART
     * @param seperationCharacter seperation character to print right after the value
     */
    void printValue(int channel, const char *seperationCharacter = ";");

    /*!
     * @brief Prints out all channels over UARTS with Serial. Expects Serial to be setup
     * @param seperationCharacter seperation character to print right after each value
     */
    void printValues(const char *seperationCharacter = ";");
};

#endif