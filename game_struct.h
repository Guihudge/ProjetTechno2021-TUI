#ifndef __GAMESTRUCT_H__
#define __GAMESTRUCT_H__

#include "game.h"

struct game_s {
    square **tab;
    uint nb_row;
    uint nb_col;
};

#endif