#Version Cmake
cmake_minimum_required(VERSION 3.0)

#projet
project(game_text C)

include(CTest)
enable_testing()

#variable
set(CMAKE_C_FLAGS "-std=c99 -Wall")

set(GameSources libgame/auxiliars.c libgame/game_aux.c libgame/game_ext.c libgame/game.c)
set(GameHeaders libgame/auxiliars.h libgame/game_aux.h libgame/game_ext.h libgame/game.h libgame/game_struct.h)

set(StackSources libstack/stack.c)
set(StackHeaders libstack/stack.h)

add_library(game ${GameSources} ${GameHeaders})
add_library(stack ${StackSources} ${StackHeaders})

#création de l'éxécutable
add_executable(game_text game_text.c)

#on lie les librairie
target_link_libraries(game_text game)
target_link_libraries(game stack)

#on ajoute les tests
add_subdirectory(test)