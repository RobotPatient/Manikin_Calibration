#ifndef NAU7802_HPP
#define NAU7802_HPP

#include <Arduino.h>
#include <SparkFun_Qwiic_Scale_NAU7802_Arduino_Library.h>

/*!
 * @brief nau7802 wrapper class, used to comunicate and get data out of the loadcell. Uses TwoWire to communicate
 */
class nau7802
{
private:
    NAU7802 *_loadCell;
    TwoWire *_wire;
    int32_t _offset;
    float _value, _calibrationFactor;

    /*!
     * @brief Clears the Serial buffer and waits until a key is pressed
     */
    void waitForUserKeyPress();

public:
    /*!
     * @brief Consturctor for the class
     * @param wire Pointer to the TwoWire class. Should already be configured with the right pin configuration
     */
    nau7802(TwoWire *wire);

    /*!
     * @brief ends TwoWire connection
     */
    ~nau7802();

    /*!
     * @brief Reads out load cell value and puts it in _value.
     * given value is the weight (when calibrated) So no calulation is nessesary (since weight is already a force, to get the mass devide by g constant)
     * @return _value. Measured weight on the load cell
     */
    int32_t readLoadCell(bool calibratedRead = true);

    /*!
     * @brief get last measured value of the sensor
     * @return int32_t, last measured value
     */
    int32_t getValue();

    /*!
     * @brief Prints last measured value stored in _value to the Serial UART
     * @param seperationCharacter default ";". Prints this character before printing value
     */
    void printValue(const char *seperationCharacter = ";");

    /*!
     * @brief Helper function to print the zero offset value to Serial
     */
    void printZeroOffset();

    /*!
     * @brief Calibrates internally by settting the 0 value, excpect the loadcell to have no load at running temperature
     */
    void calibrateInternal();

    /*!
     * @brief Calibrates externally by measuring the loadcell when nothing is on it and when a known weight is on the loadcell.
     */
    void calibrateExternal();

    /*!
     * @brief
     *
     *
     * @param newOffset
     * @param newCalibrationFactor
     * @param newGain
     */
    void setCalibrationValues(int32_t newOffset, float newCalibrationFactor, int32_t newGain);
};

#endif