cmake_minimum_required (VERSION 4.0)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("AccountingClient" LANGUAGES CXX)

# Uncomment the line below to specify Git executable location if necessary
#set(GIT_EXECUTABLE "C:/Program Files/Git/bin/git.exe") 

# Add nlohmann json to project
set(NLOHMANN_JSON_VERSION "v3.12.0")
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG ${NLOHMANN_JSON_VERSION}
)
FetchContent_MakeAvailable(json)


# Shortcut to source directory
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# All executables as a list
set(SOURCES
  "${SRC_DIR}/entities/account.cpp"
  "${SRC_DIR}/entities/transfer_state_switch.cpp"
  "${SRC_DIR}/entities/transfer.cpp"
  "${SRC_DIR}/repository/file_repository.cpp"
  "${SRC_DIR}/serialization/json_serializers.cpp"
  "${SRC_DIR}/interface/cli.cpp"
  "${SRC_DIR}/source.cpp"
)


add_executable (AccountingClient ${SOURCES})

set_target_properties(AccountingClient PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(AccountingClient PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(AccountingClient PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(AccountingClient PRIVATE ${SRC_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AccountingClient PROPERTY CXX_STANDARD 20)
endif()


# --- GoogleTest ---
include(FetchContent)
set(GOOGLE_TEST_VERSION "v1.17.0")
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG ${GOOGLE_TEST_VERSION}
)
# Для Windows, чтобы не было конфликтов с MSVC runtime
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()  # Включаем CTest

# --- Добавляем тесты ---
add_executable(AccountingTests
    )

target_link_libraries(AccountingTests 
  GTest::gtest_main 
  nlohmann_json::nlohmann_json 
)

include(GoogleTest)
gtest_discover_tests(AccountingTests)
