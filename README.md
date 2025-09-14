TODO:
- make a `README.md`
- finish logging system: `src/common/logger.cpp`, `src/common/logger.h`, `src/common/log_scope.cpp` and `src/common/logging.h`
- test methods from `src/files/`
- test methods from `src/repository/file_repository.cpp|.h`
- implement Command Line Interface (CLI) in `src/interface/cli.cpp|.h`

- - implement conditional compilation in `transfer.cpp` and `transfer.h` depending on `USE_CUSTOM_DATE_TIME_`
- - implement serialization/parsers for `std::tm` with the new custom structure/class

# Documentation
- src/
  - common/
    - [strings.h]
    - [aliases.h]
    - [time.h]
    - [date_time.h]


### strings.h
*No includes*  
Contains strings used in the project with `#define` macros.
Strings are devided in logical sections. First word of macro name is either a section name or `ERROR` for error messages.


### aliases.h
*Includes:* `<cstdint>`, `<optional>`, `<memomry>`, `<chrono>`, "./strings.h"  
Contains the aliases for the types used in the project:
- numerics from `cstdint`: `i8`, `i32`, `u8`, `u32`, `u64`
- numerics for identifiers like 16-bit unsigned `id_t` and 64-bit unsigned `lid_t` 
- `optional_tm` for `std::optional<std::tm>`. Actual redundant, might be removed in the future
- `uptr` for `std::unique_ptr`
- `sptr` for `std::shared_ptr`

Aliases are defined with `using` keyword.  
Also contains some `using`s for `std` namespace types:  
- `std::string`
- `std::chrono::steady_clock`
- `std::chrono::system_clock`


### time.h
*Includes:* `<ctime>`, `<string>`, `<sstream>`, `<iomanip>`, "./aliases.h"  
Contains small `inline` functions for basic time operations.
- `to_tm(const time_t& src)` to convert `std::time_t` into a local-time `std::tm`. Uses unsafe `std::localtime` function unless `ACCOUNTING_THREAD_SAFE_TIME` macro is defined. If defined, uses `localtime_s` on Windows and `localtime_r` on POSIX systems
- `get_current_time()` gets current local time as `std::time_t` from `std::chrono::system_clock`
- `get_current_time_tm()` gets current local time as `std::tm` from `std::chrono::system_clock`
- `to_tm_utc(const time_t& src)` to convert `std::time_t` into a UTC `std::tm`. Uses unsafe `std::gmtime` function unless `ACCOUNTING_THREAD_SAFE_TIME` macro is defined. If defined, uses `gmtime_s` on Windows and `gmtime_r` on POSIX systems
- `get_current_time_utc()` gets current UTC time as `std::time_t` from `std::chrono::system_clock`
- `get_current_time_tm_utc()` gets current UTC time as `std::tm` from `std::chrono::system_clock`
- `to_string(const tm& t)` parses `std::tm` into an `ISO8601` string
- `from_string(const string& s)` parses `ISO8601` string into `std::tm`. Returns `std::optional<std::tm>` if parsed successfully. `std::nullopt` if parsing failed


### date_time.h
*Includes:* "./time.h"
Contains custom `DateTime` wrapper type for `std::tm`. 
`nlohmann::json` can't parse `std::tm` using `to_json` and `from_json` overloads
 from `accounting` namespace. There are several ways to solve this issue.
 Creating custom wrapper type within `accounting` namespace is one of them.

`DateTime` class:
- Rule of five implemented (default ctor, copy ctor, move ctor, copy assignment, move assignment)
- `explicit DateTime(const tm& t)` creates a `DateTime` instance based on `std::tm` reference provided. Marked `explicit` to prevent implicit conversions
- `explicit DareTime(const optional_tm& t)` creates a `DateTime` instance from `optional_tm` reference. See [aliases.h] for `optional_tm` definition
- `DateTime& operator=(const tm& t)` assignment operator. Sets internal value to `std::tm` provided 
- `DateTime& operator=(const optional_tm& t)` assignment operator. Sets internal container to `optional_tm` provided. See [aliases.h] for `optional_tm` definition
- `constexpr const tm& value()` returns `std::tm` internal value
- `constexpr bool is_null()` returns true if internal container is `std::nullopt`
- `void reset()` resets internal container to `std::nullopt`
- `operator<<` overload. "null" if `DateTime` instance has no value. `ISO8601`-stringified `DateTime` otherwise 