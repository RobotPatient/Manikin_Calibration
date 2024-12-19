#ifndef WINDOWSLOGGER_HPP
#define WINDOWSLOGGER_HPP

#include <fstream>

class windowsLogger
{
private:
    std::ofstream *_outFile;
    std::string _directory;

public:
    windowsLogger(const std::string &directory, bool createFile = true);
    ~windowsLogger();
    void createFile();

    void addDataToFile(std::string &newData);

    template <typename T>
    windowsLogger &operator<<(const T &newData)
    {
        if (_outFile && _outFile->is_open())
        {
            (*_outFile) << newData;
        }
        return *this;
    }

protected:
    std::string createFileName();
};

#endif