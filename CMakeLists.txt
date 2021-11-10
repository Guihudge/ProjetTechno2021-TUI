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
#executable de test
add_executable(game_test_fclaisse game_test_fclaisse.c)
add_executable(game_test_gdindart game_test_gdindart.c)

target_link_libraries(game_text game)

# Ajout des tests
# fclaisse
add_test(test_fclaisse_dummy ./game_test_fclaisse dummy)
add_test(test_fclaisse_game_default_solution ./game_test_fclaisse game_default_solution)
add_test(test_fclaisse_game_new ./game_test_fclaisse game_new)
add_test(test_fclaisse_game_set_square ./game_test_fclaisse game_set_square)
add_test(test_fclaisse_game_is_lightbulb ./game_test_fclaisse game_is_lightbulb)
add_test(test_fclaisse_game_is_lighted ./game_test_fclaisse game_is_lighted)
add_test(test_fclaisse_game_check_move ./game_test_fclaisse game_check_move)
add_test(test_fclaisse_game_play_move ./game_test_fclaisse game_play_move)
add_test(test_fclaisse_game_restart ./game_test_fclaisse game_restart)

#gdindart
add_test(test_gdindart_dummy ./game_test_gdindart dummy)
