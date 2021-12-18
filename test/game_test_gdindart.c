#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../libgame/game.h"
#include "../libgame/game_aux.h"
#include "../libgame/game_ext.h"

/*Util fonction*/
void print_bool(bool ok, char *text) {
    fprintf(stderr, "%s", text);
    if (ok) {
        fprintf(stderr, "true\n");
    } else {
        fprintf(stderr, "false\n");
    }
}

/*test_game_update_flags*/
bool test_game_update_flags() {
    bool ok = true;

    // test game creation
    game test_game = game_default();
    game_set_square(test_game, 0, 6, S_LIGHTBULB);

    // print_bool(ok, "calling update flags, ok = ");
    // update flags
    game_update_flags(test_game);

    int x_check, y_check;
    x_check = 0;
    y_check = 6;
    print_bool(ok, "start test, ok = ");

    while (x_check < game_nb_cols(test_game))  // colone avant le mur
    {
        if (game_is_black(test_game, x_check, 6)) {
            x_check++;
            break;
        }
        ok = ok && game_is_lighted(test_game, x_check, 6);
        fprintf(stderr, "coord (%d, 6), ", x_check);
        print_bool(ok, "ok = ");
        x_check++;
    }
    print_bool(ok, "after 'colone avant le mur' ok = ");

    while (x_check < game_nb_cols(test_game))  // colone après le mur
    {
        if (game_is_black(test_game, x_check, 6)) {
            break;
        }
        ok = ok && !game_is_lighted(test_game, x_check, 6);
        fprintf(stderr, "coord (%d, 6), ", x_check);
        print_bool(ok, "ok = ");
        x_check++;
    }
    print_bool(ok, "after 'colone après le mur' ok = ");

    while (y_check >= 0)  // ligne avant le mur
    {
        if (game_is_black(test_game, 0, y_check)) {
            y_check--;
            break;
        }
        ok = ok && game_is_lighted(test_game, 0, y_check);
        fprintf(stderr, "coord (0, %d), ", y_check);
        print_bool(ok, "ok = ");
        y_check--;
    }
    print_bool(ok, "after 'ligne avant le mur' ok = ");

    while (y_check >= 0)  // ligne après le mur
    {
        if (game_is_black(test_game, 0, y_check)) {
            break;
        }
        ok = ok && !game_is_lighted(test_game, 0, y_check);
        fprintf(stderr, "coord (0, %d), ", y_check);
        print_bool(ok, "ok = ");
        y_check--;
    }
    print_bool(ok, "after 'ligne après le mur' ok = ");
    // Error flags
    game_set_square(test_game, 0, 3, S_LIGHTBULB);

    game_update_flags(test_game);
    print_bool(ok, "Beofre test list: ");

    if (!game_has_error(test_game, 0, 3) || !game_is_lighted(test_game, 0, 3)) {
        fprintf(stderr, "test 1\n");
        ok = false;
    }
    if (!game_has_error(test_game, 0, 6) || !game_is_lighted(test_game, 0, 6)) {
        fprintf(stderr, "test 2\n");
        ok = false;
    }
    if (game_has_error(test_game, 0, 4) || !game_is_lighted(test_game, 0, 4)) {
        fprintf(stderr, "test 3\n");
        ok = false;
    }
    if (game_has_error(test_game, 0, 5) || !game_is_lighted(test_game, 0, 5)) {
        fprintf(stderr, "test 4\n");
        ok = false;
    }

    game_set_square(test_game, 0, 3, S_MARK);
    game_update_flags(test_game);

    if (game_has_error(test_game, 0, 3) || !game_is_lighted(test_game, 0, 3)) {
        fprintf(stderr, "test 5\n");
        ok = false;
    }

    game_set_square(test_game, 3, 0, S_LIGHTBULB);
    game_set_square(test_game, 5, 0, S_LIGHTBULB);
    game_update_flags(test_game);

    if (!game_has_error(test_game, 4, 0) || game_is_lighted(test_game, 4, 0)) {
        print_bool(!game_has_error(test_game, 4, 0), "error!");
        print_bool(game_is_lighted(test_game, 4, 0), "lighted");
        fprintf(stderr, "test 6");
        ok = false;
    }

    game_delete(test_game);

    game empty_game = game_new_empty();
    game_update_flags(empty_game);

    for (int i = 0; i < game_nb_cols(empty_game); i++) {
        for (int y = 0; y < game_nb_rows(empty_game); y++) {
            if (game_get_flags(empty_game, i, y) != 0) {
                ok = false;
            }
        }
    }

    game_delete(empty_game);
    return ok;
}

/*test_game_default*/
bool test_game_default() {
    // create test game
    square init_value_test[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK,  S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACKU,
        S_BLACK2, S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLACK1, S_BLACKU,
        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    game test_game = game_new(init_value_test);

    game default_game = game_default();

    if (default_game == NULL) {
        return false;
    }

    bool ok = game_equal(test_game, default_game);
    game_delete(test_game);
    game_delete(default_game);
    return ok;
}

/*test_game_has_error*/
bool test_game_has_error() {
    bool ok = true;

    square init_test_value[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_LIGHTBULB, S_BLANK, S_BLACK1, S_LIGHTBULB, S_BLANK, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK,  S_BLACK2,
        S_BLANK,     S_BLANK, S_BLANK,  S_BLANK,     S_BLANK, S_BLANK, S_BLANK,     S_BLANK, S_BLANK,  S_BLACKU,
        S_BLACK2,    S_BLANK, S_BLANK,  S_BLANK,     S_BLANK, S_BLANK, S_BLANK,     S_BLANK, S_BLACK1, S_BLACKU,
        S_BLANK,     S_BLANK, S_BLANK,  S_BLANK,     S_BLANK, S_BLANK, S_BLANK,     S_BLANK, S_BLANK,  S_BLACK2,
        S_BLANK,     S_BLANK, S_BLANK,  S_BLANK,     S_BLANK, S_BLANK, S_BLACKU,    S_BLANK, S_BLANK};

    game test_game = game_new(init_test_value);
    game_update_flags(test_game);

    ok = game_has_error(test_game, 0, 6);
    // print_bool(ok, "test1: ");
    ok = game_has_error(test_game, 0, 3) && ok;
    // print_bool(ok, "test2: ");
    ok = !game_has_error(test_game, 0, 0) && ok;
    // print_bool(ok, "test3: ");
    game_delete(test_game);
    return ok;
}

/*test_game_is_marked*/
bool test_game_is_marked() {
    square init_test_value[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK,  S_BLANK, S_BLACK1, S_BLANK, S_MARK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACKU,
        S_BLACK2, S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_MARK,  S_BLANK,  S_BLANK, S_BLACK1, S_BLACKU,
        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    game test_game = game_new(init_test_value);
    game_update_flags(test_game);
    bool ok = game_is_marked(test_game, 0, 4) && game_is_marked(test_game, 3, 4) && !game_is_marked(test_game, 0, 6);

    game_delete(test_game);
    return ok;
}

/*test_game_is_black*/
bool test_game_is_black() {
    square init_test_value[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK,  S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACKU,
        S_BLACK2, S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLACK1, S_BLACKU,
        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLANK,  S_BLANK, S_BLANK,  S_BLACK2,
        S_BLANK,  S_BLANK, S_BLANK,  S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    game test_game = game_new(init_test_value);
    game_update_flags(test_game);

    char mask = (char)247;  // 11110111
    char check = (char)255;
    bool ok = true;

    for (int i = 0; i < game_nb_cols(test_game); i++) {
        for (int y = 0; y < game_nb_rows(test_game); y++) {
            char tiles = game_get_square(test_game, i, y);
            ok = ok && (((tiles | mask) == check) == game_is_black(test_game, i, y));
        }
    }
    game_delete(test_game);
    return ok;
}

/*test_game_set_square*/
bool test_game_get_square() {
    game test_game = game_default_solution();

    for (int i = 0; i < game_nb_cols(test_game); i++) {
        for (int y = 0; y < game_nb_rows(test_game); y++) {
            char val = game_get_flags(test_game, i, y) + game_get_state(test_game, i, y);

            if (game_get_square(test_game, i, y) != val) {
                game_delete(test_game);
                return false;
            }
        }
    }
    game_delete(test_game);
    return true;
}

/*test_game_equal*/
bool test_game_equal() {
    game base_game = game_default();
    game_update_flags(base_game);

    game equal_game = game_default();
    game_update_flags(equal_game);

    game diff1_game = game_default_solution();
    game_update_flags(diff1_game);

    square solution_value[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_LIGHTBULB, S_BLANK,  S_BLACK1, S_LIGHTBULB, S_BLANK,     S_BLANK,     S_BLANK, S_BLANK,     S_LIGHTBULB,
        S_BLACK2,    S_BLANK,  S_BLANK,  S_BLANK,     S_LIGHTBULB, S_BLANK,     S_BLANK, S_LIGHTBULB, S_BLANK,
        S_BLANK,     S_BLACKU, S_BLACK2, S_BLANK,     S_BLANK,     S_BLANK,     S_BLANK, S_BLANK,     S_BLANK,
        S_LIGHTBULB, S_BLACK1, S_BLACKU, S_BLANK,     S_BLANK,     S_LIGHTBULB, S_BLANK, S_BLANK,     S_LIGHTBULB,
        S_BLANK,     S_BLANK,  S_BLANK,  S_BLACK2,    S_LIGHTBULB, S_BLANK,     S_BLANK, S_LIGHTBULB, S_BLANK,
        S_BLANK,     S_BLACKU, S_BLANK,  S_BLANK};

    game diff2_game = game_new(solution_value);

    bool ok = game_equal(base_game, equal_game);
    ok = ok && !game_equal(base_game, diff1_game);
    ok = ok && !game_equal(diff1_game, diff2_game);
    ok = ok && !game_equal(base_game, diff2_game);

    game_update_flags(diff2_game);

    ok = ok && game_equal(diff2_game, diff1_game);

    game_play_move(diff2_game, 0, 3, S_LIGHTBULB);
    game_play_move(diff2_game, 0, 6, S_LIGHTBULB);

    ok = ok && !game_equal(diff1_game, diff2_game);

    game_delete(base_game);
    game_delete(equal_game);
    game_delete(diff1_game);
    game_delete(diff2_game);
    return ok;
}

/*test_game_new_empty*/
bool test_game_new_empty() {
    game blank_game = game_new_empty();

    if (blank_game == NULL) {
        return false;
    }

    for (int i = 0; i < game_nb_cols(blank_game); i++) {
        for (int y = 0; y < game_nb_rows(blank_game); y++) {
            if (game_get_square(blank_game, i, y) != S_BLANK) {
                return false;
            }
        }
    }
    game_delete(blank_game);
    return true;
}

/*Dummy test*/

bool test_dummy() { return true; }

/*Usage*/
void usage(int argc, char *argv[]) {
    fprintf(stderr, "Usage : %s <test_name>\n", argv[0]);
    exit(EXIT_FAILURE);
}

/*Main*/
int main(int argc, char *argv[]) {
    if (argc == 1) {
        usage(argc, argv);
    }

    srand(time(NULL));

    fprintf(stderr, "Starting test '%s'.\n", argv[1]);
    bool passed = false;
    if (strcmp("dummy", argv[1]) == 0) {
        passed = test_dummy();
    } else if (strcmp("game_update_flags", argv[1]) == 0) {
        passed = test_game_update_flags();
    } else if (strcmp("game_default", argv[1]) == 0) {
        passed = test_game_default();
    } else if (strcmp("game_has_error", argv[1]) == 0) {
        passed = test_game_has_error();
    } else if (strcmp("game_is_marked", argv[1]) == 0) {
        passed = test_game_is_marked();
    } else if (strcmp("game_is_black", argv[1]) == 0) {
        passed = test_game_is_black();
    } else if (strcmp("game_get_square", argv[1]) == 0) {
        passed = test_game_get_square();
    } else if (strcmp("game_equal", argv[1]) == 0) {
        passed = test_game_equal();
    } else if (strcmp("game_new_empty", argv[1]) == 0) {
        passed = test_game_new_empty();
    } else {
        fprintf(stderr, "Error: unkown test name %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /*Test result*/
    if (passed) {
        fprintf(stderr, "Test %s passed\n", argv[1]);
        exit(EXIT_SUCCESS);
    } else {
        fprintf(stderr, "Test %s failed\n", argv[1]);
        exit(EXIT_FAILURE);
    }
}