TODO:
- make a `README.md`
- finish logging system: `src/common/logger.cpp`, `src/common/logger.h`, `src/common/log_scope.cpp` and `src/common/logging.h`
- test methods from `src/files/`
- test methods from `src/repository/file_repository.cpp|.h`
- implement Command Line Interface (CLI) in `src/interface/cli.cpp|.h`

- - implement conditional compilation in `transfer.cpp` and `transfer.h` depending on `USE_CUSTOM_DATE_TIME_`
- - implement serialization/parsers for `std::tm` with the new custom structure/class

# Documentation
### strings.h
*No includes*
Contains strings used in the project with `#define` macros.
Strings are devided in logical sections. First word of macro name is either a section name or `ERROR` for error messages.

### aliases.h
*Includes:* <cstdint>, <optional>, <memomry>, <chrono>, "./strings.h"
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
*Includes:* <ctime>, <string>, <sstream>, <iomanip>, "./aliases.h"
Contains small `inline` functions for basic time operations.
- `to_tm(const time_t& src)` to convert `time_t` into a local-time `tm`. Uses unsafe `std::localtime` function unless `ACCOUNTING_THREAD_SAFE_TIME` macro is defined. If defined, uses `localtime_s` on Windows and `localtime_r` on POSIX systems
- `get_current_time` gets current local time as `time_t` from `std::chrono::system_clock`
- `get_current_time_tm` gets current local time as `tm` from `std::chrono::system_clock`
- `to_tm_utc(const time_t& src)` to convert `time_t` into a UTC `tm`. Uses unsafe `std::gmtime` function unless `ACCOUNTING_THREAD_SAFE_TIME` macro is defined. If defined, uses `gmtime_s` on Windows and `gmtime_r` on POSIX systems
- `get_current_time_utc` gets current UTC time as `time_t` from `std::chrono::system_clock`
- `get_current_time_tm_utc` gets current UTC time as `tm` from `std::chrono::system_clock`


### date_time.h
