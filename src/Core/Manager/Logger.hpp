#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#define LOG_ERROR(...) ::spdlog::error(__VA_ARGS__)
#define LOG_WARNING(...) ::spdlog::warn(__VA_ARGS__)
#define LOG_INFO(...) ::spdlog::info(__VA_ARGS__)
#define WRITE_ERROR(...) ::spdlog::get("write_logger")->error(__VA_ARGS__)
#define WRITE_WARNING(...) ::spdlog::get("write_logger")->warn(__VA_ARGS__)
#define WRITE_INFO(...) ::spdlog::get("write_logger")->info(__VA_ARGS__)

#if defined(_DEBUG)
    #define ASSERTM_ERROR(condition, message)\
   (!(condition)) ?\
      (std::cerr << "ERROR: Assertion failed: (" << #condition << "), "\
      << "function " << __FUNCTION__\
      << ", file " << __FILE__\
      << ", line " << __LINE__ << "."\
      << std::endl << message << std::endl, abort(), 0) : 1
    #define ASSERT_ERROR(condition)\
   (!(condition)) ?\
      (std::cerr << "ERROR: Assertion failed: (" << #condition << "), "\
      << "function " << __FUNCTION__\
      << ", file " << __FILE__\
      << ", line " << __LINE__ << "."\
      << std::endl, abort(), 0) : 1
    #define ASSERTM_WARNING(condition, message)\
   (!(condition)) ?\
      (std::cout << "WARNING: Assertion failed: (" << #condition << "), "\
      << "function " << __FUNCTION__\
      << ", file " << __FILE__\
      << ", line " << __LINE__ << "."\
      << std::endl << message << std::endl, abort(), 0) : 1
    #define ASSERT_WARNING(condition)\
   (!(condition)) ?\
      (std::cout << "WARNING: Assertion failed: (" << #condition << "), "\
      << "function " << __FUNCTION__\
      << ", file " << __FILE__\
      << ", line " << __LINE__ << "."\
      << std::endl, 0) : 1
#else
    #define ASSERTM_ERROR(condition, message)\
   (!(condition)) ?\
      (WRITE_ERROR(message)\
      abort(), 0) : 1
    #define ASSERT_ERROR(condition)\
   (!(condition)) ?\
      (abort(), 0) : 1
    #define ASSERTM_WARNING(condition, message)\
   (!(condition)) ?\
      (WRITE_WARNING(message)\
      0) : 1
    #define ASSERT_WARNING(condition)\
   (!(condition)) ?\
      (0) : 1
#endif

class Logger
{
   public:
    Logger() = default;
    ~Logger() = default;
    static void StopApp();
    static void StartApp();
};

#endif  // LOGGER_H