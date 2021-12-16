#include "game_struct.h"
#include "game_ext.h"
#include "game.h"

game game_new_ext(uint nb_rows, uint nb_cols, square* squares, bool wrapping);
game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping);
uint game_nb_rows(cgame g);
uint game_nb_cols(cgame g);
bool game_is_wrapping(cgame g);
void game_undo(game g);
void game_redo(game g);
