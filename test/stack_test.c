#include "../libstack/stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ********** AUXILIARS ********** */

move create_move(uint i, uint j, square s) {  // oui c'est une redefinition ;)
    move new = (move)malloc(sizeof(struct move_s));
    assert(new);
    new->i = i;
    new->j = j;
    new->s = s;
    return new;
}

bool move_equal(move move1, move move2) { return move1->i == move2->i && move1->j == move2->j && move1->s == move2->s; }

/* ********** TEST STACK NEW EMPTY ********** */

bool test_stack_new_empty(void) {
    move_stack test = stack_new_empty();

    if (test != NULL) {
        return false;
    }

    stack_free(test);

    return true;
}

/* ********** TEST STACK IS EMPTY ********** */

bool test_stack_is_empty(void) {
    move_stack test = stack_new_empty();

    if (!stack_is_empty(test)) {
        return false;
    }
    test = stack_push_head(test, create_move(4, 5, S_LIGHTBULB));
    if (stack_is_empty(test)) {
        return false;
    }

    stack_free(test);

    return true;
}

/* ********** TEST STACK PUSH HEAD ********** */

bool test_stack_push_head(void) {
    move_stack test = stack_new_empty();

    move move1 = create_move(5, 6, S_LIGHTBULB);
    move move2 = create_move(8, 10, S_BLANK);

    test = stack_push_head(test, move1);
    if (!move_equal(move1, stack_peek_head(test))) {
        return false;
    }
    test = stack_push_head(test, move2);
    if (!move_equal(move2, stack_peek_head(test))) {
        return false;
    }

    stack_free(test);

    return true;
}

/* ********** TEST STACK POP HEAD ********** */

bool test_stack_pop_head(void) {
    move_stack test = stack_new_empty();

    move move1 = create_move(5, 6, S_LIGHTBULB);
    move move2 = create_move(8, 10, S_BLANK);

    test = stack_push_head(test, move1);
    test = stack_push_head(test, move2);

    test = stack_pop_head(test);
    if (!move_equal(move1, stack_peek_head(test))) {
        return false;
    }
    test = stack_pop_head(test);
    if (!stack_is_empty(test)) {
        return false;
    }

    stack_free(test);

    return true;
}

/* ********** TEST STACK PEEK HEAD ********** */

bool test_stack_peek_head(void) {
    move_stack test = stack_new_empty();

    move move1 = create_move(5, 6, S_LIGHTBULB);
    move move2 = create_move(8, 10, S_BLANK);

    test = stack_push_head(test, move1);
    test = stack_push_head(test, move2);

    if (!move_equal(move2, stack_peek_head(test))) {
        return false;
    }
    test = stack_pop_head(test);
    if (!move_equal(move1, stack_peek_head(test))) {
        return false;
    }

    stack_free(test);

    return true;
}

/* ********** TEST STACK CLEAR ********** */

bool test_stack_clear(void) {
    move_stack test = stack_new_empty();
    move_stack test2 = stack_new_empty();

    move move1 = create_move(5, 6, S_LIGHTBULB);
    move move2 = create_move(8, 10, S_BLANK);

    test = stack_push_head(test, move1);
    test = stack_push_head(test, move2);

    test = stack_clear(test);
    test2 = stack_clear(test2);

    return stack_is_empty(test) && stack_is_empty(test2);
}

/* ********** TEST STACK FREE ********** */

bool test_stack_free(void) {
    move_stack test = stack_new_empty();
    move_stack test2 = stack_new_empty();

    move move1 = create_move(5, 6, S_LIGHTBULB);
    move move2 = create_move(8, 10, S_BLANK);

    test = stack_push_head(test, move1);
    test = stack_push_head(test, move2);

    stack_free(test);
    stack_free(test2);

    return true;
}

/* ********** USAGE ********** */

void usage(int argc, const char *argv[]) {
    fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
    exit(EXIT_FAILURE);
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        usage(argc, argv);
    }

    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool passed = false;

    if (strcmp("stack_new_empty", argv[1]) == 0) {
        passed = test_stack_new_empty();
    } else if (strcmp("stack_is_empty", argv[1]) == 0) {
        passed = test_stack_is_empty();
    } else if (strcmp("stack_push_head", argv[1]) == 0) {
        passed = test_stack_push_head();
    } else if (strcmp("stack_pop_head", argv[1]) == 0) {
        passed = test_stack_pop_head();
    } else if (strcmp("stack_peek_head", argv[1]) == 0) {
        passed = test_stack_peek_head();
    } else if (strcmp("stack_clear", argv[1]) == 0) {
        passed = test_stack_clear();
    } else if (strcmp("stack_free", argv[1]) == 0) {
        passed = test_stack_free();
    } else {
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
