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
#define ACCOUNTING_SAFE_TIME


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
#ifdef ACCOUNTING_SAFE_TIME
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
static string to_string(Currency currency) {
  string currency_name;
  switch (currency) {
    case Currency::USD:
      currency_name = "USD";
      break;
    case Currency::MYR:
      currency_name = "MYR";
      break;
    case Currency::BYN:
      currency_name = "BYN";
      break;
    case Currency::NONE:
      currency_name = "NONE";
      break;
    default:
      currency_name = "Error. Invalid currency value.";
      break;
  }
  return currency_name;
}

static string to_full_string(Currency currency) {
  string currency_name;
  switch (currency) {
    case Currency::USD:
      currency_name = "US Dollars";
      break;
    case Currency::MYR:
      currency_name = "Malaysian Ringgits";
      break;
    case Currency::BYN:
      currency_name = "Belarussian Rubles";
      break;
    case Currency::NONE:
      currency_name = "NO CURRENCY";
      break;
    default:
      currency_name = "Error. Invalid currency value.";
      break;
  }
  return currency_name;
}

static string to_string(AccountType account_type) {
  string account_type_name;
  switch (account_type) {
    case AccountType::PASSIVE:
      account_type_name = "Passive";
      break;
    case AccountType::ACTIVE:
      account_type_name = "Active";
      break;
    case AccountType::NONE:
      account_type_name = "NONE";
      break;
    default:
      account_type_name = "Error. Invalid account type value.";
      break;
  }
  return account_type_name;
}
} // namespace accounting