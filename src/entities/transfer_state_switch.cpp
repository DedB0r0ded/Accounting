// transfer_state_switch.cpp
#include "transfer_state_switch.h"

namespace accounting {

// Bitwise operators for flags
TransferState operator|(TransferState a, TransferState b) {
  return static_cast<TransferState>(static_cast<i8>(a) | static_cast<i8>(b));
}

TransferState& operator|=(TransferState& a, TransferState b) {
  a = a | b;
  return a;
}

TransferState operator&(TransferState a, TransferState b) {
  return static_cast<TransferState>(static_cast<i8>(a) & static_cast<i8>(b));
}

TransferState& operator&=(TransferState& a, TransferState b) {
  a = a & b;
  return a;
}

// Constructors
TransferStateSwitch::TransferStateSwitch() : state_{TransferState::NONE} {}

TransferStateSwitch::TransferStateSwitch(TransferState state) : state_{state} {}

TransferStateSwitch::TransferStateSwitch(const TransferStateSwitch& other)
    : state_{other.state_} {}

// Assignment operator
TransferStateSwitch& TransferStateSwitch::operator=(
    const TransferStateSwitch other) {
  state_ = other.state_;
  return *this;
}

// Methods for VALIDATED state
void TransferStateSwitch::set_validated(bool val) {
  if (val)
    state_ |= TransferState::VALIDATED;
  else
    state_ &= TransferState::NOT_VALIDATED;
}

bool TransferStateSwitch::is_validated() const {
  return (state_ & TransferState::VALIDATED) == TransferState::VALIDATED;
}

// Methods for STARTED state
void TransferStateSwitch::set_started(bool val) {
  if (val)
    state_ |= TransferState::STARTED;
  else
    state_ &= TransferState::NOT_STARTED;
}

bool TransferStateSwitch::is_started() const {
  return (state_ & TransferState::STARTED) == TransferState::STARTED;
}

// Methods for CREDIT_DECREASED state
void TransferStateSwitch::set_credit_decreased(bool val) {
  if (val)
    state_ |= TransferState::CREDIT_DECREASED;
  else
    state_ &= TransferState::CREDIT_NOT_DECREASED;
}

bool TransferStateSwitch::was_credit_decreased() const {
  return (state_ & TransferState::CREDIT_DECREASED) ==
         TransferState::CREDIT_DECREASED;
}

// Methods for DEBIT_INCREASED state
void TransferStateSwitch::set_debit_increased(bool val) {
  if (val)
    state_ |= TransferState::DEBIT_INCREASED;
  else
    state_ &= TransferState::DEBIT_NOT_INCREASED;
}

bool TransferStateSwitch::was_debit_increased() const {
  return (state_ & TransferState::DEBIT_INCREASED) ==
         TransferState::DEBIT_INCREASED;
}

// Methods for FINISHED state
void TransferStateSwitch::set_finished(bool val) {
  if (val)
    state_ |= TransferState::FINISHED;
  else
    state_ &= TransferState::NOT_FINISHED;
}

bool TransferStateSwitch::is_finished() const {
  return (state_ & TransferState::FINISHED) == TransferState::FINISHED;
}

// Methods for INTERRUPTED state
void TransferStateSwitch::set_interrupted(bool val) {
  if (val)
    state_ |= TransferState::INTERRUPTED;
  else
    state_ &= TransferState::NOT_INTERRUPTED;
}

bool TransferStateSwitch::was_interrupted() const {
  return (state_ & TransferState::INTERRUPTED) == TransferState::INTERRUPTED;
}

// Composite state checks
bool TransferStateSwitch::is_completed() const {
  const TransferState completed_state =
      TransferState::VALIDATED | TransferState::STARTED |
      TransferState::CREDIT_DECREASED | TransferState::DEBIT_INCREASED |
      TransferState::FINISHED;

  return (state_ & completed_state) == completed_state;
}

bool TransferStateSwitch::is_in_progress() const {
  return is_started() && !is_finished() && !was_interrupted();
}

bool TransferStateSwitch::is_pending() const {
  return is_validated() && !is_started();
}

// General state management
void TransferStateSwitch::reset() {
  state_ = TransferState::NONE;
}

TransferState TransferStateSwitch::get_state() const {
  return state_;
}

void TransferStateSwitch::set_state(TransferState state) {
  state_ = state;
}

} // namespace accounting