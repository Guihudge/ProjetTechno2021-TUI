#include "auxiliars.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_ext.h"
#include "game_struct.h"
#include "../libstack/stack.h"

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

void memory_error(char *file, int line) {
    fprintf(stderr, "Memory error in file %s at line %d\n", file, line);
    exit(EXIT_FAILURE);
}

void pointer_error(char *file, int line) {
    fprintf(stderr, "Pointeur error in file %s at line %d\n", file, line);
    exit(EXIT_FAILURE);
}

void is_viable_pointer(const void *pointer, const char *type, char *file, int line) {
    if (pointer == NULL) {
        if (strcmp("memory", type) == 0)
            memory_error(file, line);
        else if (strcmp("pointer", type) == 0)
            pointer_error(file, line);
        else {
            fprintf(stderr, "Unknown error type by fonction %s providing %s at line %d\n", __func__, file, line);
            exit(EXIT_FAILURE);
        }
    }
}

void check_coordinates(cgame g, uint i, uint j, const char *fonction) {
    if (i >= game_nb_rows(g) || j >= game_nb_cols(g)) {
        fprintf(stderr, "Wrong arguments (%d,%d) for (%d,%d) inside %s call\n", i, j, game_nb_rows(g), game_nb_cols(g),
                fonction);
        exit(EXIT_FAILURE);
    }
}

bool delete_and_exit(bool exit, game *games, uint size, char *error) {
    for (uint i = 0; i != size; i++) {
        game_delete(games[i]);
    }
    if (strcmp(error, "")) {
        fprintf(stderr, "%s\n", error);
    }
    return exit;
}

game create_game_struct(uint nrow, uint ncol) {
    game ngame = (game) malloc(sizeof(struct game_s));
    if (ngame == NULL) {
        pointer_error(__FILE__, __LINE__);
    }

    ngame->tab = (square **) malloc(sizeof(square *) * nrow);
    is_viable_pointer(ngame->tab, "memory", __FILE__, __LINE__);

    for (uint x = 0; x < nrow; x++) {
        ngame->tab[x] = (square *)malloc(sizeof(square) * ncol);
        is_viable_pointer(ngame->tab[x], "memory", __FILE__, __LINE__);
    }

    return ngame;
}