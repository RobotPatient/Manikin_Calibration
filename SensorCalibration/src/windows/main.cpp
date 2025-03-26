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
#include "statemachine.hpp"

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

    StateMachine stateMachine(argv[1]);
    stateMachine.run();

    return 0;
}