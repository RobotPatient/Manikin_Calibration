#include "windowsConfigManager.hpp"

windowsConfigManager::windowsConfigManager(const std::string &filePath) : _filePath{filePath}
{
}

windowsConfigManager::windowsConfigManager()
{
}

windowsConfigManager::~windowsConfigManager()
{
}

void windowsConfigManager::setFilePath(const std::string &filePath)
{
    _filePath = filePath;
}

std::string windowsConfigManager::readString(const std::string &section, const std::string &key, const std::string &defaultValue)
{
    char buffer[256];
    GetPrivateProfileString(section.c_str(), key.c_str(), defaultValue.c_str(), buffer, sizeof(buffer), _filePath.c_str());
    return std::string(buffer);
}

int windowsConfigManager::readInt(const std::string &section, const std::string &key, int defaultValue)
{
    return GetPrivateProfileInt(section.c_str(), key.c_str(), defaultValue, _filePath.c_str());
}

void windowsConfigManager::writeString(const std::string &section, const std::string &key, const std::string &value)
{
    WritePrivateProfileString(section.c_str(), key.c_str(), value.c_str(), _filePath.c_str());
}

void windowsConfigManager::writeInt(const std::string &section, const std::string &key, int value)
{
    WritePrivateProfileString(section.c_str(), key.c_str(), std::to_string(value).c_str(), _filePath.c_str());
}
