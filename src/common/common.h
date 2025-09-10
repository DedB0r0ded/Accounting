// common.h
// Pragmas
#pragma once


// C
#include <ctime>
#include <cmath>

// C++
#include <iostream>
#include <memory>
#include <mutex>
#include <type_traits>
#include <chrono>
#include <string>
#include <vector>

// Libs
#include "nlohmann/json.hpp"


// Defines
#define ACCOUNTING_THREAD_SAFE_TIME


using namespace std::string_literals;


namespace accounting {
// General aliases
template <typename T>
using uptr = std::unique_ptr<T>;

template <typename T>
using sptr = std::shared_ptr<T>;

using std::string;

using std::chrono::steady_clock;
using std::chrono::system_clock;

using optional_tm = std::optional<std::tm>;

using json = nlohmann::json;


// Numeric aliases
using i8 = int8_t;
using i32 = int32_t;

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;

using id_t = uint16_t;
using lid_t = uint64_t;


// Enums
enum class Currency : i8 { NONE = -1, USD, MYR, BYN };

enum class AccountType : i8 {
  NONE = -1,
  PASSIVE = 0,
  ACTIVE = 1
};

enum class AccountFlags : i8 {
  OPENED = ~(1 << 1),
  CANCELLED = 1 << 1
};


// Math
static bool is_close_double(double a, double b, double rel_tol = 1e-6,
                            double abs_tol = 0.0) {
  double a_abs = std::abs(a);
  double b_abs = std::abs(b);
  return std::abs(a - b) <= std::max(rel_tol * std::max(a_abs, b_abs), abs_tol);
}


// Time
static tm to_tm(const time_t& src) {
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

static time_t get_current_time() {
  return system_clock::to_time_t(system_clock::now());
}

static tm get_current_time_tm() {
  return to_tm(get_current_time());
}


// Enum parsing
inline string to_string(Currency currency) {
  switch (currency) {
    case Currency::USD: return "USD";
    case Currency::MYR: return "MYR";
    case Currency::BYN: return "BYN";
    case Currency::NONE: return "NONE";
    default: return "Error. Invalid currency value.";
  }
}

inline string to_full_string(Currency currency) {
  switch (currency) {
    case Currency::USD: return "US Dollars";
    case Currency::MYR: return "Malaysian Ringgits";
    case Currency::BYN: return "Belarussian Rubles";
    case Currency::NONE: return "NO CURRENCY";
    default: return "Error. Invalid currency value.";
  }
}

inline string to_string(AccountType account_type) {
  string account_type_name;
  switch (account_type) {
    case AccountType::PASSIVE: return "Passive";
    case AccountType::ACTIVE: return "Active";
    case AccountType::NONE: return "NONE";
    default: return "Error. Invalid account type value.";
  }
  return account_type_name;
}
} // namespace accounting