#include "windowsLogger.hpp"
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <chrono>
#include <iomanip>

windowsLogger::windowsLogger(const std::string &directory, bool createFile) : _directory{directory}
{
    if (!createFile)
    {
        return;
    }
    const std::string filePath = directory + createFileName();
    _outFile = new std::ofstream(filePath);
    std::cout << filePath.c_str() << std::endl;
    if (!_outFile->is_open())
    {
        std::cerr << "Error: File creation failed in constructor" << std::endl;
    }
}

windowsLogger::~windowsLogger()
{
    if (_outFile->is_open())
    {
        _outFile->close();
    }
    delete _outFile;
}

void windowsLogger::createFile()
{
    if (_outFile->is_open())
    {
        std::cerr << "Error: A file is already open" << std::endl;
        return;
    }
    _outFile = new std::ofstream(_directory + createFileName());
}

void windowsLogger::addDataToFile(std::string &newData)
{
    if (!_outFile->is_open())
    {
        std::cerr << "Error: File does not exist" << std::endl;
    }
    *_outFile << newData;
}

std::string windowsLogger::createFileName()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm *now_tm = std::localtime(&now_time);
    std::ostringstream format_time;
    format_time << std::put_time(now_tm, "%Y-%m-%d_%H-%M-%S");
    return "data" + format_time.str() + ".log";
}