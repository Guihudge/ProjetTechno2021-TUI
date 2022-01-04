#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#include "auxiliars.h"
#include "game_ext.h"
#include "game_struct.h"

void reset_flags(game g) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);

    for (uint i = 0; i < g->nb_row; i++) {
        for (uint j = 0; j < g->nb_col; j++) {
            game_set_square(g, i, j, game_get_state(g, i, j));
        }
    }
}

bool check_black_wall(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    int black_number = game_get_black_number(g, i, j);
    uint lightbulb_number = 0;
    uint lighted_number = 0;
    uint blank_number = 0;

    if (black_number == -1) return false;

    int start_x, start_y, end_x, end_y;

    if (i == 0) {
        start_x = 0;
    } else {
        start_x = i - 1;
    }
    if (j == 0) {
        start_y = 0;
    } else {
        start_y = j - 1;
    }

    if (i + 1 >= g->nb_col) {
        end_x = g->nb_col - 1;
    } else {
        end_x = i + 1;
    }
    if (j + 1 >= g->nb_row) {
        end_y = g->nb_row - 1;
    } else {
        end_y = j + 1;
    }

    for (int cx = start_x; cx <= end_x; cx++) {
        for (int cy = start_y; cy <= end_y; cy++) {
            if (game_is_lightbulb(g, cx, cy) && (cx == i || cy == j)) {
                lightbulb_number++;
            } else if (game_is_lighted(g, cx, cy) && (cx == i || cy == j)) {
                lighted_number++;
            } else if (game_is_blank(g, cx, cy) && (cx == i || cy == j)) {
                blank_number++;
            }
        }
    }
    bool ret = false;

    if (lightbulb_number > black_number) {
        return true;
    }
    if ((blank_number + lightbulb_number) < black_number) {
        return true;
    }
    return ret;
}

void update_row(game g, uint i, uint j) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    int y = i;
    while (y < g->nb_row) {
        if (game_is_black(g, y, j)) {
            break;
        } else {
            g->tab[y][j] |= F_LIGHTED;
            if (y != i && game_is_lightbulb(g, y, j)) {
                g->tab[y][j] |= F_ERROR;
                g->tab[i][j] |= F_ERROR;
            }
        }
        y++;
    }
    y = i;
    while (y >= 0) {
        if (game_is_black(g, y, j))
            break;
        else {
            g->tab[y][j] |= F_LIGHTED;
            if (y != i && game_is_lightbulb(g, y, j)) {
                g->tab[y][j] |= F_ERROR;
                g->tab[i][j] |= F_ERROR;
            }
        }
        y--;
    }
}

void update_col(game g, uint i, uint j) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    int x = j;
    while (x < g->nb_col) {
        if (game_is_black(g, i, x)) {
            break;
        } else {
            g->tab[i][x] |= F_LIGHTED;
            if (x != j && game_is_lightbulb(g, i, x)) {
                g->tab[i][x] |= F_ERROR;
                g->tab[i][j] |= F_ERROR;
            }
        }
        x++;
    }
    x = j;
    while (x >= 0) {
        if (game_is_black(g, i, x))
            break;
        else {
            g->tab[i][x] |= F_LIGHTED;
            if (x != j && game_is_lightbulb(g, i, x)) {
                g->tab[i][x] |= F_ERROR;
                g->tab[i][j] |= F_ERROR;
            }
        }
        x--;
    }
}

game game_new(square *squares) {
    is_viable_pointer(squares, "pointer", __FILE__, __LINE__);

    game g = game_new_ext(DEFAULT_SIZE, DEFAULT_SIZE, squares, false);

    return g;
}

game game_new_empty(void) {
    square game_square[DEFAULT_SIZE * DEFAULT_SIZE] = {S_BLANK};

    return game_new(game_square);
}

game game_copy(cgame g) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);

    game copy = create_game_struct(g->nb_row, g->nb_col);

    for (uint x = 0; x < g->nb_row; x++) {
        for (uint y = 0; y < g->nb_col; y++) {
            copy->tab[x][y] = g->tab[x][y];
        }
    }

    return copy;
}

bool game_equal(cgame g1, cgame g2) {
    is_viable_pointer(g1, "pointer", __FILE__, __LINE__);
    is_viable_pointer(g2, "pointer", __FILE__, __LINE__);

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
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);

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

void game_set_square(game g, uint i, uint j, square s) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    g->tab[i][j] = s;
}

square game_get_square(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    return g->tab[i][j];
}

square game_get_state(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    square tiles = g->tab[i][j];
    tiles = tiles & S_MASK;
    return tiles;
}

square game_get_flags(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    square tiles = g->tab[i][j];
    tiles = tiles & F_MASK;
    return tiles;
}

bool game_is_blank(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    square tiles = g->tab[i][j];
    tiles = tiles & S_MASK;
    return (tiles == S_BLANK);
}

bool game_is_lightbulb(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    square tiles = g->tab[i][j];
    if (tiles & S_BLACK) {
        return false;
    }
    tiles = tiles & S_LIGHTBULB;
    return (tiles == S_LIGHTBULB);
}

bool game_is_black(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    square tiles = g->tab[i][j];
    tiles = tiles & S_BLACK;
    return (tiles == S_BLACK);
}

int game_get_black_number(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    square tiles = game_get_square(g, i, j);

    if ((tiles & S_BLACKU) == S_BLACKU) {
        return -1;
    }
    if ((tiles & S_BLACK4) == S_BLACK4) {
        return 4;
    }
    if ((tiles & S_BLACK3) == S_BLACK3) {
        return 3;
    }
    if ((tiles & S_BLACK2) == S_BLACK2) {
        return 2;
    }
    if ((tiles & S_BLACK1) == S_BLACK1) {
        return 1;
    }
    if ((tiles & S_BLACK0) == S_BLACK0) {
        return 0;
    } else {
        exit(EXIT_FAILURE);
    }
}

bool game_is_marked(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    square tiles = g->tab[i][j];
    tiles = tiles & S_MARK;
    return (tiles == S_MARK);
}

bool game_is_lighted(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    square tiles = g->tab[i][j];
    tiles = tiles & F_LIGHTED;
    return (tiles == F_LIGHTED);
}

bool game_has_error(cgame g, uint i, uint j) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    square tiles = g->tab[i][j];
    tiles = tiles & F_ERROR;
    return (tiles == F_ERROR);
}

bool game_check_move(cgame g, uint i, uint j, square s) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);

    if (s != S_BLANK && s != S_LIGHTBULB && s != S_MARK) {
        return false;
    }
    // Pas besoin de i < 0 et j < 0 car ils sont de type unsigned int
    if (i >= game_nb_rows(g) || j >= game_nb_cols(g)) {
        return false;
    }
    if (game_is_black(g, i, j)) {
        return false;
    }

    return true;
}

void game_play_move(game g, uint i, uint j, square s) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);
    check_coordinates(g, i, j, __func__);

    if (!game_check_move(g, i, j, s)) {
        exit(EXIT_FAILURE);
    }

    game_set_square(g, i, j, s);
    game_update_flags(g);
}

void game_update_flags(game g) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);

    reset_flags(g);

    // update error and lighted flags for lightbulb
    for (uint i = 0; i < g->nb_row; i++) {
        for (uint j = 0; j < g->nb_col; j++) {
            if (game_is_lightbulb(g, i, j)) {
                update_row(g, i, j);
                update_col(g, i, j);
            }
        }
    }

    // update error flags on black wall
    for (uint i = 0; i < g->nb_row; i++) {
        for (uint j = 0; j < g->nb_col; j++) {
            if (game_is_black(g, i, j) && check_black_wall(g, i, j)) {
                g->tab[i][j] |= F_ERROR;
            }
        }
    }
}

bool game_is_over(cgame g) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);

    for (uint x = 0; x < g->nb_row; x++) {
        for (uint y = 0; y < g->nb_col; y++) {
            if ((!game_is_black(g, x, y) && !game_is_lighted(g, x, y)) || game_has_error(g, x, y)) {
                return false;
            }
        }
    }
    return true;
}

void game_restart(game g) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);

    for (uint x = 0; x < g->nb_row; x++) {
        for (uint y = 0; y < g->nb_col; y++) {
            if (game_is_black(g, x, y)) {
                g->tab[x][y] = g->tab[x][y] & S_MASK;
            } else {
                g->tab[x][y] = S_BLANK;
            }
        }
    }
}
