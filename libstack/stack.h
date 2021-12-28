#ifndef __STACK_H__
#define __STACK_H__

#include "../libgame/game.h"
#include "../libgame/game_struct.h"

move_stack stack_new_empty(void);

bool stack_is_empty(move_stack stack);

move_stack stack_push_head(move_stack stack, move data);

move_stack stack_pop_head(move_stack stack);

move stack_peek_head(move_stack stack);

move_stack stack_clear(move_stack stack);

void stack_free(move_stack);

#endif
