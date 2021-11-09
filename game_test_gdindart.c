#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "game_aux.h"


/*Util fonction*/
void print_bool(bool ok, char *text)
{
    fprintf(stderr, "%s", text);
    if (ok)
    {
        fprintf(stderr, "true\n");
    }
    else
    {
        fprintf(stderr, "false\n");
    }
}

/*test_game_update_flags*/
bool test_game_update_flags()
{
    bool ok = true;

    //test game creation
    game test_game = game_default();
    game_set_square(test_game, 0, 6, S_LIGHTBULB);

    //update flags
    game_update_flags(test_game);

    //test if update is correct
    if (!game_is_lighted(test_game, 0, 3))
    {
        ok = false;
    }
    if (!game_is_lighted(test_game, 0, 4))
    {
        ok = false;
    }
    if (!game_is_lighted(test_game, 0, 5))
    {
        ok = false;
    }
    if (game_is_lighted(test_game, 1, 5))
    {
        ok = false;
    }
    if (!game_is_lighted(test_game, 1, 6))
    {
        ok = false;
    }
    if (!game_is_lightbulb(test_game, 0, 6))
    {
        ok = false;
    }
    game_delete(test_game);
    return ok;
}

/*test_game_default*/
bool test_game_default()
{
    //create test game
    square init_value_test[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    game test_game = game_new(init_value_test);

    game default_game = game_default();
    
    bool ok = game_equal(test_game, default_game);
    game_delete(test_game);
    game_delete(default_game);
    return ok;
}

/*test_game_has_error*/
bool test_game_has_error()
{
    bool ok = true;

    square init_test_value[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_LIGHTBULB, S_BLANK, S_BLACK1, S_LIGHTBULB, S_BLANK, S_BLANK, S_LIGHTBULB,
        S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    game test_game = game_new(init_test_value);
    game_update_flags(test_game);

    ok = game_has_error(test_game, 0, 6);
    //print_bool(ok, "test1: ");
    ok = game_has_error(test_game, 0, 3) && ok;
    //print_bool(ok, "test2: ");
    ok = !game_has_error(test_game, 0, 0) && ok;
    //print_bool(ok, "test3: ");
    game_delete(test_game);
    return ok;
}

/*test_game_is_marked*/
bool test_game_is_marked()
{
    square init_test_value[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_MARK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_MARK, S_BLANK, S_BLANK,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    game test_game = game_new(init_test_value);
    game_update_flags(test_game);
    bool ok = game_is_marked(test_game, 0, 4) && game_is_marked(test_game, 3, 4) && !game_is_marked(test_game, 0, 6);
    
    game_delete(test_game);
    return ok;
}

/*test_game_is_black*/
bool test_game_is_black()
{
    square init_test_value[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    game test_game = game_new(init_test_value);
    game_update_flags(test_game);

    char mask = 247; //11110111
    char check = 255;
    bool ok = true;

    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        for (int y = 0; y < DEFAULT_SIZE; y++)
        {
            char tiles = game_get_square(test_game, i, y);
            ok = ok && (((tiles | mask) == check) == game_is_black(test_game, i, y));
        }
    }
    game_delete(test_game);
    return ok;
}

/*test_game_set_square*/
bool test_game_set_square()
{
    game test_game = game_new_empty();

    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        for (int y = 0; y < DEFAULT_SIZE; y++)
        {
            char val = rand() % 256;
            game_set_square(test_game, i, y, val);

            if (game_get_square(test_game, i, y) != val){
                return false;
            }
        }
    }
    game_delete(test_game);
    return true;

}

/*test_game_equal*/
bool test_game_equal()
{
    square base_game_val[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    game base_game = game_new(base_game_val);
    game_update_flags(base_game);

    square equal_game_val[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    game equal_game = game_new(equal_game_val);
    game_update_flags(equal_game);

    square diff_game_val[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_MARK,
        S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLACK1, S_BLACKU, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

    game diff_game = game_new(diff_game_val);
    game_update_flags(diff_game);

    bool ok = game_equal(base_game, equal_game) && !game_equal(base_game, diff_game);

    game_delete(base_game);
    game_delete(equal_game);
    game_delete(diff_game);
    return ok;
}

/*test_game_new_empty*/
bool test_game_new_empty()
{
    game blank_game = game_new_empty();

    for (int i = 0; i < DEFAULT_SIZE; i++)
    {
        for (int y = 0; y < DEFAULT_SIZE; y++)
        {
            if (game_get_square(blank_game, i, y) != S_BLANK)
            {
                return false;
            }
        }
    }
    game_delete(blank_game);
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

    srand(time(NULL));

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