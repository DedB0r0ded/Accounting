#pragma once


#include "./aliases.h"


namespace accounting {

// Enums
enum class Currency : i8 { NONE = -1, USD, MYR, BYN };

enum class AccountType : i8 { NONE = -1, PASSIVE = 0, ACTIVE = 1 };

enum class AccountFlags : i8 { OPENED = ~(1 << 1), CANCELLED = 1 << 1 };


// Enum parsing
inline string to_string(Currency currency) {
  switch (currency) {
    case Currency::USD:
      return "USD";
    case Currency::MYR:
      return "MYR";
    case Currency::BYN:
      return "BYN";
    case Currency::NONE:
      return "NONE";
    default:
      return "Error. Invalid currency value.";
  }
}

inline string to_full_string(Currency currency) {
  switch (currency) {
    case Currency::USD:
      return "US Dollars";
    case Currency::MYR:
      return "Malaysian Ringgits";
    case Currency::BYN:
      return "Belarussian Rubles";
    case Currency::NONE:
      return "NO CURRENCY";
    default:
      return "Error. Invalid currency value.";
  }
}

inline string to_string(AccountType account_type) {
  string account_type_name;
  switch (account_type) {
    case AccountType::PASSIVE:
      return "Passive";
    case AccountType::ACTIVE:
      return "Active";
    case AccountType::NONE:
      return "NONE";
    default:
      return "Error. Invalid account type value.";
  }
  return account_type_name;
}

} // namespace accounting