#include "common.h"

namespace accounting {
string to_string(Currency currency) {
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

string to_full_string(Currency currency) {
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

string to_string(AccountType account_type) {
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