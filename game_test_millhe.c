#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game.h"

bool test_dummy(){
  return true;
}

bool test_game_is_over(){
  square test[DEFAULT_SIZE * DEFAULT_SIZE] = {
    S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
    S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
    S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
    S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
    S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
    S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
    S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

  game g2 = game_new(test); 

  square solution_test[DEFAULT_SIZE * DEFAULT_SIZE] = {
    S_LIGHTBULB, S_BLANK, S_BLACK1, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLANK,
    S_BLANK, S_LIGHTBULB, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_LIGHTBULB,
    S_BLANK, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
    S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_LIGHTBULB,
    S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK,
    S_LIGHTBULB, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_LIGHTBULB, S_BLANK,
    S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK
    };
  game sol_test = game_new(solution_test);
  game_update_flags(sol_test);
  for (int i = 0; i < DEFAULT_SIZE; i++)
  {
    for (int j = 0; j < DEFAULT_SIZE; j++)
    {
      if (game_is_lighbulb(sol_test, i, j))
      {
        game_play_move(g2, i, j, S_LIGHTBULB);
        if (g2 != sol_test){
          if (game_is_over(g2)){
            return false;
          }
        }
        else if (g2 == sol_test){
          return game_is_over(g2);
         }
      }
    }
  }   
} 

bool test_game_is_blanck(){

  square test[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};
  
  game g2 = game_new (test);
  for (int i = 0; i < DEFAULT_SIZE; i++)
  {
    for (int j = 0; j < DEFAULT_SIZE; j++)
    {
      char carre = game_get_square(test, i, j);
      if (! (carre==0) == game_is_blank(test, i, j)){
        return false;
      }
    }
  }
  return true;
  
}
bool test_game_delete(){
    square test[DEFAULT_SIZE * DEFAULT_SIZE] = {
      S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
      S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
      S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
      S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
      S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
      S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
      S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};
    game g2 = game_new(test);
    game_delete(g2);
    if (g2!=NULL)
    {
      return false;
    }
    return true;
}

bool test_game_copy(){
  square test[DEFAULT_SIZE * DEFAULT_SIZE] = {
      S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
      S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
      S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
      S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
      S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
      S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
      S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};
  
  game g2 = game_new(test);
  game g3 = game_copy(g2);
  return game_equal(g3, test);
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
    if (ok)
    {
      exit(EXIT_SUCCESS);
    }
    else {
      exit(EXIT_FAILURE);
    }
    


    return EXIT_SUCCESS;
}
