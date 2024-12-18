#include "windowsSerial.hpp"

windowsSerial::windowsSerial(const std::string &portName) : _portName{portName}
{
    configureSerialPort();
}

windowsSerial::windowsSerial()
{
}

windowsSerial::~windowsSerial()
{
    CloseHandle(_hSerial);
}

void windowsSerial::setNewPort(const std::string &portName)
{
    _portName = portName;
}

void windowsSerial::setNewPort(int portNumber)
{
    _portName = "COM" + std::to_string(portNumber);
}

std::string windowsSerial::getPort()
{
    return _portName;
}

void windowsSerial::configureSerialPort()
{
    _hSerial = CreateFile(_portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (_hSerial == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error opening serial port" << std::endl;
        exit(1);
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(_hSerial, &dcbSerialParams))
    {
        std::cerr << "Error getting serial port state" << std::endl;
        exit(1);
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(_hSerial, &dcbSerialParams))
    {
        std::cerr << "Error setting serial port state" << std::endl;
        exit(1);
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(_hSerial, &timeouts))
    {
        std::cerr << "Error setting serial port timeouts" << std::endl;
        exit(1);
    }
}

void windowsSerial::writeToSerialPort(const std::string &data)
{
    DWORD bytesWritten;
    if (!WriteFile(_hSerial, data.c_str(), data.length(), &bytesWritten, NULL))
    {
        std::cerr << "Error writing to serial port" << std::endl;
    }
}

std::string windowsSerial::readFromSerialPort()
{
    char buffer[256];
    DWORD bytesRead;
    if (!ReadFile(_hSerial, buffer, sizeof(buffer), &bytesRead, NULL))
    {
        std::cerr << "Error reading from serial port" << std::endl;
    }
    return std::string(buffer, bytesRead);
}