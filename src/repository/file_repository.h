//file_repository.h
#pragma once


#include "common/common.h"
#include "entities/account.h"
#include "entities/transfer.h"
#include "app_repository_interface.h"
#include "files/file.h"


namespace accounting {
class FileRepository final : public AppRepository {
 private:
  std::string accounts_path_;
  std::string transfers_path_;


 public:
  FileRepository(std::string accounts_path, std::string transfers_path); // Сделать значение по умолчанию
  FileRepository();


  bool accounts_file_exists(void) {
    return File<Account>(accounts_path_).file_exists();
  }
  void save_accounts(const std::vector<Account>& accounts) override;
  std::vector<Account> load_accounts(void) override;

  
  bool transfers_file_exists(void) {
    return File<Transfer>(transfers_path_).file_exists();
  }
  void save_transfers(const std::vector<Transfer>& transfers) override;
  std::vector<Transfer> load_transfers(void) override;
};
}  // namespace accounting