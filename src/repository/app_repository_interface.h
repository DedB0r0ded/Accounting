#pragma once

#include "common/common.h"
#include "entities/account.h"
#include "entities/transfer.h"

namespace accounting {
class AppRepository {
 public:
  virtual ~AppRepository() = default;
  virtual void save_accounts(const std::vector<Account>& accounts) = 0;
  virtual std::vector<Account> load_accounts(void) = 0;
  virtual void save_transfers(const std::vector<Transfer>& transfers) = 0;
  virtual std::vector<Transfer> load_transfers(void) = 0;
};
} // namespace accounting