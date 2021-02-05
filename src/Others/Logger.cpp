#include "Logger.hpp"

Logger::Logger()
{
}

Logger::~Logger()
{
}

std::ofstream Logger::outfile;

void Logger::WriteLog(const std::string &msg)
{
    /*auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    char *time = std::ctime(&end_time);
    Logger::outfile << "time: " << time << "message: " << msg << "\n\n";*/
}

void Logger::StopApp()
{
    Logger::outfile.close();
}

void Logger::StartApp()
{
    Logger::outfile.open("log.txt");
}
