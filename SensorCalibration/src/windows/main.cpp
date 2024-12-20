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

    std::string writeb1 = config.readString("Reference_sensor", "b1", "0");
    std::string writeb0 = config.readString("Reference_sensor", "b0", "0");
    std::cout << "b1: " << writeb1 << ", b0: " << writeb0 << std::endl;
    uart.writeToSerialPort(writeb1 + "|" + writeb0);
    std::string receivedData1 = uart.readFromSerialPort();
    std::cout << receivedData1;

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
            // std::cout << receivedData;

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
            // std::cout << std::endl;
            logger << "\n";

            int i = 0;
            float datal[4];
            std::string temp, vv;
            if (i = receivedData.find('V') != std::string::npos)
            {
                std::string dataNew = receivedData.substr(i + 2);
                // float data[4];
                std::istringstream strm(receivedData);
                std::cout << std::endl;
                for (int j = 0; j < 10; j++)
                {
                    strm >> temp;
                    std::cout << temp << " ";
                }
                std::cout << std::endl;
                strm >> vv;
                strm >> datal[0] >> datal[1] >> datal[2] >> datal[3];
                logger << datal[0] << ";" << datal[1] << ";" << datal[2] << ";" << datal[3];
                std::cout << "---------b1:" << datal[0] << " b0:" << datal[1] << " r2:" << datal[2] << " se:" << datal[3] << "\n";
                break;
            }
            std::cout << std::endl;
        }
        Sleep(10);
    }

    return 0;
}