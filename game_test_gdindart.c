#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"

/*test_game_update_flags*/
bool test_game_update_flags()
{
    return true;
}

/*test_game_default*/
bool test_game_default()
{
    return true;
}

/*test_game_has_error*/
bool test_game_has_error()
{
    return true;
}

/*test_game_is_marked*/
bool test_game_is_marked()
{
    return true;
}

/*test_game_is_black*/
bool test_game_is_black()
{
    return true;
}

/*test_game_set_square*/
bool test_game_set_square()
{
    return true;
}

/*test_game_equal*/
bool test_game_equal()
{
    return true;
}

/*test_game_new_empty*/
bool test_game_new_empty()
{
    return true;
}

/*Dummy test*/

bool test_dummy()
{
    return true;
}

/*Usage*/
void usage(int argc, char *argv[])
{
    fprintf(stderr, "Usage : %s <test_name>\n", argv[0]);
    exit(EXIT_FAILURE);
}

/*Main*/
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        usage(argc, argv);
    }

    fprintf(stderr, "Starting test '%s'.\n", argv[1]);
    bool passed = false;
    if (strcmp("dummy", argv[1]) == 0)
    {
        passed = test_dummy();
    }
    else if (strcmp("game_update_flags", argv[1]) == 0)
    {
        passed = test_game_update_flags();
    }
    else if (strcmp("game_default", argv[1]) == 0)
    {
        passed = test_game_default();
    }
    else if (strcmp("game_has_error", argv[1]) == 0)
    {
        passed = test_game_has_error();
    }
    else if (strcmp("game_is_marked", argv[1]) == 0)
    {
        passed = test_game_is_marked();
    }
    else if (strcmp("game_is_black", argv[1]) == 0)
    {
        passed = test_game_is_black();
    }
    else if (strcmp("game_set_square", argv[1]) == 0)
    {
        passed = test_game_set_square();
    }
    else if (strcmp("game_equal", argv[1]) == 0)
    {
        passed = test_game_equal();
    }
    else if (strcmp("game_new_empty", argv[1]) == 0)
    {
        passed = test_game_new_empty();
    }
    else
    {
        fprintf(stderr, "Error: unkown test name %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /*Test result*/
    if (passed)
    {
        fprintf(stderr, "Test %s passed\n", argv[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        fprintf(stderr, "Test %s failed\n", argv[1]);
        exit(EXIT_FAILURE);
    }
}