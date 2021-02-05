#ifndef LOGGER_H
#define LOGGER_H

#ifdef _DEBUG
#include <spdlog/spdlog.h>
#define LOG_ERROR(...) ::spdlog::error(__VA_ARGS__)
#define LOG_WARNING(...) ::spdlog::warn(__VA_ARGS__)
#define LOG_INFO(...) ::spdlog::info(__VA_ARGS__)
#endif // DEBUG

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