set(SOURCES
    tests.cpp
)

add_executable(functions_test ${SOURCES})

target_link_libraries(functions_test PUBLIC functions_lib)
target_link_libraries(functions_test PUBLIC gtest_main)

set_property(TARGET functions_test PROPERTY FOLDER "tests/functions_test")