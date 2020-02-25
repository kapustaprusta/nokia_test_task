set(SOURCES
functions.h
functions.cpp
)

add_library(functions_lib ${SOURCES})

target_include_directories(functions_lib PUBLIC ${SRC_ROOT_DIR})

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES})

set_property(TARGET functions_lib PROPERTY FOLDER "functions")

add_subdirectory(tests)