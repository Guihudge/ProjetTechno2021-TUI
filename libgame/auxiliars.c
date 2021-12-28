#include "auxiliars.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_ext.h"

void memory_error(void) {
    fprintf(stderr, "Memory error\n");
    exit(EXIT_FAILURE);
}

void pointer_error(void) {
    fprintf(stderr, "Pointeur error\n");
    exit(EXIT_FAILURE);
}

void is_viable_pointer(const void *pointer, const char *type) {
    if (pointer == NULL) {
        if (strcmp("memory", type) == 0)
            memory_error();
        else if (strcmp("pointer", type) == 0)
            pointer_error();
        else {
            fprintf(stderr, "Unknown error type by fonction %s\n", __func__);
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