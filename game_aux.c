#include <stdio.h>
#include <stdlib.h>

#include "game_aux.h"
#include "game.h"

void game_print(cgame g) {
    if (g == NULL) {
        return;
    }

    printf("   ");
    for(uint i = 0; i < DEFAULT_SIZE; i++) printf("%u", i);
    printf("\n   ");
    for(uint i = 0; i < DEFAULT_SIZE; i++) printf("-");
    printf("\n");

    for (uint i = 0; i < DEFAULT_SIZE; i++) {
        printf("%u |", i);
        for (uint j = 0; j < DEFAULT_SIZE; j++) {
            square tiles = game_get_square(g, i, j);
            if (tiles > 16) {
                tiles = tiles - game_get_flags(g, i, j);
            }

            switch (tiles) {
            case S_BLANK:
                printf(" ");
                break;
            case S_LIGHTBULB:
                printf("*");
                break;
            case S_MARK:
                printf("-");
                break;
            case S_BLACK:
                printf("0");
                break;
            case S_BLACK1:
                printf("1");
                break;
            case S_BLACK2:
                printf("2");
                break;
            case S_BLACK3:
                printf("3");
                break;
            case S_BLACK4:
                printf("4");
                break;
            case S_BLACKU:
                printf("w");
                break;
            case F_LIGHTED:
                printf(".");
                break;
            case F_ERROR:
                printf(" ");
                break;
            default:
                printf("?");
                break;
            }
        }
        printf("|\n");
    }
    printf("   ");
    for(uint i = 0; i < DEFAULT_SIZE; i++) printf("-");
    printf("\n");
}

game game_default(void) {
    //new blank game
    square init_value[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK
    };

    return game_new(init_value);
}

game game_default_solution(void) {
    //Base solution tab
    square solution_value[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_LIGHTBULB, S_BLANK, S_BLACK1, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_LIGHTBULB, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_LIGHTBULB,
        S_BLANK, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_LIGHTBULB,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK,
        S_LIGHTBULB, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_LIGHTBULB, S_BLANK,
        S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK
    };

    game solution_game = game_new(solution_game);
    game_update_flags(solution_game);

    return solution_game;
}
