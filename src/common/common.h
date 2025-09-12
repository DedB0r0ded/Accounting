// common.h
// Pragmas
#pragma once


// C++
#include <mutex>
#include <type_traits>
#include <vector>

// Libs
#include "nlohmann/json.hpp"
#include "./math.h"             // <cmath>
#include "./strings.h"          //
#include "./enums.h"            // "./aliases.h" <- {<optional>, <memory>}
#include "./time.h"             // {<ctime>, <string>, <chrono>, "./aliases.h" <- {<optional>, <memory>}


// Defines
// Conditional compilation flags
#define ACCOUNTING_THREAD_SAFE_TIME


using namespace std::string_literals;
