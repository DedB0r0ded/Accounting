//date_time.h
#pragma once


#include "./time.h"


namespace accounting {

class DateTime {
  optional_tm value_;

public:
  // Ctors
  DateTime() = default;

  explicit DateTime(const tm& t) { value_ = optional_tm(t); }

  explicit DateTime(const optional_tm& t) { value_ = t; }

  DateTime(const DateTime& other) = default;

  DateTime(DateTime&& other) noexcept = default;


  // Assign ops
  DateTime& operator=(const tm& t) {
    value_ = t;
    return *this;
  }

  DateTime& operator=(const optional_tm& t) { 
    value_ = t;
    return *this;
  }

  DateTime& operator=(const DateTime& other) = default;

  DateTime& operator=(DateTime&& other) noexcept = default;


  // Getters

  // might trow an exception if value was nullopt
  constexpr const tm& value(void) const { return value_.value(); }

  constexpr bool is_null(void) const noexcept {
    return !value_.has_value();
  }

  string to_string(void) const {
    return value_ ? accounting::to_string(*value_) : JSON_NULL;
  }


  // Other methods
  void reset(void) { value_ = std::nullopt; }

  friend std::ostream& operator<<(std::ostream& os, const DateTime& dt) {
    if (dt.is_null())
      return os << JSON_NULL;
    else
      return os << accounting::to_string(*dt.value_);
  }
};

} // namespace accounting