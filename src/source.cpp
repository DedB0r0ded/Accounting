// String to enforce Windows to save source code as UTF-8 so nlohmann::json lib
// would work
//  |
//  V
//"Привет! Hello! 你好！


#include <iostream>

#include <common/common.h>
#include <interface/cli.h>
#include <entities/user.h>

#ifdef _WIN32
#include "windows.h"
#endif


using namespace accounting;


struct DomainState {
  User& current_user;
  std::vector<Account>& accounts;
  std::vector<Transfer>& transfers;
};


int main(char* argv[], int argc) {
  // Set UTF-8 encoding of data on all systems
  const char* locale_result = setlocale(LC_ALL, "");
  // ifdef for Windows encoding
#ifdef _WIN32
  locale_result = setlocale(LC_ALL, ".UTF-8");
  SetConsoleOutputCP(CP_UTF8);
#endif
  auto state = acx::AppState(std::cout, std::cin);
  if (!cli_start(argv, argc, state)) {
    return -1;
  }
  return 0;
}
