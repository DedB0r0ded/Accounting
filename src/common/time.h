#pragma once


#include <ctime>

#include <string>
#include <chrono>

#include "./aliases.h"


namespace accounting {

// Time
// TODO:
// add tests for all functions;
inline tm to_tm(const time_t& src) {
#ifdef ACCOUNTING_THREAD_SAFE_TIME
  tm result{};
#ifdef _WIN32
  gmtime_s(&result, &src);
#else
  gmtime_r(&src, &result);
#endif
  return result;
#else
  return *std::gmtime(&src);
#endif
}

inline time_t get_current_time() {
  return system_clock::to_time_t(system_clock::now());
}

inline tm get_current_time_tm() {
  return to_tm(get_current_time());
}

// tm <-> ISO8601 parsing
inline string to_string(const tm& t) {
  std::ostringstream oss;
  oss << std::put_time(&t, "%Y-%m-%dT%H-%M-%SZ");
  return oss.str();
}

inline optional_tm from_string(const string& s) {
  tm t{};
  std::istringstream iss(s);
  iss >> std::get_time(&t, "%Y-%m-%dT%H-%M-%SZ");
  if (iss.fail()) {
    return std::nullopt;
  }
  return t;
}
} // namespace accounting