#include <stdio.h>
#include <stdlib.h>

#include "game_aux.h"
#include "game.h"

void game_print(cgame g)
{
    if (g == NULL)
    {
        exit(-1);
    }

    int i_cpt = 0;
    printf("\n   0123456\n");
    printf("   ------- ");
    printf("\n%d |", i_cpt);
    i_cpt++;

    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        for (int j = 0; j < DEFAULT_SIZE; j++)
        {
            square tiles = game_get_square(g, i, j);
            if (tiles > 16)
            {
                tiles = tiles - game_get_flags(g, i, j);
            }

            switch (tiles)
            {
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
        if (i_cpt <= 6)
        {
            printf("|\n%d |", i_cpt);
            i_cpt++;
        }
    }
    printf("|\n   ------- \n");
}

game game_default(void)
{
    //new blank game
    int init_value[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    int cpt = 0;
    game default_game = game_new_empty();

    for (int i = 0; i < DEFAULT_SIZE; i++) //fill up game array
    {
        for (int j = 0; j < DEFAULT_SIZE; j++)
        {
            game_set_square(default_game, i, j, init_value[cpt]);
            cpt++;
        }
    }

    return default_game;
}

game game_default_solution(void)
{
    //Base solution tab
    int solution_value[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_LIGHTBULB, S_BLANK, S_BLACK1, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_LIGHTBULB, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_LIGHTBULB,
        S_BLANK, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_LIGHTBULB,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK,
        S_LIGHTBULB, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_LIGHTBULB, S_BLANK,
        S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    int cpt = 0;
    game solution_game = game_new_empty(); //fill up game array

    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        for (int j = 0; j < DEFAULT_SIZE; j++)
        {
            game_set_square(solution_game, i, j, solution_value[cpt]);
            cpt++;
        }
    }
    game_update_flags(solution_game);

    return solution_game;
}
