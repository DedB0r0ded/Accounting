// file_reposotpry.cpp
#include "file_repository.h"

#include "files/file.h"

namespace accounting {
FileRepository::FileRepository(std::string accounts_path,
                               std::string transfers_path)
    : accounts_path_{accounts_path}, transfers_path_{transfers_path} {}

FileRepository::FileRepository() : FileRepository("", "") {}

void FileRepository::save_accounts(const std::vector<Account>& accounts) {
  File<Account> file(accounts_path_);
  file.write(accounts);
}

std::vector<Account> FileRepository::load_accounts(void) {
  File<Account> file(accounts_path_);
  return file.read_all();
}

void FileRepository::save_transfers(const std::vector<Transfer>& transfers) {
  File<Transfer> file(transfers_path_);
  file.write(transfers);
}

std::vector<Transfer> FileRepository::load_transfers(void) {
  File<Transfer> file(transfers_path_);
  return file.read_all();
}
} // namespace accounting