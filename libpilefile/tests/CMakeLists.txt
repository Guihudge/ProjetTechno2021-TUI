cmake_minimum_required(VERSION 3.0)

project(pilefile_test C)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "-std=c99 -Wall")

add_executable(pile_test pile_test.c)
add_executable(file_test file_test.c)