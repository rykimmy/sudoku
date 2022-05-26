/* 
 * Authors: Matthew, Lucy, Ashley, Ryan
 * board.h - header file for board.c
 * 
 * A ‘board’ is an array list of pointers to arraylists of pointers to slot structs.
 *
 * CS50, Spring 2022
 */

#include <stdio.h>

//////////////////////////////////
/********** Global Types ********/
//////////////////////////////////
typedef struct board board_t;

///////////////////////////////
/********** Functions ********/
///////////////////////////////

/***************** board_set *****************/
void board_set(board_t *board, int row, int column, int num, bool given);

/***************** board_new *****************/
board_t *board_new();

/***************** valid_input *****************/
bool valid_input(board_t *board, int num, int row, int column);

/***************** emptyLocation *****************/
bool emptyLocation(board_t *board);

/***************** board_print *****************/
void board_print(board_t *board);

/***************** board_delete *****************/
void board_delete(board_t *board);

/***************** board_iterate *****************/
void board_iterate(board_t *board, void *arg, void (*itemfunc)(void *arg, slot_t *slot));