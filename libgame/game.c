#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../libstack/stack.h"
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

    int start_x, start_y, end_x, end_y;  // Init valeur des cordonnée de fin et début

    bool wrapping = g->wrapping;  // on check le wrapping

    if (i == 0 && !wrapping) {
        start_x = 0;  // on neutralise la valeur si on va de l'autre coté de la grille et si wrapping est désactivé
    } else if (i == 0 && wrapping) {
        start_x = g->nb_row - 1;  // on va de l'autre coté de la grille ssi wrapping et activé
    } else {
        start_x = i - 1;  // valeur par défaut
    }
    if (j == 0 && !wrapping) {  // même principe que au-dessus
        start_y = 0;
    } else if (j == 0 && wrapping) {
        start_y = g->nb_col - 1;
    } else {
        start_y = j - 1;
    }

    if (i + 1 >= g->nb_row && !wrapping) {  // même principe que au-dessus
        end_x = g->nb_row - 1;
    } else if (i + 1 >= g->nb_row && wrapping) {
        end_x = 0;
    } else {
        end_x = i + 1;
    }
    if (j + 1 >= g->nb_col && !wrapping) {  // même principe que au-dessus
        end_y = g->nb_col - 1;
    } else if (j + 1 >= g->nb_col && wrapping) {
        end_y = 0;
    } else {
        end_y = j + 1;
    }

    int tab_x[] = {start_x, end_x, i, i};  // on génère les couples valeurs possible
    int tab_y[] = {j, j, start_y, end_y};

    for (int i = 0; i < 4; i++) {  // on vérifie chaque couple de valeur possible
        int cx = tab_x[i];         // val en x
        int cy = tab_y[i];         // val en y
        if (game_is_lightbulb(g, cx, cy)) {
            lightbulb_number++;
        } else if (game_is_lighted(g, cx, cy)) {
            lighted_number++;
        } else if (game_is_blank(g, cx, cy)) {
            blank_number++;
        }
    }
    bool ret = false;

    if (lightbulb_number > black_number) {  // cas : trop de lightbulb
        return true;
    }
    if ((blank_number + lightbulb_number) < black_number) {  // cas plus assez de place pour les lightbulb
        return true;
    }
    return ret;
}

void update_row_cols(game g, uint i, uint j, bool row) {
    is_viable_pointer(g, "pointer", __FILE__, __LINE__);  // gest. erreur
    check_coordinates(g, i, j, __func__);

    int index = row ? i : j;  // index = i si row est vrai sinon index = j
    bool forward = true;      // && ()
    while (index >= 0) {
        if (row) {
            if (index > g->nb_row - 1 || game_is_black(g, index, j)) {
                if (forward) {
                    index = i;
                    forward = false;
                } else {
                    break;
                }
            } else {
                g->tab[index][j] |= F_LIGHTED;
                if (index != i &&
                    game_is_lightbulb(g, index, j)) {  // si il index a une autre lightbulb on met une erreur
                    g->tab[index][j] |= F_ERROR;
                    g->tab[i][j] |= F_ERROR;
                }
            }
        } else {
            if (index > g->nb_col - 1||game_is_black(g, i, index)) {
                if (forward) {
                    index = j;
                    forward = false;
                } else {
                    break;
                }
            } else {
                g->tab[i][index] |= F_LIGHTED;
                if (index != j && game_is_lightbulb(g, i, index)) {
                    g->tab[i][index] |= F_ERROR;
                    g->tab[i][j] |= F_ERROR;
                }
            }
        }
        if (forward) {
            index++;
        } else {
            index--;
        }
    }
}

void update_row_col_wrapping(game g, uint i, uint j, bool row) {
     is_viable_pointer(g, "pointer", __FILE__, __LINE__);  // gest. erreur
    check_coordinates(g, i, j, __func__);

    int stop_test_value = row ? i : j;
    int size = row ? g-> nb_row : g -> nb_col;
    int index = row ? i : j;  // index = i si row est vrai sinon index = j
    bool forward = true;      // && ()
    do {
        if (row) {
            if (game_is_black(g, index, j)) {
                if (forward) {
                    index = i;
                    forward = false;
                } else {
                    break;
                }
            } else {
                g->tab[index][j] |= F_LIGHTED;
                if (index != i &&
                    game_is_lightbulb(g, index, j)) {  // si il index a une autre lightbulb on met une erreur
                    g->tab[index][j] |= F_ERROR;
                    g->tab[i][j] |= F_ERROR;
                }
            }
        } else {
            if (game_is_black(g, i, index)) {
                if (forward) {
                    index = j;
                    forward = false;
                } else {
                    break;
                }
            } else {
                g->tab[i][index] |= F_LIGHTED;
                if (index != j && game_is_lightbulb(g, i, index)) {
                    g->tab[i][index] |= F_ERROR;
                    g->tab[i][j] |= F_ERROR;
                }
            }
        }
        if (forward) {
            index = (index + 1) % size;
        } else {
           if (index - 1 < 0) {
            index = size - 1;
        } else {
            index = (index - 1) % size;
        }
        }
    } while (index != stop_test_value);
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

    square *tmp_tab = (square *)malloc(sizeof(square) * g->nb_col * g->nb_row);
    game copy = game_new_ext(g->nb_row, g->nb_col, tmp_tab, g->wrapping);

    for (uint x = 0; x < g->nb_row; x++) {
        for (uint y = 0; y < g->nb_col; y++) {
            copy->tab[x][y] = g->tab[x][y];
        }
    }

    copy->move->undo = stack_new_empty();  // on init l'historique pour la copy
    copy->move->redo = stack_new_empty();
    free(tmp_tab);
    return copy;
}

bool game_equal(cgame g1, cgame g2) {
    is_viable_pointer(g1, "pointer", __FILE__, __LINE__);
    is_viable_pointer(g2, "pointer", __FILE__, __LINE__);

    if (g1->nb_col != g2->nb_col) {
        return false;
    }
    if (g1->nb_row != g2->nb_row) {
        return false;
    }
    if (g1->wrapping != g2->wrapping) {
        return false;
    }

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

    // free 2D tab
    if (g->tab != NULL) {
        for (uint x = 0; x < g->nb_row; x++) {
            if (g->tab[x] != NULL) {
                free(g->tab[x]);
            }
        }
        free(g->tab);
    }

    // free hystory struct
    if (g->move != NULL) {
        if (g->move->redo != NULL) {
            stack_clear(g->move->redo);
        }
        if (g->move->undo != NULL) {
            stack_clear(g->move->undo);
        }

        free(g->move);
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

    square currentState = game_get_state(g, i, j);
    move playerMove = create_move(i, j, currentState);
    g->move->undo = stack_push_head(g->move->undo, playerMove);
    g->move->redo = stack_clear(g->move->redo);

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
                if (g->wrapping) {
                    update_row_col_wrapping(g, i, j, true);
                    update_row_col_wrapping(g, i, j, false);
                } else {
                    update_row_cols(g, i, j, true);
                    update_row_cols(g, i, j, false);
                }
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

    g->move->undo = stack_clear(g->move->undo);
    g->move->redo = stack_clear(g->move->redo);
}
