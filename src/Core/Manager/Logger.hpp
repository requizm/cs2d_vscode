#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#define LOG_ERROR(...) ::spdlog::error(__VA_ARGS__)
#define LOG_WARNING(...) ::spdlog::warn(__VA_ARGS__)
#define LOG_INFO(...) ::spdlog::info(__VA_ARGS__)
#define WRITE_ERROR(...) ::spdlog::get("write_logger")->error(__VA_ARGS__)
#define WRITE_WARNING(...) ::spdlog::get("write_logger")->warn(__VA_ARGS__)
#define WRITE_INFO(...) ::spdlog::get("write_logger")->info(__VA_ARGS__)

class Logger {
   public:
    Logger();
    ~Logger();
    static void StopApp();
    static void StartApp();
};

#endif  // LOGGER_H