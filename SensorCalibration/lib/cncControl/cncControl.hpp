#ifndef CNCCONTROL_HPP
#define CNCCONTROL_HPP

#include "windowsSerial.hpp"
#include <windows.h>

class CNCController : public windowsSerial
{
public:
    CNCController(const std::string &portName, int baudrate = 115200);

    bool moveRelativeZ(double length_mm);
    bool setCurrentPositionToZero();
    bool moveToHomePosition();
};

#endif