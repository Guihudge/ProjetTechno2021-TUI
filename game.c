#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#include "auxiliars.h"

struct game_s {
    square **tab;
    uint nb_row;
    uint nb_col;
};

void reset_flags(game g) {
    is_viable_pointer(g, "pointer");

    for(uint i = 0; i < g->nb_row; i++) {
        for(uint j = 0; j < g->nb_col; j++) {
            game_set_square(g, i, j, game_get_state(g, i, j));
        }
    }
}

bool check_black_wall(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer");
    check_coordinates(i, j, __func__);

    int black_number = game_get_black_number(g, i, j);
    uint lightbulb_number = 0;

    if(black_number == -1) return false;

    if(j > 0 && game_is_lightbulb(g, i, j--)) lightbulb_number++;
    if(j < DEFAULT_SIZE - 1 && game_is_lightbulb(g, i, j++)) lightbulb_number++;
    if(i > 0 && game_is_lightbulb(g, i--, j)) lightbulb_number++;
    if(i < DEFAULT_SIZE - 1 && game_is_lightbulb(g, i, j)) lightbulb_number++;

    return lightbulb_number > black_number;
}

void update_row(game g, uint i, uint j) {
    is_viable_pointer(g, "pointer");
    check_coordinates(i, j, __func__);

    for(uint y = i; y < g->nb_row; y++) {
        if(game_is_black(g, y, j)) break;
        else g->tab[y][j] = g->tab[y][j] | F_LIGHTED;
    }

    for(uint y = i; y >= 0; y--) {
        if(game_is_black(g, y, j)) break;
        else g->tab[y][j] = g->tab[y][j] | F_LIGHTED;
    }
}

void update_col(game g, uint i, uint j) {
    is_viable_pointer(g, "pointer");
    check_coordinates(i, j, __func__);

    for(uint x = j; x < g->nb_col; x++) {
        if(game_is_black(g, i, x)) break;
        else g->tab[i][x] = g->tab[i][x] | F_LIGHTED;
    }

    for(uint x = j; x >= 0; x--) {
        if(game_is_black(g, i, x)) break;
        else g->tab[i][x] = g->tab[i][x] | F_LIGHTED;
    }
}

game create_game_struct(int nrow, int ncol) {
    game ngame = malloc(sizeof(struct game_s));
    is_viable_pointer(ngame, "memory");

    ngame->tab = malloc(sizeof(square *) * nrow);
    is_viable_pointer(ngame->tab, "memory");

    for (uint x = 0; x < nrow; x++) {
        ngame->tab[x] = malloc(sizeof(square) * ncol);
        is_viable_pointer(ngame->tab[x], "memory");
    }

    ngame->nb_col = ncol;
    ngame->nb_row = nrow;

    return ngame;
}

game game_new(square *init_tab) {
    is_viable_pointer(init_tab, "pointer");

    game g = create_game_struct(DEFAULT_SIZE, DEFAULT_SIZE);

    for (int x = 0; x < g->nb_row; x++) {
        for (int y = 0; y < g->nb_col; y++) {
            g->tab[x][y] = init_tab[x * g->nb_col + y];
        }
    }

    return g;
}

game game_new_empty(void) {
    square game_square[DEFAULT_SIZE * DEFAULT_SIZE] = {S_BLANK};

    return game_new(game_square);
}

game game_copy(cgame g) { return NULL; }

bool game_equal(cgame g1, cgame g2) {
    is_viable_pointer(g1, "pointer");
    is_viable_pointer(g2, "pointer");

    for (uint x = 0; x < g1->nb_row; x++) {
        for (uint y = 0; y < g1->nb_col; y++) {
            if (g1->tab[x][y] != g2->tab[x][y]) {
                return false;
            }
        }
    }

    return true;
}

void game_delete(game g) {
    is_viable_pointer(g, "pointer");

    // Rajouter des conditions pour ne pas free sur pointeur NULL
    if (g->tab != NULL) {
        for (uint x = 0; x < g->nb_row; x++) {
            if (g->tab[x] != NULL) {
                free(g->tab[x]);
            }
        }
        free(g->tab);
    }
    free(g);
}

void game_set_square(game g, uint i, uint j, square s) {}

square game_get_square(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer");
    check_coordinates(i, j, __func__);

    return g->tab[i][j];
}

square game_get_state(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer");
    check_coordinates(i, j, __func__);

    square tiles = g->tab[i][j];
    tiles = tiles & S_MASK;
    return tiles;
}

square game_get_flags(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer");
    check_coordinates(i, j, __func__);

    square tile = game_get_square(g, i, j);

    return tile & F_MASK;
}

bool game_is_blank(cgame g, uint i, uint j) { return true; }

bool game_is_lightbulb(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer");
    check_coordinates(i, j, __func__);

    return game_get_state(g, i, j) == S_LIGHTBULB;
}

bool game_is_black(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer");
    check_coordinates(i, j, __func__);

    square tiles = g->tab[i][j];
    tiles = tiles & S_BLACK;
    return (tiles == S_BLACK);
}

int game_get_black_number(cgame g, uint i, uint j) { return 1; }

bool game_is_marked(cgame g, uint i, uint j) { return true; }

bool game_is_lighted(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer");
    check_coordinates(i, j, __func__);

    square tiles = g->tab[i][j];
    tiles = tiles & F_LIGHTED;
    return (tiles == F_LIGHTED);
}

bool game_has_error(cgame g, uint i, uint j) { return true; }

bool game_check_move(cgame g, uint i, uint j, square s) {
    is_viable_pointer(g, "pointer");

    if(s != S_BLANK && s != S_LIGHTBULB && s != S_MARK) {
        printf("error state");
        return false;
    }
    if(i >= DEFAULT_SIZE || i < 0 || j >= DEFAULT_SIZE || j < 0) {
        printf("error coordinates");
        return false;
    }
    if(game_is_black(g, i, j)) {
        printf("error black wall");
        return false;
    }

    return true;
}

void game_play_move(game g, uint i, uint j, square s) {
    is_viable_pointer(g, "pointer");
    check_coordinates(i, j, __func__);

    if(!game_check_move(g, i, j, s)) 
        exit(EXIT_FAILURE);

    game_set_square(g, i, j, s);
    game_update_flags(g);
}

void game_update_flags(game g) {
    is_viable_pointer(g, "pointer");

    reset_flags(g);

    uint lightbulb_row = 0;
    uint lightbulb_col = 0;

    for(uint i = 0; i < g->nb_row; i++) {
        for(uint j = 0; j < g->nb_col; j++) {
            if(game_is_black(g, i, j) && check_black_wall(g, i, j)) {
                g->tab[i][j] = g->tab[i][j] | F_ERROR;
            }
            else if(game_is_lightbulb(g, i, j)) {
                update_col(g, i, j);
                update_row(g, i, j);
            }
        }
    }

    for(uint i = 0; i < g->nb_row; i++) {
        for(uint j = 0; j < g->nb_col; j++) {
            if(game_is_black(g, i, j)) lightbulb_col = 0;
            if(game_is_lightbulb(g, i, j) && lightbulb_col) {
                g->tab[i][j] = g->tab[i][j] | F_ERROR;
                g->tab[i][lightbulb_col] = g->tab[i][lightbulb_col] | F_ERROR;
            }
            if(game_is_lightbulb(g, i, j)) lightbulb_col = j;
        }
        lightbulb_col = 0;
    }

    for(uint j = 0; j < g->nb_col; j++) {
        for(uint i = 0; i < g->nb_row; i++) {
            if(game_is_black(g, i, j)) lightbulb_row = 0;
            if(game_is_lightbulb(g, i, j) && lightbulb_row) {
                g->tab[i][j] = g->tab[i][j] | F_ERROR;
                g->tab[i][lightbulb_row] = g->tab[i][lightbulb_row] | F_ERROR;
            }
            if(game_is_lightbulb(g, i, j)) lightbulb_row = i;
        }
        lightbulb_row = 0;
    }
}

bool game_is_over(cgame g) { return true; }

void game_restart(game g) {
    is_viable_pointer(g, "pointer");
    for (uint x = 0; x < g->nb_row; x++) {
        for (uint y = 0; y < g->nb_col; y++) {
            if (!game_is_black(g, x, y)) {
                g->tab[x][y] = 0;
            }
        }
    }
}
