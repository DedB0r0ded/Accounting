// strings.h
#pragma once


// Enums
#define ERROR_CURRENCY_INVALID "Error. Invalid currency value."

#define CURRENCY_SHORT_USD "USD"
#define CURRENCY_SHORT_MYR "MYR"
#define CURRENCY_SHORT_BYN "BYN"
#define CURRENCY_SHORT_NONE "none"

#define CURRENCY_FULL_USD "US Dollars"
#define CURRENCY_FULL_MYR "Malaysian Ringgits"
#define CURRENCY_FULL_BYN "Belarussian Rubles"
#define CURRENCY_FULL_NONE "No currency"

#define ERROR_ACCOUNT_TYPE_INVALID "Error. Invalid account type value."

#define ACCOUNT_TYPE_PASSIVE "passive"
#define ACCOUNT_TYPE_ACTIVE "active"
#define ACCOUNT_TYPE_NONE "none"

// JSON
#define JSON_NULL "null"

#define JSON_ACCOUNT_ID_KEY "id"
#define JSON_ACCOUNT_NAME_KEY "name"
#define JSON_ACCOUNT_BALANCE_KEY "balance"
#define JSON_ACCOUNT_TYPE_KEY "type"
#define JSON_ACCOUNT_CURRENCY_KEY "currency"

#define JSON_TRANSFER_STATE_SWITCH_VALIDATED_KEY "validated"
#define JSON_TRANSFER_STATE_SWITCH_STARTED_KEY "started"
#define JSON_TRANSFER_STATE_SWITCH_CREDIT_DECREASED_KEY "credit_decreased"
#define JSON_TRANSFER_STATE_SWITCH_DEBIT_INCREASED_KEY "debit_increased"
#define JSON_TRANSFER_STATE_SWITCH_FINISHED_KEY "finished"
#define JSON_TRANSFER_STATE_SWITCH_INTERRUPTED_KEY "interrupted"

#define JSON_TRANSFER_ID_KEY "id"
#define JSON_TRANSFER_DATE_TIME_KEY "date_time"
#define JSON_TRANSFER_CONVERSION_RATE_KEY "conversion_rate"
#define JSON_TRANSFER_STATE_KEY "state"
#define JSON_TRANSFER_ERR_MSG_KEY "err_msg"
#define JSON_TRANSFER_DEBIT_ACCOUNT_KEY "debit_account"
#define JSON_TRANSFER_DEBIT_AMOUNT_KEY "debit_amount"
#define JSON_TRANSFER_CREDIT_ACCOUNT_KEY "credit_account"
#define JSON_TRANSFER_CREDIT_AMOUNT_KEY "credit_amount"

