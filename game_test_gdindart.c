#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*Dummy test*/

bool test_dummy(){
    return true;
}

/*Usage*/
void usage(int argc, char *argv[]){
    fprintf(stderr, "Usage : %s <test_name>\n", argv[0]);
    exit(EXIT_FAILURE);
}

/*Main*/
int main(int argc, char *argv[]){
    if (argc == 1){
        usage(argc, argv);
    }

    fprintf(stderr, "Starting test '%s'.\n", argv[1]);
    bool passed = false;
    if (strcmp("dummy", argv[1]) == 0){
        passed = test_dummy();
    }
    else{
        fprintf(stderr, "Error: unkown test name %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /*Test result*/
    if (passed){
        fprintf(stderr, "Test %s passed\n", argv[1]);
        exit(EXIT_SUCCESS);
    }
    else{
        fprintf(stderr, "Test %s failed\n", argv[1]);
        exit(EXIT_FAILURE);
    }

}