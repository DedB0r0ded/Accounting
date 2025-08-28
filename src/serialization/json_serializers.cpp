// json_serializers.cpp
#include "json_serializers.h"

namespace accounting {

bool is_valid_json_transfer_state_switch(const nlohmann::json& j) {
  if (j.contains("validated") && j.contains("started") &&
      j.contains("credit_decreased") && j.contains("debit_increase") &&
      j.contains("currency"))
    return true;
  return false;
}

bool is_valid_json_account(const nlohmann::json& j) {
  if (j.contains("id") && j.contains("name") && j.contains("balance") &&
      j.contains("type") && j.contains("currency"))
    return true;
  return false;
}

bool is_valid_json_transfer(const nlohmann::json& j) {
  if (j.contains("id") && j.contains("date_time") &&
      j.contains("conversion_rate") && j.contains("state") &&
      j.contains("err_msg") && j.contains("debit_account") &&
      j.contains("debit_amount") && j.contains("credit_account") &&
      j.contains("credit_amount"))
    return true;
  return false;
}


void to_json(nlohmann::json& j, const TransferStateSwitch& state_switch) {
  j = {{"validated", state_switch.is_validated()},
       {"started", state_switch.is_started()},
       {"credit_decreased", state_switch.was_credit_decreased()},
       {"debit_increased", state_switch.was_debit_increased()},
       {"finished", state_switch.is_finished()},
       {"interrupted", state_switch.was_interrupted()}};
}

void from_json(const nlohmann::json& j, TransferStateSwitch& state_switch) {
  if (!is_valid_json_transfer_state_switch(j)) {
    state_switch.reset();
    return;
  }
  state_switch.set_validated(j.at("validated").get<bool>());
  state_switch.set_started(j.at("started").get<bool>());
  state_switch.set_credit_decreased(j.at("credit_decreased").get<bool>());
  state_switch.set_debit_increased(j.at("debit_increased").get<bool>());
  state_switch.set_finished(j.at("finished").get<bool>());
  state_switch.set_interrupted(j.at("interrupted").get<bool>());
}


void to_json(nlohmann::json& j, const TransferState& transfer_state) {
  const auto state_switch = TransferStateSwitch(transfer_state);
  to_json(j, state_switch);
}

void from_json(const nlohmann::json& j, TransferState& transfer_state) {
  auto state_switch = TransferStateSwitch(transfer_state);
  from_json(j, state_switch);
  transfer_state = state_switch.get_state();
}


void to_json(nlohmann::json& j, const Account& obj) {
  j = {{"id", obj.id()},
       {"name", obj.name()},
       {"balance", obj.balance()},
       {"type", obj.type()},
       {"currency", obj.currency()}};
}

void from_json(const nlohmann::json& j, Account& obj) {
  if (!is_valid_json_account(j)) {
    obj.set_id(-1);
    obj.set_type(AccountType::NONE);
    return;
  }
  obj.set_id(j.at("id").get<id_t>());
  obj.set_name(j.at("name").get<string>());
  obj.set_balance(j.at("balance").get<i32>());
  obj.set_type(j.at("type").get<AccountType>());
  obj.set_currency(j.at("currency").get<Currency>());
}


void to_json(nlohmann::json& j, const Transfer& obj) {
  j = {{"id", obj.id()},
       //{"date_time", obj.date_time().value()},
       {"conversion_rate", obj.conversion_rate()},
       {"state", obj.state_switch()},
       {"err_msg", obj.err_msg()},
       {"debit_account", *(obj.debit_account())},
       {"debit_amount", obj.debit_amount()},
       {"credit_account", *(obj.credit_account())},
       {"credit_amount", obj.credit_amount()}};
}

void from_json(const nlohmann::json& j, Transfer& obj) {
  if (!is_valid_json_transfer(j)) {
    return;
  }
  obj.set_id(j.at("id").get<lid_t>());
  // obj.set_date_time(j.at("id").get<tm>());
  obj.set_conversion_rate(j.at("conversion_rate").get<double>());
  obj.set_state_switch(j.at("state").get<TransferStateSwitch>());
  obj.set_err_msg(j.at("err_msg").get<string>());
  obj.set_debit_account(j.at("debit_account").get<Account>());
  obj.set_debit_amount(j.at("debit_amount").get<accounting::lid_t>());
  obj.set_credit_account(j.at("credit_account").get<Account>());
  obj.set_credit_amount(j.at("credit_amount").get<lid_t>());
}

}  // namespace accounting