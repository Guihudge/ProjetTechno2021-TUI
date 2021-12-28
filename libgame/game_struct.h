#ifndef __GAMESTRUCT_H__
#define __GAMESTRUCT_H__

#include "game.h"

/**
 * @brief
 *
 */
typedef struct history_s* history;

/**
 * @brief
 *
 */
typedef struct move_stack_s* move_stack;

/**
 * @brief
 *
 */
typedef struct move_s* move;

/**
 * @brief
 *
 */
struct game_s {
    square** tab;  /**< */
    uint nb_row;   /**< */
    uint nb_col;   /**< */
    bool warpping; /**< */
    history move;  /**< */
};

/**
 * @brief
 *
 */
struct history_s {
    move_stack undo; /**< */
    move_stack redo; /**< */
};

/**
 * @brief
 *
 */
struct move_stack_s {
    move data;       /**< */
    move_stack next; /**< */
};

/**
 * @brief
 *
 */
struct move_s {
    uint i;   /**< */
    uint j;   /**< */
    square s; /**< */
};

#endif