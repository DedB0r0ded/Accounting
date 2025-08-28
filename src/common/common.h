//common.h
#pragma once

#include "nlohmann/json.hpp"

#include <type_traits>

#include <memory>
#include <mutex>

#include <iostream>
#include <string>

#include <chrono>
#include <ctime>

#include <cmath>
#include <vector>


using namespace std::string_literals;


namespace accounting {
    template<typename T>
    using uptr = std::unique_ptr<T>;

    template<typename T>
    using sptr = std::shared_ptr<T>;

    using std::cout, std::cin;
    using std::string;

    using std::chrono::steady_clock;
    using std::chrono::system_clock;

    using i8 = int8_t;
    using i32 = int32_t;

    using u8 = uint8_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    using id_t = uint16_t;
    using lid_t = uint64_t;

    using opt_tm = std::optional<tm>;

    using json = nlohmann::json;


    enum class Currency : i8 {
        NONE = -1,
        USD,
        MYR,
        BYN
    };

    enum class AccountType : i8 {
        NONE = -1,
        PASSIVE = 0,
        ACTIVE = 1
    };


    static bool is_close_double(double a, double b, double rel_tol = 1e-6, double abs_tol = 0.0) {
        double a_abs = std::abs(a);
        double b_abs = std::abs(b);
        return std::abs(a - b) <= std::max(rel_tol * std::max(a_abs, b_abs), abs_tol);
    }


    static tm* to_tm(const time_t& src) {
        tm* res = new tm;
        *res = *std::gmtime(&src);
        return res;
    }

    static time_t get_current_time() {
        auto now = system_clock::now();
        time_t cnow = system_clock::to_time_t(now);
        return cnow;
    }

    static uptr<tm> get_current_time_tm() {
        time_t now = get_current_time();
        auto now_tm = uptr<tm>(to_tm(now));
        *now_tm = *std::gmtime(&now);
        return now_tm;
    }


    static string get_currency_name(Currency currency) {
        string currency_name;
        switch (currency) {
        case Currency::USD:
            currency_name = "USD";
            break;
        case Currency::MYR:
            currency_name = "MYR";
            break;
        case Currency::BYN:
            currency_name = "BYN";
            break;
        case Currency::NONE:
            currency_name = "NONE";
            break;
        default:
            currency_name = "Error. Invalid currency value.";
            break;
        }
        return currency_name;
    }

    static string get_currency_full_name(Currency currency) {
        string currency_name;
        switch (currency) {
        case Currency::USD:
            currency_name = "US Dollars";
            break;
        case Currency::MYR:
            currency_name = "Malaysian Ringgits";
            break;
        case Currency::BYN:
            currency_name = "Belarussian Rubles";
            break;
        case Currency::NONE:
            currency_name = "NO CURRENCY";
            break;
        default:
            currency_name = "Error. Invalid currency value.";
            break;
        }
        return currency_name;
    }

    static string get_account_type_name(AccountType account_type) {
        string account_type_name;
        switch (account_type) {
        case AccountType::PASSIVE:
            account_type_name = "Passive";
            break;
        case AccountType::ACTIVE:
            account_type_name = "Active";
            break;
        case AccountType::NONE:
            account_type_name = "NONE";
            break;
        default:
            account_type_name = "Error. Invalid account type value.";
            break;
        }
        return account_type_name;
    }
}