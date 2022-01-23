#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libgame/game.h"
#include "../libgame/game_aux.h"
#include "../libgame/game_ext.h"

bool test_dummy() { return true; }

bool test_game_print() {
    square test[] = {S_LIGHTBULB, S_BLANK,  S_BLACK1, S_MARK,      S_LIGHTBULB, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK,
                     S_BLACK2,    S_BLANK,  S_BLANK,  S_BLANK,     S_BLANK,     S_BLANK, S_BLANK,     S_BLANK, S_BLANK,
                     S_BLANK,     S_BLACKU, S_BLACK2, S_BLANK,     S_BLANK,     S_BLANK, S_BLANK,     S_BLANK, S_BLANK,
                     S_LIGHTBULB, S_BLACK1, S_BLACK0, S_LIGHTBULB, S_BLANK,     S_BLANK, S_BLANK,     S_BLANK, S_BLANK,
                     S_BLANK,     S_BLACK4, S_BLANK,  S_BLACK3,    S_BLANK,     S_BLANK, S_BLANK,     S_BLANK, S_BLANK,
                     S_BLANK,     S_BLACKU, S_BLANK,  S_LIGHTBULB};
    game g2 = game_new(test);
    game_update_flags(g2);
    game_print(g2);
    game_delete(g2);
    return true;
}

bool test_game_get_flags() {
    square test_jeu[] = {S_LIGHTBULB, S_BLANK,  S_BLACK1,    S_MARK,      S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLACK2,    S_BLANK,  S_BLANK,     S_BLANK,     S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLANK,     S_BLACKU, S_BLACK2,    S_BLANK,     S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_LIGHTBULB, S_BLACK1, S_BLACK0,    S_LIGHTBULB, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLANK,     S_BLACK4, S_BLANK,     S_BLACK3,    S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLANK,     S_BLACKU, S_LIGHTBULB, S_LIGHTBULB};
    game g2 = game_new(test_jeu);
    game_update_flags(g2);
    square test;
    test = game_get_flags(g2, 0, 0);
    if (test != F_LIGHTED) {
        game_delete(g2);
        return false;
    }
    test = game_get_flags(g2, 0, 1);
    if (test != F_LIGHTED) {
        game_delete(g2);
        return false;
    }
    test = game_get_flags(g2, 4, 1);
    if (test != F_ERROR) {
        game_delete(g2);
        return false;
    }
    test = game_get_flags(g2, 6, 6);
    if (test != (F_ERROR + F_LIGHTED)) {
        game_delete(g2);
        return false;
    }
    game_delete(g2);
    return true;
}

bool test_game_get_black_number() {
    square test[] = {S_LIGHTBULB, S_BLANK, S_BLACK1, S_MARK,  S_BLANK, S_BLANK, S_BLANK,  S_BLANK,  S_BLANK,  S_BLACK2,
                     S_BLANK,     S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK,  S_BLANK,  S_BLACKU,
                     S_BLACK2,    S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK,  S_BLACK1, S_BLACK0,
                     S_BLANK,     S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLACK4, S_BLANK,  S_BLACK3,
                     S_BLANK,     S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK,  S_BLANK};

    game g2 = game_new(test);
    // game_update_flags(g2);
    int t1 = game_get_black_number(g2, 0, 2);
    int t2 = game_get_black_number(g2, 1, 2);
    int t3 = game_get_black_number(g2, 5, 4);
    int t4 = game_get_black_number(g2, 5, 2);
    int t = game_get_black_number(g2, 4, 1);
    int t5 = game_get_black_number(g2, 6, 4);
    fprintf(stderr, "t = %d, t1 = %d, t2 = %d, t3 = %d, t4 = %d, t5 = %d\n", t, t1, t2, t3, t4, t5);
    if (t != 0 || t1 != 1 || t2 != 2 || t3 != 3 || t4 != 4 || t5 != -1) {
        game_delete(g2);
        return false;
    }
    game_delete(g2);
    return true;
}

bool test_game_get_state() {
    square test[] = {S_LIGHTBULB, S_BLANK, S_BLACK1, S_MARK,  S_BLANK, S_BLANK,  S_BLANK,  S_BLANK,  S_BLANK,  S_BLACK2,
                     S_BLANK,     S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLACK0, S_BLANK,  S_BLANK,  S_BLANK,  S_BLACKU,
                     S_BLACK2,    S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK,  S_BLANK,  S_BLANK,  S_BLACK1, S_BLACKU,
                     S_BLANK,     S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK,  S_BLANK,  S_BLACK4, S_BLANK,  S_BLACK3,
                     S_BLANK,     S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK,  S_BLACKU, S_BLANK,  S_BLANK};

    game g2 = game_new(test);
    // game_update_flags(g2);
    if (game_get_state(g2, 0, 0) != S_LIGHTBULB) {
        fprintf(stderr, "S_LIGHTBULB failed");
        game_delete(g2);
        return false;
    }
    if (game_get_state(g2, 0, 1) != S_BLANK) {
        fprintf(stderr, "S_BLANK failed");
        game_delete(g2);
        return false;
    }
    if (game_get_state(g2, 0, 2) != S_BLACK1) {
        fprintf(stderr, "S_BLACK1 failed");
        game_delete(g2);
        return false;
    }
    if (game_get_state(g2, 0, 3) != S_MARK) {
        fprintf(stderr, "S_MARK failed");
        game_delete(g2);
        return false;
    }
    if (game_get_state(g2, 1, 2) != S_BLACK2) {
        fprintf(stderr, "S_BLACK2 failed");
        game_delete(g2);
        return false;
    }
    if (game_get_state(g2, 4, 1) != S_BLACKU) {
        fprintf(stderr, "S_BLACKU failed");
        game_delete(g2);
        return false;
    }
    if (game_get_state(g2, 5, 4) != S_BLACK3) {
        fprintf(stderr, "S_BLACK3 failed");
        game_delete(g2);
        return false;
    }
    if (game_get_state(g2, 5, 2) != S_BLACK4) {
        fprintf(stderr, "S_BLACK4 failed");
        game_delete(g2);
        return false;
    }
    if (game_get_state(g2, 2, 1) != S_BLACK0) {
        fprintf(stderr, "S_BLACK0 failed");
        game_delete(g2);
        return false;
    }
    game_delete(g2);
    return true;
}

bool test_game_is_over() {
    square test[] = {S_BLANK,  S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
                     S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACKU,
                     S_BLACK2, S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLACK1, S_BLACKU,
                     S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
                     S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    game g2 = game_new(test);

    square solution_test[] = {S_LIGHTBULB, S_BLANK,     S_BLACK1,    S_LIGHTBULB, S_BLANK,     S_BLANK,     S_BLANK,
                              S_BLANK,     S_LIGHTBULB, S_BLACK2,    S_BLANK,     S_BLANK,     S_BLANK,     S_LIGHTBULB,
                              S_BLANK,     S_BLANK,     S_LIGHTBULB, S_BLANK,     S_BLANK,     S_BLACKU,    S_BLACK2,
                              S_BLANK,     S_BLANK,     S_BLANK,     S_BLANK,     S_BLANK,     S_BLANK,     S_LIGHTBULB,
                              S_BLACK1,    S_BLACKU,    S_BLANK,     S_BLANK,     S_LIGHTBULB, S_BLANK,     S_BLANK,
                              S_LIGHTBULB, S_BLANK,     S_BLANK,     S_BLANK,     S_BLACK2,    S_LIGHTBULB, S_BLANK,
                              S_BLANK,     S_LIGHTBULB, S_BLANK,     S_BLANK,     S_BLACKU,    S_BLANK,     S_BLANK};
    game sol_test = game_new(solution_test);

    if (game_is_over(sol_test)) {
        game_delete(g2);
        game_delete(sol_test);
        return false;
    }

    game_update_flags(sol_test);

    bool oktest;

    if (game_is_over(g2)) {
        game_delete(g2);
        game_delete(sol_test);
        return false;
    }
    if (!game_is_over(sol_test)) {
        game_delete(g2);
        game_delete(sol_test);
        return false;
    }
    game_play_move(sol_test, 0, 1, S_LIGHTBULB);

    if (game_is_over(sol_test)) {
        game_delete(g2);
        game_delete(sol_test);
        return false;
    }
    game_play_move(sol_test, 0, 1, S_BLANK);

    for (int i = 0; i < game_nb_cols(sol_test); i++) {
        for (int j = 0; j < game_nb_rows(sol_test); j++) {
            if (game_is_lightbulb(sol_test, i, j)) {
                game_play_move(g2, i, j, S_LIGHTBULB);
                if (!game_equal(g2, sol_test)) {
                    if (game_is_over(g2)) {
                        game_delete(g2);
                        game_delete(sol_test);
                        return false;
                    }
                } else if (game_equal(g2, sol_test)) {
                    oktest = game_is_over(g2);
                    game_delete(g2);
                    game_delete(sol_test);
                    return oktest;
                }
            }
        }
    }
    oktest = game_is_over(g2);
    game_delete(sol_test);
    game_delete(g2);
    return oktest;
}

bool test_game_is_blanck() {
    square test[] = {S_LIGHTBULB, S_BLANK, S_BLACK1, S_MARK,  S_BLANK, S_BLANK, S_BLANK,  S_BLANK,  S_BLANK,  S_BLACK2,
                     S_BLANK,     S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK,  S_BLANK,  S_BLACKU,
                     S_BLACK2,    S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK,  S_BLACK1, S_BLACKU,
                     S_BLANK,     S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLACK4, S_BLANK,  S_BLACK3,
                     S_BLANK,     S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK,  S_BLANK};

    game g2 = game_new(test);
    game_update_flags(g2);

    bool oktest = !game_is_blank(g2, 0, 0) && game_is_blank(g2, 0, 1) && !game_is_blank(g2, 0, 2) &&
                  !game_is_blank(g2, 0, 3) && !game_is_blank(g2, 1, 2) && !game_is_blank(g2, 4, 1) &&
                  !game_is_blank(g2, 5, 2) && !game_is_blank(g2, 5, 4);
    game_delete(g2);
    return oktest;
}
bool test_game_delete() {
    square test[] = {S_BLANK,  S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
                     S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACKU,
                     S_BLACK2, S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLACK1, S_BLACKU,
                     S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
                     S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};
    game g2 = game_new(test);
    if (g2 == NULL) {
        return false;
    }
    game_delete(g2);
    return true;
}

bool test_game_copy() {
    square test[] = {S_LIGHTBULB, S_LIGHTBULB, S_BLACK1, S_MARK,   S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                     S_BLACK2,    S_BLANK,     S_BLANK,  S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                     S_BLANK,     S_BLACK0,    S_BLACK2, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                     S_BLANK,     S_BLACK3,    S_BLACKU, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                     S_BLANK,     S_BLANK,     S_BLANK,  S_BLACK4, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                     S_BLANK,     S_BLACKU,    S_BLANK,  S_BLANK};

    game g2 = game_new_ext(DEFAULT_SIZE, DEFAULT_SIZE, test, true);
    uint nbcols = game_nb_cols(g2);
    uint nbrows = game_nb_rows(g2);
    bool wrap = game_is_wrapping(g2);
    if (g2 == NULL) {
        return false;
    }
    game g3 = game_copy(g2);
    if (g3 == NULL) {
        return false;
    }
    bool oktest;
    if (!game_equal(g3, g2) && game_nb_cols(g3) == nbcols && game_nb_rows(g3) == nbrows &&
        wrap == game_is_wrapping(g3)) {
        game_delete(g2);
        game_delete(g3);
        return false;
    }
    game_update_flags(g2);
    game g4 = game_copy(g2);
    if (g4 == NULL) {
        return false;
    }
    oktest = (game_equal(g2, g4) && game_nb_cols(g4) == nbcols && game_nb_rows(g4) == nbrows &&
              wrap == game_is_wrapping(g3));

    game_delete(g2);
    game_delete(g3);
    game_delete(g4);
    return oktest;
}

bool test_game_new_empty_ext() {
    uint i = rand() % 20 + 1;
    uint j = rand() % 20 + 1;
    bool wrapping = true;
    game test = game_new_empty_ext(i, j, wrapping);
    if (test == NULL) {
        return false;
    }
    if (game_nb_cols(test) != j || game_nb_rows(test) != i || game_is_wrapping(test) != wrapping) {
        return false;
    }
    for (int l = 0; l < i; l++) {
        for (int m = 0; m < j; m++) {
            if (game_get_square(test, l, m) != S_BLANK) {
                return false;
            }
        }
    }
    game_delete(test);
    return true;
}

bool test_game_undo() {
    square test_square[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK,  S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACKU,
        S_BLACK2, S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLACK1, S_BLACKU,
        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    game test_game = game_new_ext(DEFAULT_SIZE, DEFAULT_SIZE, test_square, false);

    game copy_test = game_copy(test_game);
    game_play_move(test_game, 0, 0, S_LIGHTBULB);
    game copy_test2 = game_copy(test_game);
    game_play_move(test_game, 6, 6, S_LIGHTBULB);
    game_undo(test_game);
    if (!game_equal(test_game, copy_test2)) {
        game_delete(test_game);
        game_delete(copy_test);
        game_delete(copy_test2);
        return false;
    }
    game_undo(test_game);
    if (!game_equal(test_game, copy_test)) {
        game_delete(test_game);
        game_delete(copy_test);
        game_delete(copy_test2);
        return false;
    }
    game_delete(test_game);
    game_delete(copy_test);
    game_delete(copy_test2);
    return true;
}
void usage(int argc, char *argv[]) {
    fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        usage(argc, argv);
    }
    fprintf(stderr, "Starting test '%s'.\n", argv[1]);
    bool ok = false;
    if (strcmp("dummy", argv[1]) == 0) {
        ok = test_dummy();
    } else if (strcmp("game_print", argv[1]) == 0) {
        ok = test_game_print();
    } else if (strcmp("game_get_flags", argv[1]) == 0) {
        ok = test_game_get_flags();
    } else if (strcmp("game_get_black_number", argv[1]) == 0) {
        ok = test_game_get_black_number();
    } else if (strcmp("game_get_state", argv[1]) == 0) {
        ok = test_game_get_state();
    } else if (strcmp("game_is_over", argv[1]) == 0) {
        ok = test_game_is_over();
    } else if (strcmp("game_is_blanck", argv[1]) == 0) {
        ok = test_game_is_blanck();
    } else if (strcmp("game_delete", argv[1]) == 0) {
        ok = test_game_delete();
    } else if (strcmp("game_copy", argv[1]) == 0) {
        ok = test_game_copy();
    } else if (strcmp("game_new_empty_ext", argv[1]) == 0) {
        ok = test_game_new_empty_ext();
    } else if (strcmp("game_undo", argv[1]) == 0) {
        ok = test_game_undo();
    } else {
        fprintf(stderr, "Error: unkown test name %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (ok) {
        fprintf(stderr, "Test %s passed\n", argv[1]);
        exit(EXIT_SUCCESS);
    } else {
        fprintf(stderr, "Test %s failed\n", argv[1]);
        exit(EXIT_FAILURE);
    }
}
