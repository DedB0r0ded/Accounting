// strings.h
#pragma once


#include "./cpp_version.h"


#if CPP_VERSION >= 17
using string_const = std::string_view;
#else
using string_const = const char*;
#endif


// Enums

constexpr string_const ERROR_CURRENCY_INVALID = "Error. Invalid currency value.";

constexpr string_const CURRENCY_SHORT_USD = "USD";
constexpr string_const CURRENCY_SHORT_MYR = "MYR";
constexpr string_const CURRENCY_SHORT_BYN = "BYN";
constexpr string_const CURRENCY_SHORT_NONE = "none";

constexpr string_const CURRENCY_FULL_USD = "US Dollars";
constexpr string_const CURRENCY_FULL_MYR = "Malaysian Ringgits";
constexpr string_const CURRENCY_FULL_BYN = "Belarussian Rubles";
constexpr string_const CURRENCY_FULL_NONE = "No currency";

constexpr string_const ERROR_ACCOUNT_TYPE_INVALID =
    "Error. Invalid account type value.";

constexpr string_const ACCOUNT_TYPE_PASSIVE = "passive";
constexpr string_const ACCOUNT_TYPE_ACTIVE = "active";
constexpr string_const ACCOUNT_TYPE_NONE = "none";


// JSON

constexpr string_const JSON_NULL = "null";

constexpr string_const JSON_ACCOUNT_ID_KEY = "id";
constexpr string_const JSON_ACCOUNT_NAME_KEY = "name";
constexpr string_const JSON_ACCOUNT_BALANCE_KEY = "balance";
constexpr string_const JSON_ACCOUNT_TYPE_KEY = "type";
constexpr string_const JSON_ACCOUNT_CURRENCY_KEY = "currency";

constexpr string_const JSON_TRANSFER_STATE_SWITCH_VALIDATED_KEY = "validated";
constexpr string_const JSON_TRANSFER_STATE_SWITCH_STARTED_KEY = "started";
constexpr string_const JSON_TRANSFER_STATE_SWITCH_CREDIT_DECREASED_KEY =
    "credit_decreased";
constexpr string_const JSON_TRANSFER_STATE_SWITCH_DEBIT_INCREASED_KEY =
    "debit_increased";
constexpr string_const JSON_TRANSFER_STATE_SWITCH_FINISHED_KEY = "finished";
constexpr string_const JSON_TRANSFER_STATE_SWITCH_INTERRUPTED_KEY =
    "interrupted";

constexpr string_const JSON_TRANSFER_ID_KEY = "id";
constexpr string_const JSON_TRANSFER_DATE_TIME_KEY = "date_time";
constexpr string_const JSON_TRANSFER_CONVERSION_RATE_KEY = "conversion_rate";
constexpr string_const JSON_TRANSFER_STATE_KEY = "state";
constexpr string_const JSON_TRANSFER_ERR_MSG_KEY = "err_msg";
constexpr string_const JSON_TRANSFER_DEBIT_ACCOUNT_KEY = "debit_account";
constexpr string_const JSON_TRANSFER_DEBIT_AMOUNT_KEY = "debit_amount";
constexpr string_const JSON_TRANSFER_CREDIT_ACCOUNT_KEY = "credit_account";
constexpr string_const JSON_TRANSFER_CREDIT_AMOUNT_KEY = "credit_amount";


// Files