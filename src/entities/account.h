// accОunt.h
#pragma once


#include <common/common.h>


namespace accounting {


  class Account {
  private: 
    id_t id_;
    string name_;
    i32 balance_;
    AccountType type_;
    AccountFlags flags_;
    Currency currency_;

    std::mutex mutex_;

    bool has_valid_type() const;
    bool has_valid_currency() const;
    bool has_valid_balance() const;
    bool has_valid_id() const;

  public:
    // ===== Ctors =====

    Account();
    Account(id_t id, Currency currency, string name, i32 balance,
           AccountType type, AccountFlags flags = AccountFlags::NONE);
    Account(const Account& other);
    Account(Account&& other) noexcept;


    // ===== Comparison =====

    bool operator==(const Account& other) const;
    bool operator!=(const Account& other) const;


    // ===== Assignment =====

    Account& operator=(const Account& other);
    Account& operator=(Account&& other) noexcept;


    // ===== Getters =====

    id_t id() const;
    string name() const;
    i32 balance() const;
    AccountType type() const;
    Currency currency() const;
    bool is_cancelled() const;
    bool is_valid() const;
    std::mutex& get_mutex();


    // ===== Setters =====

    void set_id(id_t value);
    void set_name(string value);
    void set_balance(i32 value);
    void set_type(AccountType value);
    void set_currency(Currency value);


    // ===== Domain =====

    bool increase_balance(i32 amount);
    bool decrease_balance(i32 amount);
    bool cancel();


    /// Output op (NOT a json parser)
    friend std::ostream& operator<<(std::ostream& os, const Account& account);
  };


} // namespace accounting
