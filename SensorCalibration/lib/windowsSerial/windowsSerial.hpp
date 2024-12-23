#ifndef WINDOWSSERIAL_HPP
#define WINDOWSSERIAL_HPP

#include <windows.h>
#include <iostream>

class windowsSerial
{
private:
    HANDLE _hSerial;
    std::string _portName = "COM5"; // Default com port
    int _baudrate;
    /* data */
public:
    windowsSerial(const std::string &portName, int baudrate = 115200);
    windowsSerial();
    ~windowsSerial();
    void setNewPort(const std::string &portName);
    void setNewPort(int portNumber);
    std::string getPort();
    int configureSerialPort();
    void writeToSerialPort(const std::string &data);
    std::string readFromSerialPort();
    void serialToCout();
};

#endif