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

    if(default_solution_test == NULL) fprintf(stderr, "game_new fonction return NULL pointer\n");
    if(default_solution == NULL) fprintf(stderr, "game_default_solution return NULL pointer\n");

    bool passed = false;
    if(game_is_over(default_solution) && game_equal(default_solution, default_solution_test))
        passed = true;

    game_delete(default_solution);
    game_delete(default_solution_test);

    return passed;
}

/* ********** TEST GAME NEW ********** */

bool test_game_new(void) {
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
    return true;
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