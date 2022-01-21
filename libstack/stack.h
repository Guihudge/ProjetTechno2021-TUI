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
 * @return The new created stack
 */
move_stack stack_new_empty(void);

/**
 * @brief Check if stack is empty
 *
 * @param stack The stack to test
 * @return true if stack is empty
 * @return false if stack is not empty
 */
bool stack_is_empty(move_stack stack);

/**
 * @brief Add data on the head of stack
 *
 * @param stack The stack to add data on head
 * @param data The new element to add
 * @pre @p data must be a valid pointer towar a move struct
 * @return The stack with new data on head
 */
move_stack stack_push_head(move_stack stack, move data);

/**
 * @brief Remove the header of the stack
 *
 * @param stack the stack to remove header
 * @pre @p stack must be a valid pointer towar a move_stack struct
 * @return The new header
 */
move_stack stack_pop_head(move_stack stack);

/**
 * @brief Get the data of the head of stack
 *
 * @param stack the stack to get value
 * @pre @p stack must be a valid pointer towar a move_stack struct
 * @return The data on head
 */
move stack_peek_head(move_stack stack);

/**
 * @brief replace an used stack to a new clean stack
 *
 * @param stack the stack to clear
 * @return An empty stack
 */
move_stack stack_clear(move_stack stack);

/**
 * @brief destroy the stack
 */
void stack_free(move_stack);

#endif
