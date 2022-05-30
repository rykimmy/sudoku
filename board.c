/* 
 * board.c - sudoku board module
 *
 * see board.h for more information.
 *
 * CS50 Spring 2022
 * DataNiners: Ashley Liang, Matthew Kim, Lucy Korte, Ryan Kim
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "board.h"
#include "libcs50/memory.h"


//////////////////////////////////
/********** Global Types ********/
//////////////////////////////////
typedef struct board {
  int **grid;       
} board_t;


//////////////////////////
/********** APIs ********/
//////////////////////////

/***************** board_new *****************/
/**
 * Builds a new board and calls slot_new on each slot. The caller is responsible for freeing memory.
 * 
 * Takes:
 *     nothing
 * Returns:
 *     board_t* – a pointer to the newly created board.
**/
board_t *board_new() 
{
  // Initializing the board and set of slots
  board_t *board = malloc(sizeof(board_t));
  int **row = calloc(9, sizeof(int *));
  
  // Setting up the grid
  for (int i = 0; i < 9; i++) {
    int *column = calloc(9, sizeof(int));
    row[i] = column;
  }
  
  // Set each square to 0
  board->grid = row;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      board->grid[i][j] = 0;
    }
  }
  
  return board;
}

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
void board_set(board_t *board, int row, int column, int num) 
{
  if (board != NULL) { // validate that the board_set works
    //validate that the row and column are within boundaries
      board->grid[row][column] = num;
  }
}


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
int board_get(board_t *board, int row, int column) 
{
  // Error checking
  if (board == NULL) {
    return -1;
  }
  if (row < 0 || row > 8 || column < 0 || column > 8) {
    return -1;
  }
  return board->grid[row][column];
}

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
bool valid_input(board_t *board, int row, int column, int num) {
  // check if same number is in row
  for (int i = 0; i < 9; i++) {
    if (i != column) {
      if (board->grid[row][i] == num) {
        return false;
      }
    }
  }
  
  // check if same number is in column
  for (int j = 0; j < 9; j++) {
    if (j != row) {
      if (board->grid[j][column] == num) {
        return false;
      }
    }
  }
  
  // check if same number is in box
  int row_mod = row % 3;
  int col_mod = column % 3;
  for (int a = 0; a < 3; a++) {
    for (int b = 0; b < 3; b++) {
      if ((a + row - row_mod == row) && (b + column - col_mod == column)) {
        continue;
      }
      if (board->grid[a + row - row_mod][b + column - col_mod] == num) {
        return false;
      }
    }
  }
  return true;
}

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
bool empty_location(board_t *board, int *row, int *col) {
  // Iterating through every slot
  for (*row = 0; *row < 9; (*row)++) {
    for (*col = 0; *col < 9; (*col)++) {
      if (board->grid[*row][*col] == 0) {
        return true;
      }
      
    }
  }
  return false;
}

/***************** board_print *****************/
/**
 * Prints the board, uses '*' for an empty slot.
 *
 * Takes:
 *     board_t* board – the sudoku board
 * Returns:
 *     nothing
**/
void board_print(board_t *board)
{
  // Iterating through every slot and printing each
  for (int i=0; i < 9; i++){
    for (int j=0; j < 9; j++){
        int num = board->grid[i][j]; 
        printf("%d ", num);
    }
    printf("\n");
  }
}

/***************** board_delete *****************/
/**
 * Deletes each slot, then deletes the board
 *
 * Takes:
 *     board_t* board - the sudoku board
 * Returns:
 *     nothing
**/
void board_delete(board_t *board)
{
    free(board);
}

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
board_t *board_copy(board_t *original) 
{
  // Create the copy board
  board_t *copy = board_new();
  
  // Copy each slot to the new board
  for (int i=0; i < 9; i++){
    for (int j=0; j < 9; j++){
      copy->grid[i][j] = original->grid[i][j];
    }
  }
  
  return copy;
}
