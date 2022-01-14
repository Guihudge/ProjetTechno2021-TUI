cmake_minimum_required(VERSION 3.0)

#nom sous projet
project(Stack C)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "-std=c99 -Wall --coverage")

#création de la librairie
add_library(stack stack.c stack.h)

