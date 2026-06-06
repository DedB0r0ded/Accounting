#pragma once

#include <common/common.h>
#include "entities/account.h"
#include "entities/transfer.h"

namespace accounting {


  // Application UI (CLI) entry point
  Result<void> cli_start(char* argv[], int argc, AppState& state);


} // nАmespace accounting
