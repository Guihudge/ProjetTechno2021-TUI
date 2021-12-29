#ifndef __GAMESTRUCT_H__
#define __GAMESTRUCT_H__

#include "game.h"

/**
 * @brief rename history structure for works with pointer
 *
 */
typedef struct history_s* history;

/**
 * @brief rename move_stack for simple read
 *
 */
typedef struct move_stack_s* move_stack;

/**
 * @brief remane struct move_s
 *
 */
typedef struct move_s* move;

/**
 * @brief main gamestruct
 *
 */
struct game_s {
    square** tab;  /**< 2D tab for store game flags and tiles*/
    uint nb_row;   /**< number of rows*/
    uint nb_col;   /**< number of cols*/
    bool warpping; /**< warpping or not warping, this is the question*/
    history move;  /**< a link to hitory struct*/
};

/**
 * @brief The history struct for undo and redo capabilities
 *
 */
struct history_s {
    move_stack undo; /**< the undo stack*/
    move_stack redo; /**< the redo stack*/
};

/**
 * @brief move_stack is a structure like a simpel chained list
 *
 */
struct move_stack_s {
    move data;       /**< data link to move struct*/
    move_stack next; /**< the next cell*/
};

/**
 * @brief move_s a strucure for store a playing move
 *
 */
struct move_s {
    uint i;   /**< row*/
    uint j;   /**< col*/
    square s; /**< played move*/
};

#endif