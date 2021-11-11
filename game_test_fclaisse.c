#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"

/* ********** TEST DUMMY ********** */

bool test_dummy(void) { return true; }

/* ********** TEST GAME DEFAULT SOLUTION ********** */

bool test_game_default_solution(void) {
    game default_solution = game_default_solution();
    square square_default_solution_test[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_LIGHTBULB, S_BLANK, S_BLACK1, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_LIGHTBULB, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_LIGHTBULB,
        S_BLANK, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_LIGHTBULB,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK,
        S_LIGHTBULB, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_LIGHTBULB, S_BLANK,
        S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK
    };

    game default_solution_test = game_new(square_default_solution_test);
    game_update_flags(default_solution_test);

    if(default_solution_test == NULL) {
        fprintf(stderr, "game_new fonction return NULL pointer\n");
        return false;
    }
    if(default_solution == NULL) {
        fprintf(stderr, "game_default_solution return NULL pointer\n");
        return false;
    }

    bool passed = false;
    if(game_is_over(default_solution) && game_equal(default_solution, default_solution_test))
        passed = true;

    game_delete(default_solution);
    game_delete(default_solution_test);

    return passed;
}

/* ********** TEST GAME NEW ********** */

bool test_game_new(void) {
    square game_default[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK
    };

    game test_game = game_new(game_default);

    if(test_game == NULL) {
        fprintf(stderr, "game_new return NULL pointeur\n");
        return false;
    }

    for(uint i = 0; i < DEFAULT_SIZE; i++) {
        for(uint j = 0; j < DEFAULT_SIZE; j++) {
            if(game_get_square(test_game, i, j) != game_default[i * DEFAULT_SIZE + j])
                return false;
        }
    }

    game_delete(test_game);

    return true;
}

/* ********** TEST GAME SET SQUARE ********** */

bool test_game_set_square(void) {
    return true;
}

/* ********** TEST GAME IS LIGHTBULB ********** */

bool test_game_is_lightbulb(void) {
    return true;
}

/* ********** TEST GAME IS LIGHTED ********** */

bool test_game_is_lighted(void) {
    square test_square[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_LIGHTBULB, S_LIGHTBULB, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_MARK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK
    };

    game test_game = game_new(test_square);

    if(test_game == NULL)
        return false;

    game_update_flags(test_game);

    return game_is_lighted(test_game, 0, 0) && game_is_lighted(test_game, 0, 1) && game_is_lighted(test_game, 1, 0) && game_is_lighted(test_game, 3, 1) && !game_is_lighted(test_game, 4, 0);
}

/* ********** TEST GAME CHECK MOVE ********** */

bool test_game_check_move(void) {
    return true;
}

/* ********** TEST GAME PLAY MOVE ********** */

bool test_game_play_move(void) {
    return true;
}

/* ********** TEST GAME restart ********** */

bool test_game_restart(void) {
    square default_square[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK
    };

    square solution_square[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_LIGHTBULB, S_BLANK, S_BLACK1, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_LIGHTBULB, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_LIGHTBULB,
        S_BLANK, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_LIGHTBULB,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK,
        S_LIGHTBULB, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_LIGHTBULB, S_BLANK,
        S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK
    };

    game solution_game = game_new(solution_square);
    game_update_flags(solution_game);
    game_restart(solution_game);

    if(solution_game == NULL)
        return false;

    for(uint i = 0; i < DEFAULT_SIZE; i++) {
        for(uint j = 0; j < DEFAULT_SIZE; j++) {
            if(game_get_square(solution_game, i, j) != default_square[i * DEFAULT_SIZE + j])
                return false;
        }
    }

    game_delete(solution_game);

    return true;
}

/* ********** USAGE ********** */

void usage(int argc, char *argv[]) {
    fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
    exit(EXIT_FAILURE);
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char *argv[]) {

    if(argc == 1) 
        usage(argc, argv);

    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool passed = false;
    if(strcmp("dummy", argv[1]) == 0)
        passed = test_dummy();
    else if(strcmp("game_default_solution", argv[1]) == 0)
        passed = test_game_default_solution();
    else if(strcmp("game_new", argv[1]) == 0)
        passed = test_game_new();
    else if(strcmp("game_set_square", argv[1]) == 0)
        passed = test_game_set_square();
    else if(strcmp("game_is_lightbulb", argv[1]) == 0)
        passed = test_game_is_lightbulb();
    else if(strcmp("game_is_lighted", argv[1]) == 0)
        passed = test_game_is_lighted();
    else if(strcmp("game_check_move", argv[1]) == 0)
        passed = test_game_check_move();
    else if(strcmp("game_play_move", argv[1]) == 0)
        passed = test_game_play_move();
    else if(strcmp("game_restart", argv[1]) == 0)
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