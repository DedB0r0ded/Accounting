// json_serializers.h
#pragma once

#include "common/common.h"
#include "entities/account.h"
#include "entities/transfer.h"

using std::declval;
using std::is_same;
using std::void_t;

namespace accounting {

// Enum serialization macros
NLOHMANN_JSON_SERIALIZE_ENUM(AccountType, {{AccountType::NONE, "none"},
                                           {AccountType::PASSIVE, "passive"},
                                           {AccountType::ACTIVE, "active"}})

NLOHMANN_JSON_SERIALIZE_ENUM(Currency, {{Currency::NONE, "none"},
                                        {Currency::USD, "usd"},
                                        {Currency::MYR, "myr"},
                                        {Currency::BYN, "byn"}})

// Validation functions
bool is_valid_json_transfer_state_switch(const nlohmann::json& j);
bool is_valid_json_account(const nlohmann::json& j);
bool is_valid_json_transfer(const nlohmann::json& j);

// TransferStateSwitch serialization
void to_json(nlohmann::json& j, const TransferStateSwitch& state_switch);
void from_json(const nlohmann::json& j, TransferStateSwitch& state_switch);

// TransferState serialization
void to_json(nlohmann::json& j, const TransferState& transfer_state);
void from_json(const nlohmann::json& j, TransferState& transfer_state);

// Account serialization
void to_json(nlohmann::json& j, const Account& obj);
void from_json(const nlohmann::json& j, Account& obj);

// Transfer serialization
void to_json(nlohmann::json& j, const Transfer& obj);
void from_json(const nlohmann::json& j, Transfer& obj);

} // namespace accounting