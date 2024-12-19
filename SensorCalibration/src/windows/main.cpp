#include <windows.h>
#include <iostream>
#include <conio.h> // _kbhit() and _getchar()
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "windowsSerial.hpp"
#include "windowsConfigManager.hpp"
#include "windowsLogger.hpp"

#define CONFIG_PATH "C:\\Users\\thomasoe\\OneDrive - Capgemini\\Documents\\GitRepo\\Manikin_Calibration\\SensorCalibration\\config.ini"
#define LOG_DIR "C:\\Users\\thomasoe\\OneDrive - Capgemini\\Documents\\GitRepo\\Manikin_Calibration\\SensorCalibration\\data\\"

struct sampleData
{
    unsigned int sampleNumber;
    std::vector<int> fingerPositionValues;
    int loadCellValue;
};

int main()
{
    windowsSerial uart;
    windowsConfigManager config(CONFIG_PATH);
    int portNumber;
    windowsLogger logger(LOG_DIR);

    std::string portName = config.readString("Settings", "Port", "ERROR");
    std::cout << "Port from settings: " << portName << std::endl;
    uart.setNewPort(portName);

    if (!uart.configureSerialPort())
    {
        return 1;
    }

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
            sampleData data;
            std::istringstream strm(receivedData);
            strm >> data.sampleNumber;
            strm >> data.loadCellValue;
            int fingerValue;
            for (int i = 0; i < 8; i++)
            {
                strm >> fingerValue;
                data.fingerPositionValues.push_back(fingerValue);
            }

            std::cout << "Sample Nr: " << data.sampleNumber;
            logger << data.sampleNumber << ";";
            std::cout << " LoadCell data: " << data.loadCellValue << " FingerPosition data:";
            logger << data.loadCellValue;
            for (int i = 0; i < data.fingerPositionValues.size(); i++)
            {
                std::cout << " " << i << "=" << data.fingerPositionValues.at(i);
                logger << ";" << data.fingerPositionValues.at(i);
            }
            std::cout << std::endl;
            logger << "\n";
        }
        Sleep(10);
    }

    return 0;
}