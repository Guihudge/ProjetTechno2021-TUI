/**
 * @file stack.h
 * @author lightup-A41D
 * @brief the header of libstack for stack managment
 */

#ifndef __STACK_H__
#define __STACK_H__

#include "../libgame/game.h"
#include "../libgame/game_struct.h"

/**
 * @brief Create a new stack and return it
 *
 * @return move_stack
 */
move_stack stack_new_empty(void);

/**
 * @brief Check if stack si empty
 *
 * @param stack the stick to test
 * @return true if stack is empty
 * @return false if stack is not empty
 */
bool stack_is_empty(move_stack stack);

/**
 * @brief ad data on the head of stack
 *
 * @param stack the stack to add data
 * @param data a move struct
 * @return move_stack return the stack with new data
 */
move_stack stack_push_head(move_stack stack, move data);

/**
 * @brief remove the header of the stack
 *
 * @param stack the stack to add
 * @return move_stack the return stack
 */
move_stack stack_pop_head(move_stack stack);

/**
 * @brief Get the data of the head of stack
 *
 * @param stack the stack to get value
 * @return move the data on head
 */
move stack_peek_head(move_stack stack);

/**
 * @brief replace an used stack to a new clean stack
 *
 * @param stack the stack to clear
 * @return move_stack an empty stack
 */
move_stack stack_clear(move_stack stack);

/**
 * @brief destriy the stack
 *
 */
void stack_free(move_stack);

#endif
