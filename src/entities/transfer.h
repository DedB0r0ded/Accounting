// transfer.h
#pragma once

#include "common/common.h"
#include "entities/account.h"
#include "entities/transfer_state_switch.h"

namespace accounting {
class Transfer {
 private:
  lid_t id_;
  optional_tm date_time_;
  double conversion_rate_; // debit_amount_ / credit_amount_

  TransferStateSwitch state_switch_;
  string err_msg_;

  sptr<Account> debit_account_;
  i32 debit_amount_;
  Currency debit_currency() const;

  sptr<Account> credit_account_;
  i32 credit_amount_;
  Currency credit_currency() const;

  // Private methods
  void calc_and_reset_conversion_rate();
  bool debit_equals_credit() const;
  bool same_currency_used() const;
  bool validate_conversion_rate() const;
  bool any_value_is_null() const;
  bool validate_transfer();
  void update_validity();
  bool decrease_credit_account();
  void rollback_credit_decrease();
  bool increase_debit_account();
  void rollback_debit_increase();
  bool transfer_money();

 public:
  // Constructors
  Transfer() noexcept;
  Transfer(lid_t id, const tm& date_time, double conversion_rate,
           sptr<Account> debit_account, i32 debit_amount,
           sptr<Account> credit_account, i32 credit_amount) noexcept;
  Transfer(lid_t id, const tm& date_time, sptr<Account> debit_account,
           i32 debit_amount, sptr<Account> credit_account,
           i32 credit_amount) noexcept;
  Transfer(lid_t id, const tm& date_time, sptr<Account> debit_account,
           sptr<Account> credit_account, i32 amount) noexcept;

  // Getters
  lid_t id() const;
  optional_tm date_time() const;
  double conversion_rate() const;
  bool is_valid() const;
  TransferStateSwitch state_switch() const;
  TransferState state() const;
  const string& err_msg() const;
  const sptr<Account> debit_account() const;
  i32 debit_amount() const;
  const sptr<Account> credit_account() const;
  i32 credit_amount() const;

  // Setters
  void set_id(const lid_t& id);
  void set_date_time(const optional_tm& date_time);
  void set_conversion_rate(double rate);
  void set_state_switch(const TransferStateSwitch& state_switch);
  void set_err_msg(const string& msg);
  void set_debit_account(const Account& account);
  void set_debit_amount(i32 amount);
  void set_credit_account(const Account& account);
  void set_credit_amount(i32 amount);

  // Main method
  bool commit();
};
} // namespace accounting