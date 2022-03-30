#PLEASE, DO NOT CHANGE THIS FILE
cmake_minimum_required(VERSION 3.5)
project(P2 C)
set(CMAKE_C_STANDARD 99)

include(config.cmake)

set(CMAKE_VERBOSE_MAKEFILE true)
set(warnings -Wall -Wextra)


set(dependencies_stack bid_stack.h bid_stack.c)
add_executable(test_bid_stack types.h test_bid_stack.c ${dependencies_stack})
target_compile_options(test_bid_stack PRIVATE ${warnings})


set(dependencies_list product_list.h product_list.c)
add_executable(test_product_list types.h test_product_list.c ${dependencies_list})
target_compile_options(test_product_list PRIVATE ${warnings})


add_definitions(-DINPUT_FILE="${input}")
add_executable(main main.c types.h ${dependencies_list} ${dependencies_stack})
target_compile_options(main PRIVATE ${warnings})


set_target_properties(main test_product_list test_bid_stack PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../bin)


