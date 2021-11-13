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
add_executable(game_test_millhe game_test_millhe.c)

target_link_libraries(game_text game)
target_link_libraries(game_test_gdindart game)
target_link_libraries(game_test_millhe game)
target_link_libraries(game_test_fclaisse game)

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
add_test(test_gdindart_game_update_flags ./game_test_gdindart game_update_flags)
add_test(test_gdindart_game_default ./game_test_gdindart game_default)
add_test(test_gdindart_game_has_error ./game_test_gdindart game_has_error)
add_test(test_gdindart_game_is_marked ./game_test_gdindart game_is_marked)
add_test(test_gdindart_game_is_black ./game_test_gdindart game_is_black)
add_test(test_gdindart_game_set_square ./game_test_gdindart game_get_square)
add_test(test_gdindart_game_equal ./game_test_gdindart game_equal)
add_test(test_gdindart_game_new_empty ./game_test_gdindart game_new_empty)

#millhe
add_test(test_millhe_dummy ./game_test_millhe dummy)
add_test(test_millhe_game_print ./game_test_millhe game_print)
add_test(test_millhe_game_get_flags ./game_test_millhe game_get_flags)
add_test(test_millhe_game_get_black_number ./game_test_millhe game_get_black_number)
add_test(test_millhe_game_get_state ./game_test_millhe game_get_square)
add_test(test_millhe_game_is_over ./game_test_millhe game_is_over)
add_test(test_millhe_game_is_blanck ./game_test_millhe game_is_blanck)
add_test(test_millhe_game_delete ./game_test_millhe game_delete)
add_test(test_millhe_game_copy ./game_test_millhe game_copy)

