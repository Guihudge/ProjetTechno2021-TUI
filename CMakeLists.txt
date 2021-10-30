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
target_link_libraries(game_test_gdindart game)

# Ajout des tests
# fclaisse
add_test(test_fclaisse_dummy ./game_test_fclaisse dummy)

#gdindart
add_test(test_gdindart_dummy ./game_test_gdindart dummy)
add_test(test_gdindart_game_update_flags ./game_test_gdindart game_update_flags)
add_test(test_gdindart_game_default ./game_test_gdindart game_default)
add_test(test_gdindart_game_has_error ./game_test_gdindart game_has_error)
add_test(test_gdindart_game_is_marked ./game_test_gdindart game_is_marked)
add_test(test_gdindart_game_is_black ./game_test_gdindart game_is_black)
add_test(test_gdindart_game_set_square ./game_test_gdindart game_set_square)
add_test(test_gdindart_game_equal ./game_test_gdindart game_equal)
add_test(test_gdindart_game_new_empty ./game_test_gdindart game_new_empty)
