#ifndef __GAMESTRUCT_H__
#define __GAMESTRUCT_H__

#include "game.h"

typedef struct history_s* history;
typedef struct move_pile_s* move_pile;

struct game_s {
    square** tab;
    uint nb_row;
    uint nb_col;
    bool warpping;
    history move;
};

struct history_s {
    move_pile undo;
    move_pile redo;
};

struct move_pile_s {
    uint j;
    uint i;
    square move;
    move_pile next;
};

#endif