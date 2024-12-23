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
#include "cncControl.hpp"

#define DEFAULT_LOG_DIR "C:"

struct sampleData
{
    unsigned int sampleNumber;
    std::vector<double> fingerPositionValues;
    int loadCellValue;
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path to config.ini>" << std::endl;
        return 1;
    }

    std::string configFilePath = argv[1];

    windowsSerial uart;
    CNCController cnc("COM8");
    windowsConfigManager config(configFilePath);
    int portNumber;
    std::string logDir = config.readString("Settings", "LogDir", DEFAULT_LOG_DIR);

    windowsLogger logger(logDir);

    std::string portName = config.readString("Settings", "Port", "ERROR");
    std::cout << "Port from settings: " << portName << std::endl;
    uart.setNewPort(portName);

    if (!uart.configureSerialPort())
    {
        return 1;
    }

    std::string writeb1 = config.readString("Reference_sensor", "b1", "0");
    std::string writeb0 = config.readString("Reference_sensor", "b0", "0");
    std::string writeSampleSize = config.readString("Reference_sensor", "SampleSize", "5");
    std::cout << "b1: " << writeb1 << ", b0: " << writeb0 << ", n: " << writeSampleSize << std::endl;
    uart.writeToSerialPort(writeb1 + " " + writeb0 + " " + writeSampleSize + "\n");
    uart.serialToCout();
    uart.serialToCout();

    // cnc.moveToHomePosition();

    while (true)
    {
        // std::cout << "Measurement ready... (enter)";
        // getchar();
        // std::cout << std::endl;
        uart.writeToSerialPort("\n");

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
            logger << data.sampleNumber << " ";
            std::cout << " LoadCell data: " << data.loadCellValue << " FingerPosition data:";
            logger << data.loadCellValue;
            for (int i = 0; i < data.fingerPositionValues.size(); i++)
            {
                std::cout << " " << i << "=" << data.fingerPositionValues.at(i);
                logger << " " << data.fingerPositionValues.at(i);
            }
            // std::cout << std::endl;
            logger << "\n";
        }

        int i = 0;
        std::string datal[4];
        int channel;
        std::string temp, CC;
        if (i = receivedData.find('C') != std::string::npos && !receivedData.empty())
        {
            size_t pos = receivedData.find('\n');
            std::string newData = receivedData.substr(pos + 1);
            // std::cout << "\n NEWDATA: " << newData;

            std::istringstream strm2(newData);
            std::cout << std::endl;
            for (int k = 0; k < 8; k++)
            {
                strm2 >> CC >> channel;
                strm2 >> datal[0] >> datal[1] >> datal[2] >> datal[3];
                logger << channel << " " << datal[0] << " " << datal[1] << " " << datal[2] << " " << datal[3] << "\n";
                std::cout << "Channel: " << channel << " b1:" << datal[0] << " b0:" << datal[1] << " r2:" << datal[2] << " se:" << datal[3] << std::endl;
            }
            break;
        }
        std::cout << std::endl;
        cnc.moveRelativeZ(-0.1);
        Sleep(1000);
    }
    cnc.moveRelativeZ(1.0);            // move the cnc back
    uart.writeToSerialPort("RESET\n"); // reset the arduino
    return 0;
}