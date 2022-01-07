#include "game_ext.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libstack/stack.h"
#include "auxiliars.h"
#include "game_struct.h"

history add_move(history hist, char* pile, uint i, uint j, square s) {
    is_viable_pointer(hist, "pointer", __FILE__, __LINE__);
    is_viable_pointer(pile, "pointer", __FILE__, __LINE__);

    move m = create_move(i, j, s);

    if (strcmp(pile, "undo") == 0) {
        hist->undo = stack_push_head(hist->undo, m);
    } else if (strcmp(pile, "redo") == 0) {
        hist->redo = stack_push_head(hist->redo, m);
    } else {
        fprintf(stderr, "Error on history!!");
        exit(EXIT_FAILURE);
    }

    return hist;
}

game game_new_ext(uint nb_rows, uint nb_cols, square* squares, bool wrapping) {
    /*if (MALLOCSIZE(squares) < nb_cols * nb_rows) {
        fprintf(stderr, "game_size %u > squares_size %zu\n", nb_rows * nb_cols, MALLOCSIZE(squares));
        exit(EXIT_FAILURE);
    }*/

    if (nb_rows < 1 || nb_rows > 10 || nb_cols < 1 || nb_cols > 10) {
        fprintf(stderr, "Invalid size of grid\n");
        exit(EXIT_FAILURE);
    }

    game new_game = create_game_struct(nb_rows, nb_cols);

    for (uint i = 0; i < nb_rows; i++) {
        for (uint j = 0; j < nb_cols; j++) {
            new_game->tab[i][j] = squares[i * nb_cols + j];
        }
    }

    new_game->nb_row = nb_rows;
    new_game->nb_col = nb_cols;
    new_game->wrapping = wrapping;
    new_game->move = init_game_history();

    return new_game;
}

game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping) {
    uint size = nb_rows * nb_cols;
    square* tab = malloc(sizeof(square) * (size));
    for (uint i = 0; i < size; i++) {
        tab[i] = S_BLANK;
    }

    game ngame = game_new_ext(nb_rows, nb_cols, tab, wrapping);
    free(tab);
    return ngame;
}

uint game_nb_rows(cgame g) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    return g->nb_row;
}

uint game_nb_cols(cgame g) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    return g->nb_col;
}

bool game_is_wrapping(cgame g) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    return g->wrapping;
}

void game_undo(game g) {}

void game_redo(game g) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    is_viable_pointer(g->move, "pointer", __FILE__, __LINE__);

    if (stack_is_empty(g->move->redo)) {
        return;
    } else {
        move redo = stack_peek_head(g->move->redo);
        game_play_move(g, redo->i, redo->j, redo->s);
    }
}
