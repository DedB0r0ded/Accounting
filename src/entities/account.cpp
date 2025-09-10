// account.cpp
#include "account.h"

namespace accounting {

Account::Account()
    : id_{0},
      currency_{Currency::NONE},
      balance_{0},
      type_{AccountType::NONE} {}

Account::Account(id_t id, Currency currency, string name, i32 balance,
                 AccountType type)
    : id_{id},
      currency_{currency},
      name_{name},
      balance_{balance},
      type_{type} {}

Account::Account(const Account& other)
    : id_(other.id_),
      currency_(other.currency_),
      name_(other.name_),
      balance_(other.balance_),
      type_(other.type_),
      mutex_{} {}

Account::Account(Account&& other) noexcept
    : id_(std::exchange(other.id_, 0)),
      currency_(std::exchange(other.currency_, Currency::NONE)),
      name_(std::move(other.name_)),
      balance_(std::exchange(other.balance_, 0)),
      type_(std::exchange(other.type_, AccountType::NONE)) {}

bool Account::operator==(const Account& other) const {
  return id_ == other.id_ && currency_ == other.currency_ &&
         name_ == other.name_ && balance_ == other.balance_ &&
         type_ == other.type_;
}

bool Account::operator!=(const Account& other) const {
  return !(*this == other);
}

Account& Account::operator=(const Account& other) {
  if (this != &other) {
    id_ = other.id_;
    currency_ = other.currency_;
    name_ = other.name_;
    balance_ = other.balance_;
    type_ = other.type_;
  }
  return *this;
}

Account& Account::operator=(Account&& other) noexcept {
  if (this != &other) {
    id_ = std::exchange(other.id_, 0);
    currency_ = std::exchange(other.currency_, Currency::NONE);
    name_ = std::move(other.name_);
    balance_ = std::exchange(other.balance_, 0);
    type_ = std::exchange(other.type_, AccountType::NONE);
  }
  return *this;
}

id_t Account::id() const {
  return id_;
}

Currency Account::currency() const {
  return currency_;
}

string Account::name() const {
  return name_;
}

i32 Account::balance() const {
  return balance_;
}

AccountType Account::type() const {
  return type_;
}

std::mutex& Account::get_mutex() {
  return mutex_;
}

void Account::set_id(id_t value) {
  id_ = value;
}

void Account::set_currency(Currency value) {
  currency_ = value;
}

void Account::set_name(string value) {
  name_ = value;
}

void Account::set_balance(i32 value) {
  balance_ = value;
}

void Account::set_type(AccountType value) {
  type_ = value;
}

bool Account::increase_balance(i32 amount) {
  balance_ += amount;
  return true;
}

bool Account::decrease_balance(i32 amount) {
  if (balance_ < amount) return false;
  balance_ -= amount;
  return true;
}

std::ostream& operator<<(std::ostream& os, const Account& account) {
  os << "Account \"" << account.name_ << "\".\n";
  os << "Id: " << account.id_
     << "; Currency: " << to_full_string(account.currency_) << ";\n";
  os << "Account type: " << to_string(account.type_)
     << "; Balance:" << account.balance_;
  return os;
}

} // namespace accounting