cmake_minimum_required(VERSION 3.0)

project(Stack C)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "-std=c99 -Wall")

set(SRCS stack.c)
set(HEADERS stack.h)

add_library(stack ${SRCS} ${HEADERS})

add_executable(stack_test stack_test.c)
target_link_libraries(stack_test stack)