// json_serializers.cpp
#include "json_serializers.h"

#include <sstream>

// Validations currently check only the presence of all fields
// TODO: Add value validation for Transfer and Account, maybe for
// TransferStateSwitch 
// Create tests
namespace accounting {

bool has_all_fields(const nlohmann::json& j,
                    std::initializer_list<const char*> fields) {
  for (auto field : fields)
    if (!j.contains(field)) return false;
  return true;
}


// Unable to use tm directly, because nlohmann::json is trying to find parser inside the `std` namespace instead of `accounting`.
// Using custom DateTime struct instead
void to_json(nlohmann::json& j, const tm& t) {
  j = to_string(t);
}

void from_json(const nlohmann::json& j, tm& t) {
  // TODO: FINISH. ADD OPT VALIDATION
  // TODO: ADD UTC-MAKER TO COMMON.H
  t = from_string(j).value();
}


// std::optional<tm> or optional_tm
void to_json(nlohmann::json& j, const optional_tm& ot) {
  if (ot == std::nullopt) {
    j = JSON_NULL;
    return;
  }
  j = to_string(ot.value());
}

void from_json(const nlohmann::json& j, optional_tm& ot) {
  ot = from_string(j);
}


// TransferStateSwitch
bool is_valid_json_transfer_state_switch(const nlohmann::json& j) {
  bool has_all =
      has_all_fields(j, {JSON_TRANSFER_STATE_SWITCH_VALIDATED_KEY,
                         JSON_TRANSFER_STATE_SWITCH_STARTED_KEY,
                         JSON_TRANSFER_STATE_SWITCH_CREDIT_DECREASED_KEY,
                         JSON_TRANSFER_STATE_SWITCH_DEBIT_INCREASED_KEY,
                         JSON_TRANSFER_STATE_SWITCH_FINISHED_KEY,
                         JSON_TRANSFER_STATE_SWITCH_INTERRUPTED_KEY});
  return has_all;
}

void to_json(nlohmann::json& j, const TransferStateSwitch& state_switch) {
  j = {{JSON_TRANSFER_STATE_SWITCH_VALIDATED_KEY, state_switch.is_validated()},
       {JSON_TRANSFER_STATE_SWITCH_STARTED_KEY, state_switch.is_started()},
       {JSON_TRANSFER_STATE_SWITCH_CREDIT_DECREASED_KEY,
        state_switch.was_credit_decreased()},
       {JSON_TRANSFER_STATE_SWITCH_DEBIT_INCREASED_KEY,
        state_switch.was_debit_increased()},
       {JSON_TRANSFER_STATE_SWITCH_FINISHED_KEY, state_switch.is_finished()},
       {JSON_TRANSFER_STATE_SWITCH_INTERRUPTED_KEY,
        state_switch.was_interrupted()}};
}

void from_json(const nlohmann::json& j, TransferStateSwitch& state_switch) {
  if (!is_valid_json_transfer_state_switch(j)) {
    state_switch.reset();
    return;
  }
  state_switch.set_validated(
      j.at(JSON_TRANSFER_STATE_SWITCH_VALIDATED_KEY).get<bool>());
  state_switch.set_started(
      j.at(JSON_TRANSFER_STATE_SWITCH_STARTED_KEY).get<bool>());
  state_switch.set_credit_decreased(
      j.at(JSON_TRANSFER_STATE_SWITCH_CREDIT_DECREASED_KEY).get<bool>());
  state_switch.set_debit_increased(
      j.at(JSON_TRANSFER_STATE_SWITCH_DEBIT_INCREASED_KEY).get<bool>());
  state_switch.set_finished(
      j.at(JSON_TRANSFER_STATE_SWITCH_FINISHED_KEY).get<bool>());
  state_switch.set_interrupted(
      j.at(JSON_TRANSFER_STATE_SWITCH_INTERRUPTED_KEY).get<bool>());
}


// TransferState. Constructs TransferStateSwitch before parsing
void to_json(nlohmann::json& j, const TransferState& transfer_state) {
  const auto state_switch = TransferStateSwitch(transfer_state);
  to_json(j, state_switch);
}

void from_json(const nlohmann::json& j, TransferState& transfer_state) {
  auto state_switch = TransferStateSwitch(transfer_state);
  from_json(j, state_switch);
  transfer_state = state_switch.get_state();
}


// Account
bool is_valid_json_account(const nlohmann::json& j) {
  bool has_all = has_all_fields(
      j, {JSON_ACCOUNT_ID_KEY, JSON_ACCOUNT_NAME_KEY, JSON_ACCOUNT_BALANCE_KEY,
          JSON_ACCOUNT_TYPE_KEY, JSON_ACCOUNT_CURRENCY_KEY});
  return has_all;
}

void to_json(nlohmann::json& j, const Account& obj) {
  if (obj.type() == AccountType::NONE) {
    j = JSON_NULL;
    return;
  }
  j = {{JSON_ACCOUNT_ID_KEY, obj.id()},
       {JSON_ACCOUNT_NAME_KEY, obj.name()},
       {JSON_ACCOUNT_BALANCE_KEY, obj.balance()},
       {JSON_ACCOUNT_TYPE_KEY, obj.type()},
       {JSON_ACCOUNT_CURRENCY_KEY, obj.currency()}};
}

void from_json(const nlohmann::json& j, Account& obj) {
  if (!is_valid_json_account(j)) {
    obj.set_id(-1);
    obj.set_type(AccountType::NONE);
    return;
  }
  obj.set_id(j.at(JSON_ACCOUNT_ID_KEY).get<id_t>());
  obj.set_name(j.at(JSON_ACCOUNT_NAME_KEY).get<string>());
  obj.set_balance(j.at(JSON_ACCOUNT_BALANCE_KEY).get<i32>());
  obj.set_type(j.at(JSON_ACCOUNT_TYPE_KEY).get<AccountType>());
  obj.set_currency(j.at(JSON_ACCOUNT_CURRENCY_KEY).get<Currency>());
}


// Transfer validation & parsing
bool is_valid_json_transfer(const nlohmann::json& j) {
  bool has_all = has_all_fields(
      j, {JSON_TRANSFER_ID_KEY, JSON_TRANSFER_DATE_TIME_KEY,
          JSON_TRANSFER_CONVERSION_RATE_KEY, JSON_TRANSFER_STATE_KEY,
          JSON_TRANSFER_ERR_MSG_KEY, JSON_TRANSFER_DEBIT_ACCOUNT_KEY,
          JSON_TRANSFER_DEBIT_AMOUNT_KEY, JSON_TRANSFER_CREDIT_ACCOUNT_KEY,
          JSON_TRANSFER_CREDIT_AMOUNT_KEY});
  return has_all;
}

void to_json(nlohmann::json& j, const Transfer& obj) {
  j = {{JSON_TRANSFER_ID_KEY, obj.id()},
       {JSON_TRANSFER_DATE_TIME_KEY, obj.date_time()},
       {JSON_TRANSFER_CONVERSION_RATE_KEY, obj.conversion_rate()},
       {JSON_TRANSFER_STATE_KEY, obj.state_switch()},
       {JSON_TRANSFER_ERR_MSG_KEY, obj.err_msg()},
       {JSON_TRANSFER_DEBIT_ACCOUNT_KEY, 
    obj.debit_account() ? *(obj.debit_account()) : Account()},
       {JSON_TRANSFER_DEBIT_AMOUNT_KEY, obj.debit_amount()},
       {JSON_TRANSFER_CREDIT_ACCOUNT_KEY, 
    obj.credit_account() ? *(obj.credit_account()) : Account()},
       {JSON_TRANSFER_CREDIT_AMOUNT_KEY, obj.credit_amount()}};
}

void from_json(const nlohmann::json& j, Transfer& obj) {
  if (!is_valid_json_transfer(j)) {
    return;
  }
  obj.set_id(j.at(JSON_TRANSFER_ID_KEY).get<lid_t>());
  obj.set_date_time(j.at(JSON_TRANSFER_DATE_TIME_KEY).get<optional_tm>());
  obj.set_conversion_rate(
      j.at(JSON_TRANSFER_CONVERSION_RATE_KEY).get<double>());
  obj.set_state_switch(
      j.at(JSON_TRANSFER_STATE_KEY).get<TransferStateSwitch>());
  obj.set_err_msg(j.at(JSON_TRANSFER_ERR_MSG_KEY).get<string>());
  obj.set_debit_account(j.at(JSON_TRANSFER_DEBIT_ACCOUNT_KEY).get<Account>());
  obj.set_debit_amount(
      j.at(JSON_TRANSFER_DEBIT_AMOUNT_KEY).get<accounting::lid_t>());
  obj.set_credit_account(j.at(JSON_TRANSFER_CREDIT_ACCOUNT_KEY).get<Account>());
  obj.set_credit_amount(j.at(JSON_TRANSFER_CREDIT_AMOUNT_KEY).get<lid_t>());
}

} // namespace accounting