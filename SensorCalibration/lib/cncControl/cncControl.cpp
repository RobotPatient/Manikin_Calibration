#include "cncControl.hpp"

CNCController::CNCController(const std::string &portName, int baudrate) : windowsSerial(portName, baudrate)
{
}

bool CNCController::moveRelativeZ(double length_mm)
{
    // Set to incremental positioning
    const char *setIncremental = "G91\n";
    writeToSerialPort(setIncremental);

    // Create the G-code command to move on the Z-axis
    std::string gcode = "G01 Z" + std::to_string(length_mm) + " F100\n";
    writeToSerialPort(gcode);

    std::cout << "G-code sent successfully!" << std::endl;
    return true;
}

bool CNCController::setCurrentPositionToZero()
{
    // Set the current position to (0,0,0)
    const char *setZero = "G92 X0 Y0 Z0\n";
    writeToSerialPort(setZero);

    std::cout << "Current position set to (0,0,0)!" << std::endl;
    return true;
}

bool CNCController::moveToHomePosition()
{
    // Move to the home position
    const char *moveToHome = "G28\n";
    writeToSerialPort(moveToHome);

    std::cout << "Moved to home position (0,0,0)!" << std::endl;
    return true;
}