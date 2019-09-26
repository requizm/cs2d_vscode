#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <stdlib.h>

class Logger
{
private:
    /* data */
    const std::string currentDateTime();
    static std::ofstream outfile;

public:
    Logger();
    ~Logger();

    static void DebugLog(std::string msg);
    static void WriteLog(std::string msg);
    static void Start();
    static void Stop();
};

#endif