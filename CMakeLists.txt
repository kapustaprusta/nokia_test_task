cmake_minimum_required(VERSION 3.15)
project(nokia_test_task)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(google_tests)

add_executable(nokia_test_task main.cpp utils/utils.h defs/defs.h google_tests/utils_tests.cpp)