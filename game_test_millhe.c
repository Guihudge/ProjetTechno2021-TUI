#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game.h"

bool test_dummy(){
  return true;
}

bool test_game_get_black_number(){
  square test[DEFAULT_SIZE * DEFAULT_SIZE] = {
    S_LIGHTBULB, S_BLANK, S_BLACK1, S_MARK, S_BLANK, S_BLANK, S_BLANK,
    S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
    S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
    S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
    S_BLACK1, S_BLACK0, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
    S_BLANK, S_BLANK, S_BLACK4, S_BLANK, S_BLACK3, S_BLANK, S_BLANK,
    S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

  game g2 = game_new(test);
  game_update_flags(g2);
  int t1 = game_get_black_number(g2, 0, 2);
  int t2 = game_get_black_number(g2, 1, 2);
  int t3 = game_get_black_number(g2, 5, 4);
  int t4 = game_get_black_number(g2, 5, 2);
  int t = game_get_black_number(g2, 4, 1);
  int t5 = game_get_black_number(g2, 6, 4);
  if (t != 0 || t1 != 1 || t2 != 2 || t3 != 3 || t4 != 4 || t5 != -1){
    return false;
  }
  return true;
}
 
bool test_game_get_square(){
  square test[DEFAULT_SIZE * DEFAULT_SIZE] = {
    S_LIGHTBULB, S_BLANK, S_BLACK1, S_MARK, S_BLANK, S_BLANK, S_BLANK,
    S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
    S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
    S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
    S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
    S_BLANK, S_BLANK, S_BLACK4, S_BLANK, S_BLACK3, S_BLANK, S_BLANK,
    S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

  game g2 = game_new(test);
  game_update_flags(g2);
  if (game_get_square(g2, 0, 0) != S_LIGHTBULB){
    return false;
  }
  if (game_get_square(g2, 0, 1) != S_BLANK){
    return false;
  }
  if (game_get_square(g2, 0, 2) != S_BLACK1){
    return false;
  }
  if (game_get_square(g2, 0, 3) != S_MARK){
    return false;
  }
  if (game_get_square(g2, 1, 2) != S_BLACK2){
    return false;
  }
  if (game_get_square(g2, 4, 1) != S_BLACKU){
    return false;
  }
  if (game_get_square(g2, 5, 4) != S_BLACK3){
    return false;
  }
  if (game_get_square(g2, 5, 2) != S_BLACK4){
    return false;
  }
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
  if(game_is_over(g2)){
    return false;
  }
  if (!game_is_over(sol_test)){
    return false;
  }
  for (int i = 0; i < DEFAULT_SIZE; i++)
  {
    for (int j = 0; j < DEFAULT_SIZE; j++)
    {
      if (game_is_lighbulb(sol_test, i, j))
      {
        game_play_move(g2, i, j, S_LIGHTBULB);
        if (!game_equal(g2, sol_test)){
          if (game_is_over(g2)){
            return false;
          }
        }
        else if (game_equal(g2, sol_test)){
          return game_is_over(g2);
         }
      }
    }
  }   
} 

bool test_game_is_blanck(){

  square test[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_LIGHTBULB, S_BLANK, S_BLACK1, S_MARK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLACK4, S_BLANK, S_BLACK3, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};
  
  game g2 = game_new (test);
  game_update_flags(g2);
  
  return !game_is_blank(g2, 0, 0) && game_is_blank(g2, 0, 1) && !game_is_blank(g2, 0, 2) && !game_is_blank(g2, 0, 3) && !game_is_blank(g2, 1, 2) && !game_is_blank(g2, 4, 1) && !game_is_blank(g2, 5, 2) && !game_is_blank(g2, 5, 4);
  
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
    return (g2==NULL);
}

bool test_game_copy(){
  square test[DEFAULT_SIZE * DEFAULT_SIZE] = {
      S_LIGHTBULB, S_LIGHTBULB, S_BLACK1, S_MARK, S_BLANK, S_BLANK, S_BLANK,
      S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
      S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK0, S_BLACK2,
      S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
      S_BLACK3, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
      S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK4, S_BLANK, S_BLANK,
      S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};
  
  game g2 = game_new(test);
  game g3 = game_copy(g2);
  if (!game_equal(g3, test)){
    return false;
  }
  game_update_flags(g2);
  g3 = game_copy(g2);
  return game_equal(g2, g3);
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
