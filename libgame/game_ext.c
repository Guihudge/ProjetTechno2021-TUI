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
        fprintf(stderr, "Error on history!!");
        exit(EXIT_FAILURE);
    }

    return hist;
}

game game_new_ext(uint nb_rows, uint nb_cols, square* squares, bool wrapping) { 
    
    if(MALLOCSIZE(squares) < nb_cols * nb_rows) { 
        fprintf(stderr, "game_size %u > squares_size %zu\n", nb_rows * nb_cols, MALLOCSIZE(squares)); 
        exit(EXIT_FAILURE);    
    }
    
    game new_game = (game) malloc(sizeof(struct game_s));
    is_viable_pointer(new_game, "memory");

    new_game->tab = (square**) malloc(sizeof(square*) * nb_rows);
    is_viable_pointer(new_game->tab, "memory");

    for(uint i = 0; i < nb_rows; i++) {
        new_game->tab[i] = (square*) malloc(sizeof(square) + nb_cols);
        is_viable_pointer(new_game->tab[i], "memory");
    }

    for(uint i = 0; i < nb_rows; i++) {
        for(uint j = 0; j < nb_cols; j++) {
            new_game->tab[i][j] = squares[i + nb_cols + j];
        }
    }

    new_game->nb_row = nb_rows;
    new_game->nb_col = nb_cols;
    new_game->warpping = wrapping;
    new_game->move = init_game_history();

    return new_game;
}

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

void game_undo(game g) {

}

void game_redo(game g) {

}
