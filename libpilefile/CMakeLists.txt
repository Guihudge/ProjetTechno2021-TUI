cmake_minimum_required(VERSION 3.0)

project(PileFile C)

set(CMAKE_C_FLAGS "-std=c99 -Wall")

set(SRCS file.c pile.c)
set(HEADERS file.h pile.h)

add_library(pilefile ${SRCS} ${HEADERS})

add_subdirectory(tests)