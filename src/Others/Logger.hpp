#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#define LOG_ERROR(...) ::spdlog::error(__VA_ARGS__)
#define LOG_WARNING(...) ::spdlog::warn(__VA_ARGS__)
#define LOG_INFO(...) ::spdlog::info(__VA_ARGS__)
#define WRITE_ERROR(...) ::Logger

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <stdlib.h>

class Logger
{
private:
    const std::string currentDateTime();
    static std::ofstream outfile;

public:
    Logger();
    ~Logger();

    static void WriteLog(const std::string &msg);
    static void StopApp();
    static void StartApp();
};

#endif // LOGGER_H