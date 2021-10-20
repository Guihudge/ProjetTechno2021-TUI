#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "game.h"
#include "game_aux.h"

void crit_error(char *err)
{
    fprintf(stderr, "[CRITICAL] %s\n", err);
    exit(1);
}

void test_error(cgame g)
{

    for (int j = 0; j < DEFAULT_SIZE; j++) //pass on all array
    {
        for (int i = 0; i < DEFAULT_SIZE; i++)
        {
            if (game_has_error(g, i, j))
            {
                printf("Error at light bulb (%d, %d)\n", i, j);
            }
        }
    }
}

void scan_and_play_move(game g, square s)
{
    int i, j;
    scanf(" %d %d", &i, &j);
    if (i < 0 || i >= DEFAULT_SIZE || j < 0 || j >= DEFAULT_SIZE)
    {
        printf("Invalid position\n");
    }
    else if (game_check_move(g, i, j, s))
    {
        printf("> action: play move in (%d, %d)\n", i, j);
        game_play_move(g, i, j, s);
    }
    else
    {
        printf("Invalid move\n");
    }
}

void print_help()
{
    printf("- press 'h' for print this help\n");
    printf("- press 'q' for quit the game\n");
    printf("- press 'r' for reset the game\n");
    printf("- press 'l <i> <j>' place a lightbuld in case (<i>, <j>)\n");
    printf("- press 'm <i> <j>' place a mark in case (<i>, <j>)\n");
    printf("- press 'b <i> <j>' reset case (<i>, <j>) [remove mark and/or lightbulb]\n\n");
}

int main(void)
{
    bool win = false;
    game actual_game = game_default();

    while (!win)
    {
        game_print(actual_game);
        test_error(actual_game);

        char cmd;
        int ret;

        printf("cmd (use h for help) > ");
        ret = scanf(" %c", &cmd);

        if (ret != 1)
        {
            crit_error("Unable to prase argument");
        }

        if (cmd == 'h')
        {
            printf("> action: print help\n");
            print_help();
        }
        else if (cmd == 'r')
        {
            printf("> action: reset game\n");
            actual_game = game_default();
        }
        else if (cmd == 'q')
        {
            printf("> action: quit\n");
            printf("shame\n");
            return EXIT_SUCCESS;
        }
        else if (cmd == 'l')
        {
            scan_and_play_move(actual_game, S_LIGHTBULB);
        }
        else if (cmd == 'm')
        {
            scan_and_play_move(actual_game, S_MARK);
        }
        else if (cmd == 'b')
        {
            scan_and_play_move(actual_game, S_BLANK);
        }
        else {
            printf("undefined command '%c', use h for help.\n", cmd);
        }

        win = game_is_over(actual_game);
    }
    game_print(actual_game);
    printf("Congratulation !\n");

    return EXIT_SUCCESS;
}