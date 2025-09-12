// account.h
#pragma once

#include "common/common.h"

namespace accounting {
class Account {
 private: // fields
  id_t id_;
  string name_;
  i32 balance_;
  AccountType type_;
  Currency currency_;
  std::mutex mutex_;

 public:
  // Ctors
  Account();
  Account(id_t id, Currency currency, string name, i32 balance,
          AccountType type);
  Account(const Account& other);
  Account(Account&& other) noexcept;

  // Comparison ops
  bool operator==(const Account& other) const;
  bool operator!=(const Account& other) const;

  // Assignment ops
  Account& operator=(const Account& other);
  Account& operator=(Account&& other) noexcept;

  // Getters
  id_t id() const;
  string name() const;
  i32 balance() const;
  AccountType type() const;
  Currency currency() const;
  std::mutex& get_mutex();

  // Setters
  void set_id(id_t value);
  void set_name(string value);
  void set_balance(i32 value);
  void set_type(AccountType value);
  void set_currency(Currency value);

  // Balance methods
  bool increase_balance(i32 amount);
  bool decrease_balance(i32 amount);

  // Output op (NOT a json parser)
  friend std::ostream& operator<<(std::ostream& os, const Account& account);
};
} // namespace accounting