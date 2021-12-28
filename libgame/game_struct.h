#ifndef __GAMESTRUCT_H__
#define __GAMESTRUCT_H__

#include "game.h"
#include "../libpilefile/pile.h"

typedef struct history_s* history;
typedef struct move_s* move;

struct game_s {
    square** tab;
    uint nb_row;
    uint nb_col;
    bool warpping;
    history move;
};

struct history_s {
    pile_obj undo;
    pile_obj redo;
};

struct move_s {
    uint j;
    uint i;
    square s;
};

#endif