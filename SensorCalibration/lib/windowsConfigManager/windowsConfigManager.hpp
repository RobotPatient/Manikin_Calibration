#ifndef WINDOWSCONFIGMANAGER_HPP
#define WINDOWSCONFIGMANAGER_HPP

#include <windows.h>
#include <iostream>
#include <fstream>

class windowsConfigManager
{
private:
    OPENFILENAME fileName;
    HWND hwnd = nullptr;
    HANDLE hFile;
    std::string _filePath;

public:
    windowsConfigManager(const std::string &filePath);
    windowsConfigManager();
    ~windowsConfigManager();

    void setFilePath(const std::string &filePath);

    std::string readString(const std::string &section, const std::string &key, const std::string &defaultValue);

    int readInt(const std::string &section, const std::string &key, int defaultValue);

    void writeString(const std::string &section, const std::string &key, const std::string &value);

    void writeInt(const std::string &section, const std::string &key, int value);
};

#endif