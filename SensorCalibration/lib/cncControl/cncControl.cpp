#include "cncControl.hpp"
#include <windows.h>
#include <thread>
#include <chrono>

CNCController::CNCController(const std::string &portName, int baudrate) : windowsSerial(portName, baudrate)
{
}

CNCController::CNCController()
{
}

bool CNCController::moveRelative(const std::string &axis, double length_mm, bool waitForMovement)
{
    // Set to incremental positioning
    const char *setIncremental = "G91\n";
    writeToSerialPort(setIncremental);
    // std::cout << setIncremental << readFromSerialPort();
    // Create the G-code command to move on the specified axis
    std::string gcode = "G0 " + axis + std::to_string(length_mm) + "\n"; // + " F100\n";
    writeToSerialPort(gcode);
    // std::cout << gcode << readFromSerialPort();

    // std::cout << "G-code sent successfully!" << std::endl;

    if (waitForMovement)
    {
        waitForCompletion();
    }
    // std::cout << "Move Completed!" << std::endl;
    return true;
}

bool CNCController::setCurrentPositionToZero()
{
    // Set the current position to (0,0,0)
    const char *setZero = "G10 P0 L20 X0 Y0 Z0\n";
    writeToSerialPort(setZero);

    std::cout << "Current position set to (0,0,0)!" << std::endl;

    std::string response = readFromSerialPort();
    std::cout << "Response: " << response << std::endl;

    return true;
}

bool CNCController::moveToHomePosition()
{
    // Move to the home position
    const char *moveToHome = "G28\n";
    writeToSerialPort(moveToHome);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "Moved to home position (0,0,0)!" << std::endl;
    return true;
}

// Movement Pattern
//      0
//      1
//  2       7
//      3
//  4       6
//      5
// Channel Numbers
//      5
//      4
//  7       2
//      3
//  0       1
//      6
bool CNCController::moveOverToNext(int position)
{
    switch (position)
    {
    case 0:
        // start position, do nothing
        break;
    case 1:
        moveRelative("Z", 1);
        moveRelative("Y", -15);
        moveRelative("Z", -1);
        break;
    case 2:
        moveRelative("Z", 1);
        moveRelative("X", -9.5);
        moveRelative("Y", -4.5);
        moveRelative("Z", -1);
        break;

    case 3:
        moveRelative("Z", 1);
        moveRelative("X", 9.5);
        moveRelative("Y", -4);
        moveRelative("Z", -1);
        break;

    case 4:
        moveRelative("Z", 1);
        moveRelative("X", -9.5);
        moveRelative("Y", -4);
        moveRelative("Z", -1);
        break;

    case 5:
        moveRelative("Z", 1);
        moveRelative("X", 9.5);
        moveRelative("Y", -4.5);
        moveRelative("Z", -1);
        break;

    case 6:
        moveRelative("Z", 1);
        moveRelative("X", 9.5);
        moveRelative("Y", 4.5);
        moveRelative("Z", -1);
        break;

    case 7:
        moveRelative("Z", 1);
        moveRelative("Y", 8);
        moveRelative("Z", -1);
        break;
    case 8: // move back to start
        moveRelative("Z", 1);
        moveRelative("X", -9.5);
        moveRelative("Y", 19.5);
        moveRelative("Z", -1);
        break;
    };
    return true;
}

bool CNCController::waitForCompletion()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // Check if the machine is still moving
        const char *checkStatus = "?";
        writeToSerialPort(checkStatus);
        std::string status = readFromSerialPort();
        // std::cout << status;
        if (status.find("Idle") != std::string::npos)
        {
            // std::cout << "Movement completed!" << std::endl;
            return true;
        }
    }
}