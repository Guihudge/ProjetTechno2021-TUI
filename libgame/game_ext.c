#include "game_ext.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libstack/stack.h"
#include "auxiliars.h"
#include "game_struct.h"

history init_game_history() {
    history hist = (history)malloc(sizeof(struct history_s));
    hist->redo = stack_new_empty();
    hist->undo = stack_new_empty();
    return hist;
}

move create_move(uint i, uint j, square s) {
    move m = (move)malloc(sizeof(struct move_s));
    m->i = i;
    m->j = j;
    m->s = s;
    return m;
}

history add_move(history hist, char* pile, uint i, uint j, square s) {
    is_viable_pointer(hist, "pointer");
    is_viable_pointer(pile, "pointer");

    move m = create_move(i, j, s);

    if (strcmp(pile, "undo") == 0) {
        hist->undo = stack_push_head(hist->undo, m);
    } else if (strcmp(pile, "redo") == 0) {
        hist->redo = stack_push_head(hist->redo, m);
    } else {
        exit(EXIT_FAILURE);
        fprintf(stderr, "Error on history!!");
    }

    return hist;
}

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
