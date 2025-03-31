#ifndef CNCCONTROL_HPP
#define CNCCONTROL_HPP

#include "windowsSerial.hpp"
#include <windows.h>

// START
// Measure move MOVE(Z, 0.1) 10x, MOVE(Z, -1)
// x0, y15
// x -9.5, y4.5
// x 9.5 y4
// x-9.5, y4
// x-9.5, y4.5
// x9.5, y-4.5
// x0, y-8

class CNCController : public windowsSerial
{
private:
    bool waitForCompletion();

public:
    CNCController(const std::string &portName, int baudrate = 115200);
    CNCController();
    bool moveRelative(const std::string &axis, double length_mm, bool waitForMovement = true);
    bool setCurrentPositionToZero();
    bool moveToHomePosition();
    bool moveOverToNext(int position);
};

#endif