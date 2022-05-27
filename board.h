/* 
 * Authors: Matthew, Lucy, Ashley, Ryan
 * board.h - header file for board.c
 * 
 * A ‘board’ is an array list of pointers to arraylists of pointers to slot structs.
 *
 * CS50, Spring 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "libcs50/memory.h"

//////////////////////////////////
/********** Global Types ********/
//////////////////////////////////
typedef struct board board_t;

///////////////////////////////
/********** Functions ********/
///////////////////////////////

/***************** board_new *****************/
/* We return:
 *   pointer to a new board, or NULL if error.
 * We guarantee:
 *   The board is initialized with all 0 and false slots.
 * Caller is responsible for:
 *   later calling board_delete.
 */
board_t *board_new();

/***************** board_set *****************/
/* Sets a slot to a new number/given
 * 
 * Caller provides:
 *   valid pointer to board, 
 *   row and column must be between 0 and 8, 
 *   num must be between 0 and 9
 * We do:
 *   set the slot to the given number and boolean
 */
void board_set(board_t *board, int row, int column, int num, bool given);

int board_get(board_t *board, int row, int column);
/***************** valid_input *****************/
/* 
 */
bool valid_input(board_t *board, int num, int row, int column);

/***************** emptyLocation *****************/
bool empty_location(board_t *board, int *row, int *col);

/***************** board_print *****************/
void board_print(board_t *board);

/***************** board_delete *****************/
void board_delete(board_t *board);

/***************** board_iterate *****************/
void board_iterate(board_t *board, void *arg, void (*itemfunc)(void *arg, void *slot));