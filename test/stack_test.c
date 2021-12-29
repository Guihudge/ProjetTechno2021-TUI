#include "../libstack/stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ********** TEST STACK NEW EMPTY ********** */

bool test_stack_new_empty(void) { return true; }

/* ********** TEST STACK IS EMPTY ********** */

bool test_stack_is_empty(void) { return true; }

/* ********** TEST STACK PUSH HEAD ********** */

bool test_stack_push_head(void) { return true; }

/* ********** TEST STACK POP HEAD ********** */

bool test_stack_pop_head(void) { return true; }

/* ********** TEST STACK PEEK HEAD ********** */

bool test_stack_peek_head(void) { return true; }

/* ********** TEST STACK CLEAR ********** */

bool test_stack_clear(void) { return true; }

/* ********** TEST STACK FREE ********** */

bool test_stack_free(void) { return true; }

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
