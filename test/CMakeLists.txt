cmake_minimum_required(VERSION 3.0)

#nom sous projet
project(game_test C)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "-std=c99 -Wall")

#on crée les éxécutables de tests
add_executable(game_test_fclaisse game_test_fclaisse.c)
add_executable(game_test_gdindart game_test_gdindart.c)
add_executable(game_test_millhe game_test_millhe.c)
add_executable(stack_test stack_test.c)

#note : pas besoin d'indiquer les dossiers des lib car déjà inclue dans le cmake principale (celui à la racine du projet)
#on link la lib game
target_link_libraries(game_test_gdindart game)
target_link_libraries(game_test_millhe game)
target_link_libraries(game_test_fclaisse game)
target_link_libraries(stack_test game)

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
add_test(test_fclaisse_game_redo ./game_test_fclaisse game_redo)

#gdindart
add_test(test_gdindart_dummy ./game_test_gdindart dummy)
add_test(test_gdindart_game_update_flags ./game_test_gdindart game_update_flags)
add_test(test_gdindart_game_default ./game_test_gdindart game_default)
add_test(test_gdindart_game_has_error ./game_test_gdindart game_has_error)
add_test(test_gdindart_game_is_marked ./game_test_gdindart game_is_marked)
add_test(test_gdindart_game_is_black ./game_test_gdindart game_is_black)
add_test(test_gdindart_game_get_square ./game_test_gdindart game_get_square)
add_test(test_gdindart_game_equal ./game_test_gdindart game_equal)
add_test(test_gdindart_game_new_empty ./game_test_gdindart game_new_empty)
add_test(test_gdindart_game_nb_rows ./game_test_gdindart game_nb_rows)
add_test(test_gdindart_game_nb_cols ./game_test_gdindart game_nb_cols)
add_test(test_gdindart_game_is_wrapping ./game_test_gdindart game_is_wrapping)

#millhe
add_test(test_millhe_dummy ./game_test_millhe dummy)
add_test(test_millhe_game_print ./game_test_millhe game_print)
add_test(test_millhe_game_get_flags ./game_test_millhe game_get_flags)
add_test(test_millhe_game_get_black_number ./game_test_millhe game_get_black_number)
add_test(test_millhe_game_get_state ./game_test_millhe game_get_state)
add_test(test_millhe_game_is_over ./game_test_millhe game_is_over)
add_test(test_millhe_game_is_blanck ./game_test_millhe game_is_blanck)
add_test(test_millhe_game_delete ./game_test_millhe game_delete)
add_test(test_millhe_game_copy ./game_test_millhe game_copy)
add_test(test_millhe_game_new_empty_ext ./game_test_millhe game_new_empty_ext)
add_test(test_millhe_game_undo ./game_test_millhe game_undo)

#libstack
add_test(stack_test_new_empty ./stack_test stack_new_empty)
add_test(stack_test_is_empty ./stack_test stack_is_empty)
add_test(stack_test_push_head ./stack_test stack_push_head)
add_test(stack_test_pop_head ./stack_test stack_pop_head)
add_test(stack_test_peek_head ./stack_test stack_peek_head)
add_test(stack_test_clear ./stack_test stack_clear)
add_test(stack_test_free ./stack_test stack_free)
