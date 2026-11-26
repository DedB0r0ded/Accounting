// accОunt.cpp
#include "account.h"

namespace accounting {
bool Account::has_valid_type() const {
  return type_ != AccountType::NONE;
}

bool Account::has_valid_currency() const {
  return currency_ != Currency::NONE;
}

bool Account::has_valid_balance() const {
  return balance_ >= 0;
}

bool Account::has_valid_id() const {
  return id_ != 0;
}

// ctors
Account::Account()
    : id_{0},
      currency_{Currency::NONE},
      balance_{0},
      type_{AccountType::NONE},
      flags_{AccountFlags::NONE} {}

Account::Account(id_t id, Currency currency, string name, i32 balance,
                 AccountType type, AccountFlags flags)
    : id_{id},
      currency_{currency},
      name_{name},
      balance_{balance},
      type_{type},
      flags_{flags} {}

Account::Account(const Account& other)
    : id_(other.id_),
      currency_(other.currency_),
      name_(other.name_),
      balance_(other.balance_),
      type_(other.type_),
      flags_(other.flags_),
      mutex_{} {}

Account::Account(Account&& other) noexcept
    : id_(std::exchange(other.id_, 0)),
      currency_(std::exchange(other.currency_, Currency::NONE)),
      name_(std::move(other.name_)),
      balance_(std::exchange(other.balance_, 0)),
      type_(std::exchange(other.type_, AccountType::NONE)),
      flags_(std::exchange(other.flags_, AccountFlags::NONE)) {}

// Comparison ops
bool Account::operator==(const Account& other) const {
  return id_ == other.id_ && currency_ == other.currency_ &&
         name_ == other.name_ && balance_ == other.balance_ &&
         type_ == other.type_ && flags_ == other.flags_;
}

bool Account::operator!=(const Account& other) const {
  return !(*this == other);
}

// Assignment ops
Account& Account::operator=(const Account& other) {
  if (this != &other) {
    id_ = other.id_;
    currency_ = other.currency_;
    name_ = other.name_;
    balance_ = other.balance_;
    type_ = other.type_;
    flags_ = other.flags_;
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
    flags_ = std::exchange(other.flags_, AccountFlags::NONE);
  }
  return *this;
}

// Getters
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

bool Account::is_cancelled() const {
  return bitmask_contains(flags_, AccountFlags::CANCELLED);
}

bool Account::is_valid() const {
  return !is_cancelled() && has_valid_id() && has_valid_balance() &&
         has_valid_currency() && has_valid_type();
}

std::mutex& Account::get_mutex() {
  return mutex_;
}

// Setters
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

// Balance methods
bool Account::increase_balance(i32 amount) {
  if (amount < 0) return false;
  if (amount >= std::numeric_limits<i32>::max()) return false;
  if (amount + balance_ >= std::numeric_limits<i32>::max()) return false;
  if (!is_valid()) return false;
  balance_ += amount;
  return true;
}

bool Account::decrease_balance(i32 amount) {
  if (amount < 0) return false;
  if (amount >= std::numeric_limits<i32>::max()) return false;
  if (!is_valid()) return false;
  if (balance_ < amount) return false;
  balance_ -= amount;
  return true;
}

bool Account::cancel() {
  flags_ = bitmask_join(flags_, AccountFlags::CANCELLED);
  return is_cancelled();
}

// Output op (NOT a json parser)
std::ostream& operator<<(std::ostream& os, const Account& account) {
  os << "Account \"" << account.name_ << "\".\n";
  os << "Id: " << account.id_
     << "; Currency: " << to_full_string(account.currency_) << ";\n";
  os << "Account type: " << to_string(account.type_)
     << "; Balance: " << account.balance_ << ";\n"
     << "Flags: CANCELLED = " << account.is_cancelled()
      ? '1' : '0';
  os << '.';
  return os;
}

} // namespace accounting
