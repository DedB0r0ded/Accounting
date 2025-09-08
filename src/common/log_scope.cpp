#include "logging.h"

namespace accounting {
  void LogScope::debug(log_str msg) {
    // call logger with debug level
    // log scope prefix and msg
  }

  void LogScope::info(log_str msg) {

  }

  void LogScope::warning(log_str msg) {

  }

  void LogScope::error(log_str msg) {

  }

  void LogScope::critical(log_str msg) {

  }

  LogScope::LogScope(Logger& logger, LogLevel level = LogLevel::DEBUG)
      : logger_{logger}, level_{level} {
    // log creation with timestamp and prefix
    string msg = '[' + prefix_ + "][" + timestamp() + ']';
    msg = msg + " <<< Log start.";
    logger_.log(msg);
    is_active_ = true;
  }

  LogScope::~LogScope() {
    is_active_ = false;
    string msg = '[' + prefix_ + "][" + timestamp() + ']';
    msg += " <<< Log end.";
    logger_.log(msg);
  }
  }