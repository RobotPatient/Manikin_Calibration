#ifndef WINDOWSSERIAL_HPP
#define WINDOWSSERIAL_HPP

#include <windows.h>
#include <iostream>

class windowsSerial
{
private:
    HANDLE _hSerial;
    std::string _portName = "COM5"; // Default com port
    /* data */
public:
    windowsSerial(const std::string &portName);
    windowsSerial();
    ~windowsSerial();
    void setNewPort(const std::string &portName);
    void setNewPort(int portNumber);
    std::string getPort();
    void configureSerialPort();
    void writeToSerialPort(const std::string &data);
    std::string readFromSerialPort();
};

#endif