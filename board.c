/* 
 * board.c - sudoku board module
 *
 * see board.h for more information.
 *
 * Group 9, CS50 Spring 2022
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
 * builds slot
**/
static slot_t *slot_new(int num, bool given) 
{
  slot_t *slot = malloc(sizeof(slot_t));
  slot->num = num;
  slot->given = given;
  return slot;
}


/***************** board_new *****************/
/**
 * builds board and calls slot_new on each slot
**/
board_t *board_new() 
{
  board_t *board = malloc(sizeof(board_t));
  slot_t ***row = calloc(9, sizeof(slot_t*));
  
  for (int i = 0; i < 9; i++) {
    slot_t **column = calloc(9, sizeof(slot_t*));
    row[i] = column;
  }
  
 
  board->grid = row;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      slot_t *slot = slot_new(0, false);
      board->grid[i][j] = slot;
    }
  }
  
  // test, inputs 2 and 5 into board
  // board->grid[0][0]->num = 2;
  // board->grid[1][1]->num = 5;

  return board;
}

/***************** board_set *****************/
/**
 * sets number in slot in board
**/
void board_set(board_t *board, int row, int column, int num, bool given) 
{
  if (board != NULL){ // validate that the board_set works
    //validate that the row and column are within boundaries
    if (row > -1 && row < 9 && column > -1 && column < 9 && num > 0 && num < 10) {
      board->grid[row][column]->num = num;
      board->grid[row][column]->given = given;
    }
  }
}


/***************** board_get *****************/
/**
 * gets number in slot in board
**/
int board_get(board_t *board, int row, int column) 
{
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
 * validates the board
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
  for (int j = 0; j < 9; j++) {
    // check if same number is in column
    if (j != row) {
      if (board->grid[j][column]->num == num) {
        return false;
      }
    }
  }
  
  // check if same number is in box
  int row_mod = row % 3;
  int col_mod = column % 3;
  if (row_mod == 0) {
    if (col_mod == 0) {
      if (board->grid[row + 1][column + 1]->num == num) {
        return false;
      }
      if (board->grid[row + 1][column + 2]->num == num) {
        return false;
      }
      if (board->grid[row + 2][column + 1]->num == num) {
        return false;
      }
      if (board->grid[row + 2][column + 2]->num == num) {
        return false;
      }
    }
    if (col_mod == 1) {
      if (board->grid[row + 1][column - 1]->num == num) {
        return false;
      }
      if (board->grid[row + 1][column + 1]->num == num) {
        return false;
      }
      if (board->grid[row + 2][column - 1]->num == num) {
        return false;
      }
      if (board->grid[row + 2][column + 1]->num == num) {
        return false;
      }
    }
    if (col_mod == 2) {
      if (board->grid[row + 1][column - 1]->num == num) {
        return false;
      }
      if (board->grid[row + 1][column - 2]->num == num) {
        return false;
      }
      if (board->grid[row + 2][column - 1]->num == num) {
        return false;
      }
      if (board->grid[row + 2][column - 2]->num == num) {
        return false;
      }
    }
  }
  if (row_mod == 1) {
    if (col_mod == 0) {
      if (board->grid[row - 1][column + 1]->num == num) {
        return false;
      }
      if (board->grid[row - 1][column + 2]->num == num) {
        return false;
      }
      if (board->grid[row + 1][column + 1]->num == num) {
        return false;
      }
      if (board->grid[row + 1][column + 2]->num == num) {
        return false;
      }
    }
    if (col_mod == 1) {
      if (board->grid[row - 1][column - 1]->num == num) {
        return false;
      }
      if (board->grid[row - 1][column + 1]->num == num) {
        return false;
      }
      if (board->grid[row + 1][column - 1]->num == num) {
        return false;
      }
      if (board->grid[row + 1][column + 1]->num == num) {
        return false;
      }
    }
    if (col_mod == 2) {
      if (board->grid[row - 1][column - 1]->num == num) {
        return false;
      }
      if (board->grid[row - 1][column - 2]->num == num) {
        return false;
      }
      if (board->grid[row + 1][column - 1]->num == num) {
        return false;
      }
      if (board->grid[row + 1][column - 2]->num == num) {
        return false;
      }
    }
  }
  if (row_mod == 2) {
    if (col_mod == 0) {
      if (board->grid[row - 1][column + 1]->num == num) {
        return false;
      }
      if (board->grid[row - 1][column + 2]->num == num) {
        return false;
      }
      if (board->grid[row - 2][column + 1]->num == num) {
        return false;
      }
      if (board->grid[row - 2][column + 2]->num == num) {
        return false;
      }
    }
    if (col_mod == 1) {
      if (board->grid[row - 1][column - 1]->num == num) {
        return false;
      }
      if (board->grid[row - 1][column + 1]->num == num) {
        return false;
      }
      if (board->grid[row - 2][column - 1]->num == num) {
        return false;
      }
      if (board->grid[row - 2][column + 1]->num == num) {
        return false;
      }
    }
    if (col_mod == 2) {
      if (board->grid[row - 1][column - 1]->num == num) {
        return false;
      }
      if (board->grid[row - 1][column - 2]->num == num) {
        return false;
      }
      if (board->grid[row - 2][column - 1]->num == num) {
        return false;
      }
      if (board->grid[row - 2][column - 2]->num == num) {
        return false;
      }
    }
  }
  return true;
}


/***************** emptyLocation *****************/
/**
 * loops through board and returns true if there is an empty slot, also keeps the row and column
**/
// bool empty_location(board_t *board) {
//   for (int i = 0; i < 9; i++) {
//     for (int j = 0; j < 9; j++) {
//       if (board->grid[i][j]->num == 0) {
//         return true;
//       }
//     }
//   }
//   return false;
// }
bool empty_location(board_t *board, int *row, int *col) {
  for (*row = 0; *row < 9; *row) {
    for (*col = 0; *col < 9; *col) {
      if (board->grid[*row][*col]->num == 0) {
        return true;
      }
    }
  }
  return false;
}

/***************** board_print *****************/
/**
 * prints the board, uses '*' for an empty slot
**/
void board_print(board_t *board)
{
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
**/
void board_delete(board_t *board)
{
    for (int i=0; i < 9; i++){
        for (int j=0; j < 0; j++){
            free(board->grid[i][j]);
        }
    }
    free(board);
}

/***************** board_iterate *****************/
/**
 * iterates through each slot in the board
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



// Test
int main () {
  board_t *board = board_new();
  board->grid[0][0]->num = 6;
  if (valid_input(board, 6, 0, 1)) {
    printf("valid input\n");
  }
  else {
    printf("invalid input\n");
  }
  board_set(board, 5, 6, 5, false);
  board_set(board, 5, 1, 5, false);
  board_print(board);
  if (valid_input(board, 5, 5, 1)) {
    printf("valid input\n");
  }
  else {
    printf("invalid input\n");
  }
  board_delete(board);
}