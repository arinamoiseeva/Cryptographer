cmake_minimum_required(VERSION 3.10)
project(cryptographer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cipher main.cpp ciphers.cpp)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests tests.cpp ciphers.cpp)
target_link_libraries(run_tests gtest gtest_main)

add_test(NAME run_tests COMMAND run_tests)