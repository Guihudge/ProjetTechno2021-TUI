#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"

void crit_error(char *err) {
    fprintf(stderr, "[CRITICAL] %s\n", err);
    exit(EXIT_FAILURE);
}

void test_error(cgame g) {
    for (uint j = 0; j < DEFAULT_SIZE; j++) {
        for (uint i = 0; i < DEFAULT_SIZE; i++) {
            if (game_has_error(g, i, j)) {
                printf("Error at light bulb (%u, %u)\n", i, j);
            }
        }
    }
}

void scan_and_play_move(game g, square s) {
    uint i, j;
    scanf(" %d %d", &i, &j);
    if (i < 0 || i >= DEFAULT_SIZE || j < 0 || j >= DEFAULT_SIZE) {
        printf("Invalid position\n");
    } else if (game_check_move(g, i, j, s)) {
        printf("> action: play move in (%u, %u)\n", i, j);
        game_play_move(g, i, j, s);
    } else {
        printf("Invalid move\n");
    }
}

void print_help() {
    printf("- press 'l <i> <j>' to put a light buld at square (i, j)\n");
    printf("- press 'm <i> <j>' to put a mark at square (i, j)\n");
    printf("- press 'b <i> <j>' to blank square (i, j)\n");
    printf("- press 'r' to restart\n");
    printf("- press 'q' to quit\n");
}

int main(void) {
    bool win = false;
    game actual_game = game_default();

    while (!win) {
        game_print(actual_game);
        test_error(actual_game);

        char cmd;
        int ret;

        printf("> ? [h for help]\n");
        ret = scanf(" %c", &cmd);

        if (ret != 1) {
            crit_error("Unable to prase argument");
        }
        if (cmd == 'h') {
            printf("> action: help\n");
            print_help();
        } else if (cmd == 'r') {
            printf("> action: restart\n");
            game_restart(actual_game);
        } else if (cmd == 'q') {
            printf("> action: quit\n");
            game_delete(actual_game);
            printf("shame\n");
            return EXIT_SUCCESS;
        } else if (cmd == 'l')
            scan_and_play_move(actual_game, S_LIGHTBULB);
        else if (cmd == 'm')
            scan_and_play_move(actual_game, S_MARK);
        else if (cmd == 'b')
            scan_and_play_move(actual_game, S_BLANK);
        else
            printf("undefined command '%c', use h for help.\n", cmd);

        win = game_is_over(actual_game);
    }

    game_print(actual_game);
    printf("Congratulation !\n");

    return EXIT_SUCCESS;
}