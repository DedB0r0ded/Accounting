// transfer_state_switch.h
#pragma once
#include "common/common.h"

namespace accounting {
enum class TransferState : i8 {
  NONE = 0,

  VALIDATED = 1 << 0,
  STARTED = 1 << 1,
  CREDIT_DECREASED = 1 << 2,
  DEBIT_INCREASED = 1 << 3,
  FINISHED = 1 << 4,
  INTERRUPTED = 1 << 5,

  NOT_VALIDATED = ~(1 << 0),
  NOT_STARTED = ~(1 << 1),
  CREDIT_NOT_DECREASED = ~(1 << 2),
  DEBIT_NOT_INCREASED = ~(1 << 3),
  NOT_FINISHED = ~(1 << 4),
  NOT_INTERRUPTED = ~(1 << 5)
};


// Bitwise operators for flags
TransferState operator|(TransferState a, TransferState b);
TransferState& operator|=(TransferState& a, TransferState b);
TransferState operator&(TransferState a, TransferState b);
TransferState& operator&=(TransferState& a, TransferState b);


class TransferStateSwitch {
 private:
  TransferState state_;

 public:
  // Constructors
  TransferStateSwitch();
  TransferStateSwitch(TransferState state);
  TransferStateSwitch(const TransferStateSwitch& other);


  // Assigning operator
  TransferStateSwitch& operator=(const TransferStateSwitch other);


  // Methods for different states
  void set_validated(bool val);
  bool is_validated() const;

  void set_started(bool val);
  bool is_started() const;

  void set_credit_decreased(bool val);
  bool was_credit_decreased() const;

  void set_debit_increased(bool val);
  bool was_debit_increased() const;

  void set_finished(bool val);
  bool is_finished() const;

  void set_interrupted(bool val);
  bool was_interrupted() const;

  
  // Composite state checks
  bool is_completed() const;
  bool is_in_progress() const;
  bool is_pending() const;


  // General state management
  void reset();
  TransferState get_state() const;
  void set_state(TransferState state);
};
}  // namespace accounting