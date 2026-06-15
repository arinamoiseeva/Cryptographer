cmake_minimum_required(VERSION 3.10)
project(cryptographer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cipher main.cpp ciphers.cpp)

enable_testing()
add_executable(tests tests.cpp ciphers.cpp)
add_test(NAME CipherTests COMMAND tests)