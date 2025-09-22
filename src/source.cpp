#include <iostream>

#include "common/common.h"
#include "entities/account.h"
#include "entities/transfer.h"
#include "repository/file_repository.h"

#ifdef _WIN32
#include "windows.h"
#endif

using namespace accounting;

// TODO: refactor
std::vector<Account> static create_account_vec() {
  return std::vector<Account>();
}

std::vector<Transfer> static create_transfer_vec() {
  return std::vector<Transfer>();
}

int try_exec() {
  try {
    // Create two vectors
    auto accounts = create_account_vec();
    auto transfers = create_transfer_vec();

    // Init file repository
    FileRepository file_repo("accounts.json", "transfers.json");
    // Load accounts from file
    if (file_repo.accounts_file_exists()) accounts = file_repo.load_accounts();
    // Load transfers from file (NOT WORKING. TODO: refactor load)
    if (file_repo.transfers_file_exists())
    transfers = file_repo.load_transfers();
    // Output
    for (auto acc : accounts) std::cout << json(acc) << '\n';
    for (auto tr : transfers) std::cout << json(tr) << '\n';

    // Create test accounts
    Account account1 =
        Account(1, Currency::USD, "Alice Savings", 1000, AccountType::PASSIVE);
    Account account2 =
        Account(2, Currency::USD, "Bob Checking", 500, AccountType::ACTIVE);

    // Add test accounts to `accounts_ptr`
    accounts.push_back(account1);
    accounts.push_back(account2);

    // Get current time as C-like tm struct
    tm current_time = get_current_time_tm();
    std::cout << current_time.tm_year << '.' << current_time.tm_mon << '.'
              << current_time.tm_mday << '\n';

    // Create transfer
    Transfer transfer(1, current_time, std::make_shared<Account>(account1), 200,
                      std::make_shared<Account>(account2), 200);

    // Commit transfer
    if (transfer.commit()) {
      std::cout << "\nПеревод выполнен успешно!\n";
    } else {
      std::cout << "\nОшибка перевода: " << transfer.err_msg() << "\n";
    }
    json jt;
    to_json(jt, transfer);
    std::cout << "Transfer: " << jt << '\n';
    transfers.push_back(transfer);

    // Save all data in files
    file_repo.save_accounts(accounts);
    // TODO: refactor transfer saving
    file_repo.save_transfers(transfers);

  } catch (const std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
    return 1;
  }
}

// String to enforce Windows to save source code as UTF-8 so nlohmann::json lib
// would work
//  |
//  V
//"Привет! Hello! 你好！

// App entry point
int main() {
  // Set UTF-8 encoding of data on all systems
  setlocale(LC_ALL, "");
  // ifdef for Windows encoding
#ifdef _WIN32
  setlocale(LC_ALL, ".UTF-8");
  SetConsoleOutputCP(CP_UTF8);
#endif

  return try_exec();
}