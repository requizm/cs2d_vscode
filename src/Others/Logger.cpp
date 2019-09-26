#include "Logger.h"
#include <iostream>
#include <chrono>
#include <ctime>

Logger::Logger()
{
}

Logger::~Logger() = default;

std::ofstream Logger::outfile;

void Logger::DebugLog(std::string msg)
{
    auto start = std::chrono::system_clock::now();
    // Some computation here
    auto end = std::chrono::system_clock::now();

    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    char *time = std::ctime(&end_time);

    std::cout << "time: " << time << "message: " << msg << "\n\n\n";
}

void Logger::WriteLog(std::string msg)
{
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    char *time = std::ctime(&end_time);
    Logger::outfile << "time: " << time << "message: " << msg << "\n\n";
}

void Logger::Start()
{
    Logger::outfile.open("log.txt");
}

void Logger::Stop()
{
    Logger::outfile.close();
}
