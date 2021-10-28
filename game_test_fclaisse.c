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
    return true;
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