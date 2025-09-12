#pragma once


#include <optional>
#include <memory>


namespace accounting {
// General aliases
template <typename T>
using uptr = std::unique_ptr<T>;

template <typename T>
using sptr = std::shared_ptr<T>;

using std::string;

using std::chrono::steady_clock;
using std::chrono::system_clock;

using optional_tm = std::optional<std::tm>;

using json = nlohmann::json;


// Numeric aliases
using i8 = int8_t;
using i32 = int32_t;

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;

using id_t = uint16_t;
using lid_t = uint64_t;
} // namespace accounting