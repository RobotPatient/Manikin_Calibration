#include <windows.h>
#include <iostream>
#include <conio.h>
#include "windowsSerial.hpp"
#include "windowsConfigManager.hpp"

#define CONFIG_PATH "C:\\Users\\thomasoe\\OneDrive - Capgemini\\Documents\\GitRepo\\Manikin_Calibration\\SensorCalibration\\config.ini"

int main()
{
    windowsSerial uart;
    windowsConfigManager config(CONFIG_PATH);
    int portNumber;

    // std::cout << "type number to change com port: ";
    // std::cin >> portNumber;

    std::string portName = config.readString("Settings", "Port", "ERROR");
    std::cout << "Port from settings: " << portName << std::endl;
    uart.setNewPort(portName);

    // std::cout << "The COM port is = " << uart.getPort() << std::endl;

    uart.configureSerialPort();

    while (true)
    {
        // Exit while loop when keystroke is detected
        if (_kbhit())
        {
            _getch(); // Consume the character
            break;
        }

        std::string receivedData = uart.readFromSerialPort();
        if (!receivedData.empty())
        {
            std::cout << "Received: " << receivedData << std::endl;
        }
        Sleep(10);
    }

    return 0;
}