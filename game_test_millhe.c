#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool test_dummy(){
  return true;
}

void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

int main (int argc, char *argv[]){
    if (argc == 1){
        usage(argc, argv);
    }
    bool ok = false;
    if(strcmp("dummy", argv[1]) == 0){
        ok = test_dummy();
    }
    else{
      exit(EXIT_FAILURE);
    }


    return EXIT_SUCCESS;
}
