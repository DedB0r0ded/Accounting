#include "common/common.h"
#include "entities/account.h"
#include "entities/transfer.h"
#include "repository/file_repository.h"


#ifdef _WIN32
#include "windows.h"
#endif


using namespace accounting;


int main() {
  setlocale(LC_ALL, "");

#ifdef _WIN32
  setlocale(LC_ALL, ".UTF-8");
  SetConsoleOutputCP(CP_UTF8);
#endif

  // ?
  try {
    auto accounts = std::vector<Account>();
    auto transfers = std::vector<Transfer>();
    FileRepository file_repo("accounts.json", "transfers.json");
    if (file_repo.accounts_file_exists())
      accounts = file_repo.load_accounts();
    if (file_repo.transfers_file_exists())
      transfers = file_repo.load_transfers();
    for (auto acc : accounts) cout << json(acc);
    for (auto tr : transfers) cout << json(tr);


    // Создаем тестовые аккаунты
    auto account1 = Account(1, Currency::USD, "Alice Savings",
                                              1000, AccountType::PASSIVE);
    auto account2 = Account(2, Currency::USD, "Bob Checking",
                                              500, AccountType::ACTIVE);

    accounts.push_back(account1);
    accounts.push_back(account2);

    // Получаем текущее время
    auto current_time = *get_current_time_tm();

    // Создаем перевод между аккаунтами
    Transfer transfer(1, current_time, std::make_shared<Account>(account1), 200, std::make_shared<Account>(account2), 200);

    //"Привет! Hello! 你好！

    // Выполняем перевод
    if (transfer.commit()) {
      std::cout << "\nПеревод выполнен успешно!\n";
    } else {
      std::cout << "\nОшибка перевода: " << transfer.err_msg() << "\n";
    }


    file_repo.save_transfers(transfers);
    file_repo.save_accounts(accounts);

    
  } catch (const std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}