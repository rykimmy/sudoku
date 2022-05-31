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
 * See board.h for more information
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
 * See board.h for more information
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
 * See board.h for more information
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
 * See board.h for more information
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
 * See board.h for more information
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
 * See board.h for more information
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
 * See board.h for more information
**/
void board_delete(board_t *board)
{
  for (int i = 0; i < 9; i++) {
    free(board->grid[i]);
  }
  free(board->grid);
  free(board);
}

/***************** board_copy *****************/
/**
 * See board.h for more information
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
