#pragma once

#include "common/common.h"

namespace accounting {

enum class LogLevel {
  DEBUG,
  INFO,
  WARNING,
  ERROR,
  CRITICAL
};


class Logger {
 private:
  std::string buffer_;
  std::filesystem::path path_;

  
 public:
  const std::string& buffer() { return buffer_; }
  const std::filesystem::path& path() { return path_; }


  void clear_log();
  void log(string);
  void flush_buffer();
};


class LogScope {
 private:
  Logger& logger_;
  LogLevel level_;
  bool is_alive_;
  void set_up(void);
  void tear_down(void);


 public:
  void debug(string msg);
  void info(string msg);
  void warning(string msg);
  void error(string msg);
  
  
  LogScope();
  ~LogScope();


  bool is_alive() const { return is_alive_; }
  };
}