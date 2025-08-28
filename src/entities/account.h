// account.h
#pragma once

#include "common/common.h"

namespace accounting {
class Account {
 private:
  id_t id_;
  Currency currency_;
  string name_;
  i32 balance_;
  AccountType type_;
  std::mutex mutex_;

 public:
  // ������������
  Account();
  Account(id_t id, Currency currency, string name, i32 balance,
          AccountType type);
  Account(const Account& other);
  Account(Account&& other) noexcept;

  // ��������� ���������
  bool operator==(const Account& other) const;
  bool operator!=(const Account& other) const;

  // ��������� ������������
  Account& operator=(const Account& other);
  Account& operator=(Account&& other) noexcept;

  // �������
  id_t id() const;
  Currency currency() const;
  string name() const;
  i32 balance() const;
  AccountType type() const;
  std::mutex& get_mutex();

  // �������
  void set_id(id_t value);
  void set_currency(Currency value);
  void set_name(string value);
  void set_balance(i32 value);
  void set_type(AccountType value);

  // ������ ��� ������ � ��������
  bool increase_balance(i32 amount);
  bool decrease_balance(i32 amount);

  // �������� ������
  friend std::ostream& operator<<(std::ostream& os, const Account& account);
};
}  // namespace accounting