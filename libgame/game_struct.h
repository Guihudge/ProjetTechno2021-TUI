#ifndef __GAMESTRUCT_H__
#define __GAMESTRUCT_H__

#include "game.h"

typedef struct history_s* history;
typedef struct move_stack_s* move_stack;
typedef struct move_s* move;

struct game_s {
    square** tab;
    uint nb_row;
    uint nb_col;
    bool warpping;
    history move;
};

struct history_s {
    move_stack undo;
    move_stack redo;
};

struct move_stack_s {
    move data;
    move_stack next;
};

struct move_s {
    uint i;
    uint j;
    square s;
};

#endif