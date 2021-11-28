#include "game.h"

#include <stdio.h>
#include <stdlib.h>

struct game_s {
    square **tab;
    uint nb_row;
    uint nb_col;
};

void crit_error_game(char *err) {
    fprintf(stderr, "[CRITICAL] %s\n", err);
    exit(EXIT_FAILURE);
}

void checkmem (void* pointer){
    if (pointer == NULL){
        crit_error_game("Error on memory allocation of free");
    }
}

game create_game_struct(int nrow, int ncol){
    if(nrow<= 0 || ncol <= 0){
        crit_error_game("Invalid game size");
    }
    game ngame = malloc(sizeof(struct game_s));
    ngame -> tab = malloc(sizeof(square*)* nrow);
    checkmem(ngame -> tab);

    for(int x = 0; x < nrow; x++){
        ngame -> tab[x] = malloc(sizeof(square)*ncol);
        checkmem(ngame -> tab[x]);
    }

    ngame -> nb_col = ncol;
    ngame -> nb_row = nrow;

    return ngame;
}

game game_new(square *init_tab) { 
    checkmem(init_tab);
    game g = create_game_struct(DEFAULT_SIZE, DEFAULT_SIZE);

    for (int x = 0; x < g -> nb_row; x++)
    {
        for(int y = 0; y < g -> nb_col; y ++){
            g -> tab[x][y] = init_tab[x*g->nb_col + y];
        }
    }

    return g;

}

game game_new_empty(void) { return NULL; }

game game_copy(cgame g) { return NULL; }

bool game_equal(cgame g1, cgame g2) { 
    checkmem(g1);
    checkmem(g2);

    for (int x = 0; x < g1 -> nb_row; x++)
    {
        for(int y = 0; y < g1 -> nb_col; y ++){
            if(g1 -> tab[x][y] != g2 -> tab[x][y]){
                return false;
            }
        }
    }

    return true;
 }

void game_delete(game g) {
    checkmem(g);
    
    for(int x = 0; x < g -> nb_row; x++){
        free(g -> tab[x]);
    }
    free(g -> tab);
    free(g);
}

void game_set_square(game g, uint i, uint j, square s) {}

square game_get_square(cgame g, uint i, uint j) { return S_BLANK; }


square game_get_state(cgame g, uint i, uint j) { 
    checkmem(g);
    square tiles = g -> tab[i][j];
    char mask_flags = 48; //00110000
    tiles = tiles | mask_flags;
    tiles = tiles - 48;
    return tiles;
 }


square game_get_flags(cgame g, uint i, uint j) { return S_BLANK; }

bool game_is_blank(cgame g, uint i, uint j) { return true; }

bool game_is_lightbulb(cgame g, uint i, uint j) { return true; }

bool game_is_black(cgame g, uint i, uint j) { return true; }

int game_get_black_number(cgame g, uint i, uint j) { return 1; }

bool game_is_marked(cgame g, uint i, uint j) { return true; }

bool game_is_lighted(cgame g, uint i, uint j) { return true; }

bool game_has_error(cgame g, uint i, uint j) { return true; }

bool game_check_move(cgame g, uint i, uint j, square s) { return true; }

void game_play_move(game g, uint i, uint j, square s) {}

void game_update_flags(game g) {}

bool game_is_over(cgame g) { return true; }

void game_restart(game g) {}
