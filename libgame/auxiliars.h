/**
 * @file auxiliars.h
 * @brief Auxiliars function mainly for error gestion
 * */

#ifndef __AUXILIARS_H__
#define __AUXILIARS_H__

#include <stdbool.h>

#include "game.h"
#include "game_struct.h"

/**
 * @brief Minimum size of the game grid.
 */
#define MINSIZE 1

/**
 * @brief Maximum size of the game grid.
 */
#define MAXSIZE 10

/**
 * @brief Prints an error message and exit the program in connection with memory allocation error.
 * @deprecated Ne pas utiliser dans les test
 **/
void memory_error(char *file, int line);

/**
 * @brief Prints an error message and exit the program in connection with memory pointer error.
 * @param file Name of the file where the function is called use __FILE__ constant.
 * @param line Line number where the function is called use __LINE__ constant.
 * @deprecated Ne pas utiliser dans les test
 **/
void pointer_error(char *file, int line);

/**
 * @brief Prints an error message and exit the program in connection with an unknown error.
 * @param file Name of the file where the function is called use __FILE__ constant.
 * @param line Line number where the function is called use __LINE__ constant.
 * @deprecated Ne pas utiliser dans les test
 **/
void unknown_error(char *file, int line);

/**
 * @brief Check viability of a pointer and exit the program with the error message associated
 * in case where it would be unvalid.
 * @param pointer Tab pointer that must be checked.
 * @param type Inform of the potential error type.
 * @param file Name of the file where the function is called use __FILE__ constant.
 * @param line Line number where the function is called use __LINE__ constant.
 * @pre @p pointer Must be a pointer tab with the potential error type associated.
 * @pre @p type Must be exactly "pointer" or "memory".
 * @deprecated Ne pas utiliser dans les test
 **/
void is_viable_pointer(const void *pointer, const char *type, char *file, int line);

/**
 * @brief Check that coordinates are valid for the game and exit the program in case of error.
 * @param g game pointer.
 * @param i Row index.
 * @param j Column index.
 * @param fonction The string that correspond to the fonction where check_coordinates been called.
 * @pre @p fonction Must correspond to the fonction.
 * @deprecated Ne pas utiliser dans les test
 **/
void check_coordinates(cgame g, uint i, uint j, const char *fonction);

/**
 * @brief Deletes games in a tab of a given size and prints an error message.
 * @param exit Given boolean indicating in the exit of a boolean function should be true of false.
 * @param games Tab filled by games to delete pointers.
 * @param size The size of the games pointer tab.
 * @param error Error message associated.
 * @pre @p games Pointers should be valid and their number and location in the
 * linear tab should correspond to the games that should be deleted, other pointers
 * in the tab located after games[size-1] would be ignored.
 * @pre @p erre Can be set to "" if no error message is needed.
 * @return The given boolean.
 **/
bool delete_and_exit(bool exit, game *games, uint size, char *error);

/**
 * @brief Create a game struct object
 *
 * @param nb_rows number of rows
 * @param nb_cols number of cols
 * @return The new allocated struct
 */
game create_game_struct(uint nb_rows, uint nb_cols);

/**
 * @brief Initialize and allocate memory for the history struct
 *
 * @return The new history struct
 */
history init_game_history();

/**
 * @brief Create a move object
 *
 * @param i row
 * @param j cols
 * @param s tiles
 * @return the created move
 */
move create_move(uint i, uint j, square s);

#endif