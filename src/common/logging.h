#pragma once

#include "common/common.h"

namespace accounting {
  using log_str = const std::string&;


enum class LogLevel {
  DEBUG,
  INFO,
  WARNING,
  ERROR,
  CRITICAL,
};

constexpr bool operator>(LogLevel left, LogLevel right) {
  return static_cast<int>(left) > static_cast<int>(right);
}

constexpr bool operator>=(LogLevel left, LogLevel right) {
  return static_cast<int>(left) >= static_cast<int>(right);
}

constexpr bool operator<(LogLevel left, LogLevel right) {
  return static_cast<int>(left) < static_cast<int>(right);
}

constexpr bool operator<=(LogLevel left, LogLevel right) {
  return static_cast<int>(left) <= static_cast<int>(right);
}

constexpr bool operator==(LogLevel left, LogLevel right) {
  return static_cast<int>(left) == static_cast<int>(right);
}

constexpr bool operator!=(LogLevel left, LogLevel right) {
  return static_cast<int>(left) != static_cast<int>(right);
}


enum class SinkType {
  CONSOLE,
  FILE
};


class Logger {
 private:
  std::string buffer_;
  std::ostream file_;
  SinkType type_;
  
 public:
  const std::string& buffer() const { return buffer_; }
  const std::ostream& file() const { return file_; }
  const SinkType& type() const { return type_; }

  void flush_buffer();
  void clear_log();
  void log(log_str);
};


class LogScope {
 private:
  Logger& logger_;
  string prefix_;
  LogLevel level_;
  bool is_active_;

 public:
  void debug(log_str msg);
  void info(log_str msg);
  void warning(log_str msg);
  void error(log_str msg);
  void critical(log_str msg);

  string timestamp(void);
  
  LogScope(Logger&, LogLevel);
  ~LogScope();

  bool is_alive() const { return is_active_; }
  const string& prefix() const { return prefix_; }
  };
}