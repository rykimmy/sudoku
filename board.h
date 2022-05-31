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
/**
 * Builds a new board and calls slot_new on each slot. The caller is responsible for freeing memory.
 * 
 * Takes:
 *     no parameters
 * Returns:
 *     board_t* – a pointer to the newly created board.
**/
board_t *board_new();

/***************** board_set *****************/
/**
 * Sets the number of a given slot in the board.
 *
 * Takes:
 *     board_t* board – the board in which a slot will be set
 *     int row – the row of the slot to be changed
 *     int column – the column of the slot to be changed
 *     bool given – whether or not the slot will be part of the puzzle a slot to be filled
 * Returns:
 *     nothing
**/
void board_set(board_t *board, int row, int column, int num);

/***************** board_get *****************/
/**
 * Gets the number of a slot in the board.
 * 
 * Takes:
 *     board_t* board – a pointer to the sudoku puzzle
 *     int row – the row of the slot to get
 *     int column – the column of the slot to get
 * Returns:
 *     int – the number of the specified slot
**/
int board_get(board_t *board, int row, int column);

/***************** valid_input *****************/
/**
 * Validates the board by checking a given slot with its row, column, and box.
 * 
 * Takes:
 *     board_t* board – the sudoku board
 *     int row – the row of the slot that's being validated
 *     int column – the column of the slot that's being validated
 *     int num – the number that will be checked
 * Returns:
 *     true, if the number fits into the slot
 *     false, if the number cannot be added to the specified slot
**/
bool valid_input(board_t *board, int row, int column, int num);

/***************** empty_location *****************/
/**
 * Iterates through the slots of the board, beginning at the top left and moving to the right. Upon finding an empty slot––one that has not been set and is not given––sets the row and col values to the slot.
 *
 * Takes:
 *     board_t* board – the sudoku board
 *     int* row – pointer to the row of the slot being checked
 *     int* col – pointer to the column of the slot being checked
 * Returns:
 *     true, if the function finds an empty slot
 *     false, if the function does not find an empty slot (meaning all slots are filled and the puzzle is solved)
**/
bool empty_location(board_t *board, int *row, int *col);

/***************** board_print *****************/
/**
 * Prints the board, uses '0' for an empty slot.
 *
 * Takes:
 *     board_t* board – the sudoku board
 * Returns:
 *     nothing
**/
void board_print(board_t *board);

/***************** board_delete *****************/
/**
 * Deletes each slot, then deletes the board
 *
 * Takes:
 *     board_t* board - the sudoku board
 * Returns:
 *     nothing
**/
void board_delete(board_t *board);

/***************** board_copy *****************/
/**
 * Creates a copy of the sudoku board, copying each slot to the copied board.
 *
 * Takes:
 *     board_t* original – the original sudoku board
 *
 * Returns:
 *     board_t* – the copied board
**/
board_t *board_copy(board_t *original);