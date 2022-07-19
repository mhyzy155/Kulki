#ifndef KULKI_LOGGER_HPP
#define KULKI_LOGGER_HPP

//#define DEBUG

#include <iostream>

enum class LoggerMode {
  debug,
  info,
  warning,
  error
};

class Logger {
 public:
  static constexpr void log(const std::string& message, const LoggerMode mode = LoggerMode::debug);
};

constexpr void Logger::log(const std::string& message, const LoggerMode mode) {
  switch (mode) {
    case LoggerMode::debug:
#ifdef DEBUG
      std::cout << "[DEBUG]" << message << '\n';
#endif
      break;
    case LoggerMode::info:
      std::cout << "\x1b[37m [INFO]" << message << "\x1B[0m\n";
      break;
    case LoggerMode::warning:
      std::cout << "\x1b[33m [WARN]" << message << "\x1B[0m\n";
      break;
    case LoggerMode::error:
      std::cout << "\x1b[31m[ERROR]" << message << "\x1B[0m\n";
      break;
  }
}

#endif