#include "game_ext.h"

#include <stdio.h>

#include "auxiliars.h"
#include "game.h"
#include "game_struct.h"

game game_new_ext(uint nb_rows, uint nb_cols, square* squares, bool wrapping) { return NULL; }

game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping) { return NULL; }

uint game_nb_rows(cgame g) {
    is_viable_pointer(g, "pointer");
    return g->nb_row;
}

uint game_nb_cols(cgame g) {
    is_viable_pointer(g, "pointer");
    return g->nb_col;
}

bool game_is_wrapping(cgame g) {
    is_viable_pointer(g, "pointer");
    return g->warpping;
}

void game_undo(game g) {}

void game_redo(game g) {}
