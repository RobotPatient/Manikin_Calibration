#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "windowsSerial.hpp"
#include "windowsConfigManager.hpp"
#include "windowsLogger.hpp"
#include "cncControl.hpp"

#define DEFAULT_LOG_DIR "C:"

enum class State
{
    INITIALIZATION,
    SETUP,
    POSITIONING,
    SAMPLING,
    LOGGING,
    CLEANUP,
    DONE
};

struct SampleData
{
    unsigned int sampleNumber;
    std::vector<double> fingerPositionValues;
    int loadCellValue;
};

class StateMachine
{
public:
    StateMachine(const std::string &configFilePath)
        : config(configFilePath),
          logger(config.readString("Settings", "LogDir", DEFAULT_LOG_DIR)),
          uart(config.readString("Settings", "Port", "ERROR"), config.readInt("Settings", "BaudRate", 0)),
          cnc(config.readString("cnc_settings", "Port", "ERROR"), config.readInt("cnc_settings", "BaudRate", 0)),
          currentState(State::INITIALIZATION),
          position(0),
          samples(0) {}

    void run();

private:
    windowsConfigManager config;
    windowsLogger logger;
    windowsSerial uart;
    CNCController cnc;
    State currentState;
    int position;
    int samples;
    SampleData data;

    void processState();

    void performSampling();
    bool parseSampleData(const std::string &receivedData, SampleData &data);
    void logSampleData();
};