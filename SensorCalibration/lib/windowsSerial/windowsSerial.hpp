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
    windowsSerial(const std::string &portName, int baudrate = 115200, bool configurePort = false);
    windowsSerial();
    ~windowsSerial();
    void setNewPort(const std::string &portName);
    void setNewPort(int portNumber);
    void setNewBaudrate(int baudrate);
    std::string getPort();
    int configureSerialPort();
    void writeToSerialPort(const std::string &data);
    std::string readFromSerialPort();
    void serialToCout();
};

#endif