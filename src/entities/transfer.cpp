// transfer.cpp
#include "transfer.h"

namespace accounting {

// =====Private methods
Currency Transfer::debit_currency() const {
  return debit_account_->currency();
}

Currency Transfer::credit_currency() const {
  return credit_account_->currency();
}

void Transfer::calc_and_reset_conversion_rate() {
  conversion_rate_ = debit_amount_ / credit_amount_;
}

bool Transfer::debit_equals_credit() const {
  return debit_amount_ == credit_amount_;
}

bool Transfer::same_currency_used() const {
  return debit_currency() == credit_currency();
}

bool Transfer::validate_conversion_rate() const {
  double actual_rate =
      static_cast<double>(debit_amount_) / static_cast<double>(credit_amount_);
  return is_close_double(conversion_rate_, actual_rate, 1e-4);
}

bool Transfer::any_value_is_null() const {
  if (id_ == 0) return true;
  if (date_time_ == std::nullopt) return true;
  if (debit_account_ == nullptr) return true;
  if (credit_account_ == nullptr) return true;
  if (debit_amount_ == 0 || credit_amount_ == 0) return true;
  if (debit_currency() == Currency::NONE) return true;
  if (credit_currency() == Currency::NONE) return true;
  return false;
}

bool Transfer::validate_transfer() {
  if (any_value_is_null()) {
    err_msg_ = "Some value is null or undefined.";
    return false;
  }
  bool dr_equals_cr = debit_equals_credit();
  bool same_currency = same_currency_used();
  if (dr_equals_cr && same_currency) return true;
  if (dr_equals_cr) {
    err_msg_ = "Debit and credit are equal, but have different currencies";
    return false;
  }
  if (same_currency) {
    err_msg_ = "Debit and credit are not equal.";
    return false;
  }
  if (!validate_conversion_rate()) {
    err_msg_ = "Invalid conversion rate.";
    return false;
  }
  return true;
}

void Transfer::update_validity() {
  state_switch_.set_validated(validate_transfer());
}

bool Transfer::decrease_credit_account() {
  return credit_account_->decrease_balance(credit_amount_);
}

void Transfer::rollback_credit_decrease() {
  credit_account_->increase_balance(credit_amount_);
}

bool Transfer::increase_debit_account() {
  return debit_account_->increase_balance(debit_amount_);
}

void Transfer::rollback_debit_increase() {
  debit_account_->decrease_balance(debit_amount_);
}

bool Transfer::transfer_money() {
  state_switch_.set_started(true);
  if (!decrease_credit_account()) {
    state_switch_.set_interrupted(true);
    return false;
  }
  state_switch_.set_credit_decreased(true);
  if (!increase_debit_account()) {
    state_switch_.set_interrupted(true);
    return false;
  }
  state_switch_.set_debit_increased(true);
  return true;
}

// =====Constructors
Transfer::Transfer() noexcept
    : id_{0},
      date_time_{},
      conversion_rate_{0.0},
      debit_account_{nullptr},
      debit_amount_{0},
      credit_account_{nullptr},
      credit_amount_{0} {}

Transfer::Transfer(lid_t id, const tm& date_time, double conversion_rate,
                   sptr<Account> debit_account, i32 debit_amount,
                   sptr<Account> credit_account, i32 credit_amount) noexcept
    : id_{id},
      date_time_{date_time},
      conversion_rate_{conversion_rate},
      debit_account_{debit_account},
      debit_amount_{debit_amount},
      credit_account_{credit_account},
      credit_amount_{credit_amount} {
  state_switch_.reset();
  update_validity();
}

Transfer::Transfer(lid_t id, const tm& date_time, sptr<Account> debit_account,
                   i32 debit_amount, sptr<Account> credit_account,
                   i32 credit_amount) noexcept
    : Transfer(id, date_time, 0.0, debit_account, debit_amount, credit_account,
               credit_amount) {
  calc_and_reset_conversion_rate();
  update_validity();
}

Transfer::Transfer(lid_t id, const tm& date_time, sptr<Account> debit_account,
                   sptr<Account> credit_account, i32 amount) noexcept
    : Transfer(id, date_time, debit_account, amount, credit_account, amount) {}

// =====Getters
lid_t Transfer::id() const {
  return id_;
}

optional_tm Transfer::date_time() const {
  return date_time_;
}

double Transfer::conversion_rate() const {
  return conversion_rate_;
}

bool Transfer::is_valid() const {
  return state_switch_.is_validated();
}

TransferStateSwitch Transfer::state_switch() const {
  return state_switch_;
}

TransferState Transfer::state() const {
  return state_switch_.get_state();
}

const string& Transfer::err_msg() const {
  return err_msg_;
}

const sptr<Account> Transfer::debit_account() const {
  return debit_account_;
}

i32 Transfer::debit_amount() const {
  return debit_amount_;
}

const sptr<Account> Transfer::credit_account() const {
  return credit_account_;
}

i32 Transfer::credit_amount() const {
  return credit_amount_;
}

// =====Setters
void Transfer::set_id(const lid_t& id) {
  id_ = id;
}

void Transfer::set_date_time(const optional_tm& date_time) {
  date_time_ = date_time;
}

void Transfer::set_conversion_rate(double rate) {
  conversion_rate_ = rate;
}

void Transfer::set_state_switch(const TransferStateSwitch& state_switch) {
  state_switch_ = state_switch;
}

void Transfer::set_err_msg(const string& msg) {
  err_msg_ = msg;
}

void Transfer::set_debit_account(const Account& account) {
  *debit_account_ = account;
} // add null-check

void Transfer::set_debit_amount(i32 amount) {
  debit_amount_ = amount;
}

void Transfer::set_credit_account(const Account& account) {
  *credit_account_ = account;
} // add null-check

void Transfer::set_credit_amount(i32 amount) {
  credit_amount_ = amount;
}

// =====Main method
bool Transfer::commit() {
  update_validity();
  if (!state_switch_.is_validated()) return false;
  std::mutex& dr_mtx = debit_account_->get_mutex();
  std::mutex& cr_mtx = credit_account_->get_mutex();
  std::lock(dr_mtx, cr_mtx);
  std::lock_guard<std::mutex> dr_lock(dr_mtx, std::adopt_lock);
  std::lock_guard<std::mutex> cr_lock(cr_mtx, std::adopt_lock);
  if (transfer_money())
    state_switch_.set_finished(true);
  else {
    if (state_switch_.was_interrupted() && state_switch_.was_debit_increased())
      rollback_debit_increase();
    if (state_switch_.was_interrupted() && state_switch_.was_credit_decreased())
      rollback_credit_decrease();
    state_switch_.reset();
    return false;
  }
  return true;
}

} // namespace accounting