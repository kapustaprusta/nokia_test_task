cmake_minimum_required(VERSION 3.15)
project(nokia_test_task)

set(CMAKE_CXX_STANDARD 17)

set (SOURCES
        main.cpp
        src/utils/utils.h
        src/defs/defs.h)

add_executable(nokia_test_task ${SOURCES})
add_subdirectory(tests)