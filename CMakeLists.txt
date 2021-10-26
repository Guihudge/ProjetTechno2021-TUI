#Version Cmake
cmake_minimum_required(VERSION 2.6)

#projet
project(game_text C)

include(CTest)
enable_testing()

#variable
set(CMAKE_C_FLAGS "-std=c99 -Wall")

#cration des libraire
add_library(game game_aux.c game.o)

#création de l'éxécutable
add_executable(game_text game_text.c)
add_executable(game_test_fclaisse game_test_fclaisse.c)

target_link_libraries(game_text game)

add_test(test_fclaisse_dummy ./game_test_fclaisse dummy)