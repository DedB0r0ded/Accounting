// common.h
// Pragmas
#pragma once


// Defines
// Conditional compilation flags
#define ACCOUNTING_THREAD_SAFE_TIME
#define USE_CUSTOM_DATE_TIME


// C++
#include <mutex>
#include <type_traits>
#include <vector>

// Libs
#include "nlohmann/json.hpp"
#include "./math.h"             // <cmath>
#include "./enums.h"            // "./aliases.h" <- {<optional>, <memory>, "./strings.h"}
#include "./time.h"             // {<ctime>, <string>, <sstream>, <iomanip>, "./aliases.h" <- {<cstdint>, <optional>, <memory>, <chrono>}

#ifdef USE_CUSTOM_DATE_TIME
#include "./date_time.h"
#endif

using namespace std::string_literals;
