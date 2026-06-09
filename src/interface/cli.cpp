#include "cli.h"

namespace accounting {

  namespace{
    inline constexpr menu_option_t EXIT{0};
    inline constexpr menu_option_t BACK{0};
    inline constexpr menu_option_t MAIN_MENU_LOGIN{1};
    inline constexpr menu_option_t MAIN_MENU_SIGNUP{2};
  }


  Result<void> cli_start(char* argv[], int argc, AppState& state) {
    auto& os = state.os;
    auto& is = state.is;
    bool running = true;
    while (running) {
      clear_output(os);
      if (state.first_run) {
        os << MSG_WELCOME << NL;
      }
      os << "1. A" << NL
         << "2. B" << NL
         << "3. C" << NL
         << "0. Exit" << NL;
      auto option = get_option(is);
      if (!option) {
        print_error(os, option.error());
        os << MSG_CONTINUE;
        await_return(is);
        continue;
      }
      switch (option.value()) {
        case EXIT:
          os << MSG_BYE << NL;
          return Err(ErrorCode::TERMINATED, "Terminated by user.");
          break;
        case MAIN_MENU_LOGIN:
          sign_in_menu(state);
          break;
        case MAIN_MENU_SIGNUP:
          sign_up_menu(state);
          break;
        default:
          print_error(os, Error(ErrorCode::INVALID_ARGUMENT, MSG_INVALID_OPTION));
          os << MSG_CONTINUE;
          await_return(is);
          break;
      }
    }
    return Ok();
  }

  Result<void> user_menu(AppState& state) {
    return Ok();
  }

  Result<void> account_menu(AppState& state) {
    return Ok();
  }

  Result<void> transfer_menu(AppState& state) {
    return Ok();
  }

  Result<void> sign_in_menu(AppState& state) {
    return Ok();
  }

  Result<User> sign_up_menu(AppState& state) {
    auto& os = state.os;
    auto& is = state.is;
    bool running = true;
    string email{};
    string name{};
    string pwd{};
    id_t id{};

    return Ok<User>(User);
  }

}// nАmespace accounting
