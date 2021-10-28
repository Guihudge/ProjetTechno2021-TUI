#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* ********** TEST DUMMY ********** */

bool test_dummy(void) { return true; }

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