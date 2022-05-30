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


/////////////////////////////////
/********** Local Types ********/
/////////////////////////////////
typedef struct slot {
  int num;            // integer key provided by caller                 
  bool given;         // boolean signifying a given number
} slot_t;


//////////////////////////////////
/********** Global Types ********/
//////////////////////////////////
typedef struct board {
  slot_t ***grid;       
} board_t;

/**************** local functions ****************/
/* not visible outside this file */
static slot_t *slot_new(int num, bool given);

//////////////////////////
/********** APIs ********/
//////////////////////////

/***************** slot_new *****************/
/**
 * Builds a new slot.
 *
 * Takes:
 *     int num – the number that the slot will hold
 *     bool given – true, if the slot is part of the puzzle; false, if the slot is one that the solver must fill in
 * Returns:
 *     slot_t* – pointer the new slot
**/
static slot_t *slot_new(int num, bool given) 
{
  // Initializing slot
  slot_t *slot = malloc(sizeof(slot_t));
  
  // Assigning its vlaues
  slot->num = num;
  slot->given = given;
  
  return slot;
}


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
  slot_t ***row = calloc(9, sizeof(slot_t));
  
  // Setting up the grid
  for (int i = 0; i < 9; i++) {
    slot_t **column = calloc(9, sizeof(slot_t));
    row[i] = column;
  }
  
  board->grid = row;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      slot_t *slot = slot_new(0, false);
      board->grid[i][j] = slot;
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
void board_set(board_t *board, int row, int column, int num, bool given) 
{
  if (board != NULL){ // validate that the board_set works
    //validate that the row and column are within boundaries
    
      board->grid[row][column]->num = num;
      board->grid[row][column]->given = given;
    
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
  
  return board->grid[row][column]->num;
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
      if (board->grid[row][i]->num == num) {
        return false;
      }
    }
  }
  
  // check if same number is in column
  for (int j = 0; j < 9; j++) {
    if (j != row) {
      if (board->grid[j][column]->num == num) {
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
      if (board->grid[a + row - row_mod][b + column - col_mod]->num == num) {
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
      
      // checking for an empty slot
      if (board->grid[*row][*col]->num == 0) {
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
        int num = board->grid[i][j]->num;
        if (num == 0){
            printf("0 ");
        } else{
            printf("%d ", num);
        }
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
    // Iterate through each slot and free each slot
    for (int i=0; i < 9; i++){
        for (int j=0; j < 0; j++){
            free(board->grid[i][j]);
        }
    }

    free(board);
}

/***************** board_iterate *****************/
/**
 * Iterates through each slot in the board and applies a given function to each slot.
 *
 * Takes:
 *     board_t* board – the sudoku board
 *     void* arg – an argument to be passed into the helper function
 *     void (*itemfunc)(void *arg, void *slot) – the function to be applied to each slot
 * Returns:
 *     nothing
**/
void board_iterate(board_t *board, void *arg, void (*itemfunc)(void *arg, void *slot))
{
  if (board != NULL && itemfunc != NULL) {
    for (int i=0; i < 9; i++){
      for (int j=0; j < 9; j++){
        (*itemfunc)(arg, board->grid[i][j]);
      }
    }
  }
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
      copy->grid[i][j]->num = original->grid[i][j]->num;
    }
  }
  
  return copy;
}
