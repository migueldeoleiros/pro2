#PLEASE, DO NOT CHANGE THIS FILE
cmake_minimum_required(VERSION 3.5)
project(P1 C)
set(CMAKE_C_STANDARD 99)

include(config.cmake)

if(impl STREQUAL STATIC)
    add_definitions(-DSTATIC_LIST)
    set(dependencies static_list.h static_list.c)
elseif(impl STREQUAL DYNAMIC)
    add_definitions(-DDYNAMIC_LIST)
    set(dependencies dynamic_list.h dynamic_list.c)
endif()

set(CMAKE_VERBOSE_MAKEFILE true)
add_definitions(-DINPUT_FILE="${input}")
add_executable(main main.c types.h ${dependencies})
add_executable(test_lists types.h test.c ${dependencies})
target_compile_options(main PRIVATE -Wall -Wextra)
target_compile_options(test_lists PRIVATE -Wall -Wextra)
set_target_properties(main test_lists PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../bin)


