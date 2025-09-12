// enums.h
#pragma once


#include "./aliases.h"


namespace accounting {

// Enums
enum class Currency : i8 { NONE = -1, USD, MYR, BYN };

enum class AccountType : i8 { NONE = -1, PASSIVE = 0, ACTIVE = 1 };

enum class AccountFlags : i8 { OPENED = ~(1 << 1), CANCELLED = 1 << 1 };


// Enum parsing
constexpr std::string_view to_string(const Currency currency) {
  switch (currency) {
    case Currency::USD:
      return CURRENCY_SHORT_USD;
    case Currency::MYR:
      return CURRENCY_SHORT_MYR;
    case Currency::BYN:
      return CURRENCY_SHORT_BYN;
    case Currency::NONE:
      return CURRENCY_SHORT_NONE;
    default:
      return ERROR_CURRENCY_INVALID;
  }
}

constexpr std::string_view to_full_string(const Currency currency) {
  switch (currency) {
    case Currency::USD:
      return CURRENCY_FULL_USD;
    case Currency::MYR:
      return CURRENCY_FULL_MYR;
    case Currency::BYN:
      return CURRENCY_FULL_BYN;
    case Currency::NONE:
      return CURRENCY_FULL_NONE;
    default:
      return ERROR_CURRENCY_INVALID;
  }
}

constexpr std::string_view to_string(const AccountType account_type) {
  switch (account_type) {
    case AccountType::PASSIVE:
      return ACCOUNT_TYPE_PASSIVE;
    case AccountType::ACTIVE:
      return ACCOUNT_TYPE_ACTIVE;
    case AccountType::NONE:
      return ACCOUNT_TYPE_NONE;
    default:
      return ERROR_ACCOUNT_TYPE_INVALID;
  }
}

} // namespace accounting