#Version Cmake
cmake_minimum_required(VERSION 2.6)

#projet
project(game_text C)

#variable
set(CMAKE_C_FLAGS "-std=c99 -Wall")

#cration des libraire
add_library(libgame.a game_aux.c game.o)

#création de l'éxécutable
add_executable(game_text game_text.c)

target_link_libraries(game_text libgame.a)