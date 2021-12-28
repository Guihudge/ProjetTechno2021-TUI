#Version Cmake
cmake_minimum_required(VERSION 3.0)

#projet
project(game_text C)

include(CTest)
enable_testing()

#variable
set(CMAKE_C_FLAGS "-std=c99 -Wall")

#add Subdirectory
add_subdirectory(libgame)
add_subdirectory(libpilefile)

#création de l'éxécutable
add_executable(game_text game_text.c)

#on lie les librairie
target_link_libraries(game_text game)
target_link_libraries(game_text pilefile)

#on ajoute les tests
add_subdirectory(test)