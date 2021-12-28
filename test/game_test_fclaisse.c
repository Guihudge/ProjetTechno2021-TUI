#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../libgame/game.h"
#include "../libgame/game_aux.h"
#include "../libgame/game_ext.h"

/* ********** TEST DUMMY ********** */

bool test_dummy(void) { return true; }

/* ********** TEST GAME DEFAULT SOLUTION ********** */

bool test_game_default_solution(void) {
    game default_solution = game_default_solution();
    square square_default_solution_test[] = {
        S_LIGHTBULB, S_BLANK,  S_BLACK1, S_LIGHTBULB, S_BLANK,     S_BLANK,     S_BLANK, S_BLANK,     S_LIGHTBULB,
        S_BLACK2,    S_BLANK,  S_BLANK,  S_BLANK,     S_LIGHTBULB, S_BLANK,     S_BLANK, S_LIGHTBULB, S_BLANK,
        S_BLANK,     S_BLACKU, S_BLACK2, S_BLANK,     S_BLANK,     S_BLANK,     S_BLANK, S_BLANK,     S_BLANK,
        S_LIGHTBULB, S_BLACK1, S_BLACKU, S_BLANK,     S_BLANK,     S_LIGHTBULB, S_BLANK, S_BLANK,     S_LIGHTBULB,
        S_BLANK,     S_BLANK,  S_BLANK,  S_BLACK2,    S_LIGHTBULB, S_BLANK,     S_BLANK, S_LIGHTBULB, S_BLANK,
        S_BLANK,     S_BLACKU, S_BLANK,  S_BLANK};

    game default_solution_test = game_new(square_default_solution_test);
    game_update_flags(default_solution_test);

    if (default_solution_test == NULL) {
        fprintf(stderr, "game_new fonction return NULL pointer\n");
        return false;
    }
    if (default_solution == NULL) {
        fprintf(stderr, "game_default_solution return NULL pointer\n");
        return false;
    }

    bool passed = false;
    if (game_is_over(default_solution) && game_equal(default_solution, default_solution_test)) passed = true;

    game_delete(default_solution);
    game_delete(default_solution_test);

    return passed;
}

/* ********** TEST GAME NEW ********** */

bool test_game_new(void) {
    square game_default[] = {S_BLANK,  S_BLANK,  S_BLACK1, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                             S_BLACK2, S_BLANK,  S_BLANK,  S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                             S_BLANK,  S_BLACKU, S_BLACK2, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                             S_BLANK,  S_BLACK1, S_BLACKU, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                             S_BLANK,  S_BLANK,  S_BLANK,  S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                             S_BLANK,  S_BLACKU, S_BLANK,  S_BLANK};

    game test_game = game_new(game_default);

    if (test_game == NULL) {
        fprintf(stderr, "game_new return NULL pointeur\n");
        return false;
    }

    for (uint i = 0; i < game_nb_cols(test_game); i++) {
        for (uint j = 0; j < game_nb_rows(test_game); j++) {
            if (game_get_square(test_game, i, j) != game_default[i * game_nb_cols(test_game) + j]) {
                game_delete(test_game);
                return false;
            }
        }
    }

    game_delete(test_game);
    return true;
}

/* ********** TEST GAME SET SQUARE ********** */

bool test_game_set_square(void) {
    game test_game = game_new_empty();

    for (int i = 0; i < game_nb_cols(test_game); i++) {
        for (int y = 0; y < game_nb_rows(test_game); y++) {
            char val = rand() % 256;
            game_set_square(test_game, i, y, val);

            if (game_get_square(test_game, i, y) != val) {
                game_delete(test_game);
                return false;
            }
        }
    }

    game_delete(test_game);
    return true;
}

/* ********** TEST GAME IS LIGHTBULB ********** */

bool test_game_is_lightbulb(void) {
    square test_square[] = {
        S_LIGHTBULB, S_LIGHTBULB, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK,  S_BLACK2,
        S_BLANK,     S_BLANK,     S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,     S_BLANK, S_BLANK,  S_BLACKU,
        S_BLACK2,    S_BLANK,     S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,     S_BLANK, S_BLACK1, S_BLACKU,
        S_BLANK,     S_BLANK,     S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,     S_BLANK, S_BLANK,  S_BLACK2,
        S_BLANK,     S_BLANK,     S_MARK,   S_BLANK, S_BLANK, S_BLANK, S_BLACKU,    S_BLANK, S_BLANK};

    game test_game = game_new(test_square);

    if (test_game == NULL) return false;

    if (!game_is_lightbulb(test_game, 0, 6)) {
        game_delete(test_game);
        return false;
    }

    game_update_flags(test_game);

    if (!game_is_lightbulb(test_game, 0, 0) || !game_is_lightbulb(test_game, 0, 1) ||
        !game_is_lightbulb(test_game, 0, 6)) {
        game_delete(test_game);
        return false;
    }

    if (game_is_lightbulb(test_game, 1, 0) || game_is_lightbulb(test_game, 4, 0) ||
        game_is_lightbulb(test_game, 6, 0)) {
        game_delete(test_game);
        return false;
    }

    game_delete(test_game);
    return true;
}

/* ********** TEST GAME IS LIGHTED ********** */

bool test_game_is_lighted(void) {
    square test_square[] = {S_LIGHTBULB, S_LIGHTBULB, S_BLACK1, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                            S_BLACK2,    S_BLANK,     S_BLANK,  S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                            S_BLANK,     S_BLACKU,    S_BLACK2, S_BLANK,  S_MARK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                            S_BLANK,     S_BLACK1,    S_BLACKU, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                            S_BLANK,     S_BLANK,     S_BLANK,  S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                            S_BLANK,     S_BLACKU,    S_BLANK,  S_BLANK};

    game test_game = game_new(test_square);

    if (test_game == NULL) return false;

    game_update_flags(test_game);

    bool passed = false;
    passed = game_is_lighted(test_game, 0, 0) && game_is_lighted(test_game, 0, 1) && game_is_lighted(test_game, 1, 0) &&
             game_is_lighted(test_game, 3, 1) && !game_is_lighted(test_game, 4, 0);

    game_delete(test_game);

    return passed;
}

/* ********** TEST GAME CHECK MOVE ********** */

bool test_game_check_move(void) {
    square test_square[] = {
        S_LIGHTBULB, S_LIGHTBULB, S_BLACK1, S_LIGHTBULB, S_MARK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
        S_BLANK,     S_BLANK,     S_BLANK,  S_LIGHTBULB, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACKU,
        S_BLACK2,    S_BLANK,     S_BLANK,  S_BLANK,     S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLACK1, S_BLACKU,
        S_BLANK,     S_BLANK,     S_BLANK,  S_BLANK,     S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
        S_BLANK,     S_BLANK,     S_BLANK,  S_BLANK,     S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    game test_game = game_new(test_square);

    if (test_game == NULL) return false;

    game_update_flags(test_game);

    bool passed = true;
    if (game_check_move(test_game, 0, 0, S_BLANK) == false)
        passed = false;
    else if (game_check_move(test_game, 0, 1, S_MARK) == false)
        passed = false;
    else if (game_check_move(test_game, 1, 0, S_LIGHTBULB) == false)
        passed = false;
    else if (game_check_move(test_game, 0, 2, S_MARK) == true)
        passed = false;
    else if (game_check_move(test_game, 0, 2, S_LIGHTBULB) == true)
        passed = false;
    else if (game_check_move(test_game, 0, 2, S_BLANK) == true)
        passed = false;
    else if (game_check_move(test_game, -1, 0, S_BLANK) == true)
        passed = false;
    else if (game_check_move(test_game, 7, 6, S_BLANK) == true)
        passed = false;

    game_delete(test_game);
    return passed;
}

/* ********** TEST GAME PLAY MOVE ********** */

bool test_game_play_move(void) {
    square test_square[] = {S_BLANK,  S_BLANK,  S_BLACK1, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                            S_BLACK2, S_BLANK,  S_BLANK,  S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                            S_BLANK,  S_BLACKU, S_BLACK2, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                            S_BLANK,  S_BLACK1, S_BLACKU, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                            S_BLANK,  S_BLANK,  S_BLANK,  S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                            S_BLANK,  S_BLACKU, S_BLANK,  S_BLANK};

    square solution_square[] = {S_LIGHTBULB, S_BLANK,  S_BLACK1, S_LIGHTBULB, S_BLANK,  S_BLANK,     S_BLANK,  S_BLANK,
                                S_LIGHTBULB, S_BLACK2, S_BLANK,  S_BLANK,     S_BLANK,  S_LIGHTBULB, S_BLANK,  S_BLANK,
                                S_LIGHTBULB, S_BLANK,  S_BLANK,  S_BLACKU,    S_BLACK2, S_BLANK,     S_BLANK,  S_BLANK,
                                S_BLANK,     S_BLANK,  S_BLANK,  S_LIGHTBULB, S_BLACK1, S_BLACKU,    S_BLANK,  S_BLANK,
                                S_LIGHTBULB, S_BLANK,  S_BLANK,  S_LIGHTBULB, S_BLANK,  S_BLANK,     S_BLANK,  S_BLACK2,
                                S_LIGHTBULB, S_BLANK,  S_BLANK,  S_LIGHTBULB, S_BLANK,  S_BLANK,     S_BLACKU, S_BLANK,
                                S_BLANK};

    game test_game = game_new(test_square);
    game solution_game = game_new(solution_square);

    if (test_game == NULL || solution_game == NULL) return false;

    game_update_flags(solution_game);

    game_play_move(test_game, 0, 0, S_LIGHTBULB);
    game_play_move(test_game, 0, 3, S_LIGHTBULB);
    game_play_move(test_game, 1, 1, S_LIGHTBULB);
    game_play_move(test_game, 1, 6, S_LIGHTBULB);
    game_play_move(test_game, 2, 2, S_LIGHTBULB);
    game_play_move(test_game, 3, 6, S_LIGHTBULB);
    game_play_move(test_game, 4, 4, S_LIGHTBULB);
    game_play_move(test_game, 5, 0, S_LIGHTBULB);
    game_play_move(test_game, 5, 5, S_LIGHTBULB);
    game_play_move(test_game, 6, 1, S_LIGHTBULB);

    bool passed = false;
    passed = game_equal(test_game, solution_game);

    game_delete(test_game);
    game_delete(solution_game);

    return passed;
}

/* ********** TEST GAME RESTART ********** */

bool test_game_restart(void) {
    square squares[] = {S_BLANK,  S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
                        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACKU,
                        S_BLACK2, S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLACK1, S_BLACKU,
                        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
                        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    game g_true;
    cgame g1;
    cgame g2;

    g_true = game_default();

    if (g_true == NULL) exit(EXIT_FAILURE);

    bool failed = false;

    for (uint i = 0; i < game_nb_cols(g_true); i++) {
        for (uint j = 0; j < game_nb_rows(g_true); j++) {
            if (game_get_square(g_true, i, j) == S_BLANK) {
                game_play_move(g_true, i, j, S_MARK);
            }
        }
    }

    game_restart(g_true);

    g1 = g_true;
    game g_true2 = game_default();
    g2 = g_true2;

    if (g1 == NULL || g2 == NULL || g_true2 == NULL) exit(EXIT_FAILURE);

    if (!game_equal(g1, g2)) {
        for (uint i = 0; i < game_nb_cols(g_true); i++) {
            for (uint j = 0; j < game_nb_rows(g_true); j++) {
                if (game_get_square(g1, i, j) != squares[i * game_nb_cols(g_true) + j]) {
                    failed = true;
                }
            }
        }
    }

    g1 = NULL;
    g2 = NULL;
    game_delete(g_true);
    game_delete(g_true2);
    return !(failed);
}

/* ********** USAGE ********** */

void usage(int argc, char *argv[]) {
    fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
    exit(EXIT_FAILURE);
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char *argv[]) {
    if (argc == 1) usage(argc, argv);

    srand(time(NULL));

    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool passed = false;
    if (strcmp("dummy", argv[1]) == 0)
        passed = test_dummy();
    else if (strcmp("game_default_solution", argv[1]) == 0)
        passed = test_game_default_solution();
    else if (strcmp("game_new", argv[1]) == 0)
        passed = test_game_new();
    else if (strcmp("game_set_square", argv[1]) == 0)
        passed = test_game_set_square();
    else if (strcmp("game_is_lightbulb", argv[1]) == 0)
        passed = test_game_is_lightbulb();
    else if (strcmp("game_is_lighted", argv[1]) == 0)
        passed = test_game_is_lighted();
    else if (strcmp("game_check_move", argv[1]) == 0)
        passed = test_game_check_move();
    else if (strcmp("game_play_move", argv[1]) == 0)
        passed = test_game_play_move();
    else if (strcmp("game_restart", argv[1]) == 0)
        passed = test_game_restart();
    else {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (passed) {
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    }

    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
}