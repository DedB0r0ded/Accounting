// time.h
#pragma once


#include <ctime>

#include <string>
#include <sstream>
#include <iomanip>

#include "./aliases.h"


namespace accounting {

// TODO:
// add tests for all functions;

// UTC/GMT
inline tm to_tm_utc(const time_t& src) {
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

inline time_t get_current_time_utc() noexcept {
  return system_clock::to_time_t(system_clock::now());
}

inline tm get_current_time_tm_utc() noexcept {
  return to_tm_utc(get_current_time_utc());
}


// Local
inline tm to_tm(const time_t& src) {
#ifdef ACCOUNTING_THREAD_SAFE_TIME
  tm result{};
#ifdef _WIN32
  localtime_s(&result, &src);
#else
  localtime_r(&src, &result);
#endif
  return result;
#else
  return *std::localtime(&src);
#endif
}

inline time_t get_current_time() noexcept {
  return system_clock::to_time_t(system_clock::now());
}

inline tm get_current_time_tm() noexcept {
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