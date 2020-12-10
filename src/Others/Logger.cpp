#include "Logger.hpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>

Logger::Logger()
{
}

Logger::~Logger() = default;

std::ofstream Logger::outfile;

void Logger::DebugLog(const std::string &msg)
{
    auto start = std::chrono::system_clock::now();
    // Some computation here
    auto end = std::chrono::system_clock::now();

    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    char *time = std::ctime(&end_time);

    std::cout << "time: " << time << "message: " << msg << "\n\n\n";
}
/*
void Logger::DebugLog(bool msg)
{
    auto start = std::chrono::system_clock::now();
    // Some computation here
    auto end = std::chrono::system_clock::now();

    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    char *time = std::ctime(&end_time);

    std::string res = msg ? "true" : "false";

    std::cout << "time: " << time << "message: " << res << "\n\n\n";
}*/

void Logger::WriteLog(const std::string &msg)
{
    Start();
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    char *time = std::ctime(&end_time);
    Logger::outfile << "time: " << time << "message: " << msg << "\n\n";
    Stop();
}

void Logger::Start()
{
    Logger::outfile.open("log.txt", std::ofstream::out | std::ofstream::app);
}

void Logger::Stop()
{
    Logger::outfile.close();
}

void Logger::StartApp()
{
    Logger::outfile.open("log.txt");
    Logger::outfile.close();
}
