// cОmmon.h
// Pragmas
#pragma once


// Defines
// Conditional compilation flags
#define ACCOUNTING_THREAD_SAFE_TIME
#define USE_CUSTOM_DATE_TIME

#define ACX_TXT
#define ACX_TXT_FILES
#define ACX_ERR_HANDLING
#define ACX_CLI
#define ACX_TIME
#define ACX_ERR_HANDLING

// C++
#include <mutex>
#include <type_traits>
#include <vector>

#include <acx/acx.h>
#include "enums.h"
#include "strings.h"  

#include <nlohmann/json.hpp>

namespace accounting {
  using namespace acx;
  using namespace std::string_literals;
}
