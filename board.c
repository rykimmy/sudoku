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

//////////////////////////
/********** APIs ********/
//////////////////////////

/***************** slot_new *****************/
static slot_t *slot_new(int num, bool given) {
  slot_t *slot = malloc(sizeof(slot_t));
  slot->num = num;
  slot->given = given;
  return slot;
}

/***************** board_new *****************/
board_t *board_new() 
{
  board_t *board = malloc(sizeof(board_t));
  slot_t ***row = calloc(sizeof(slot_t), 9);
  for (int i = 0; i < 9; i++) {
    slot_t **column = calloc(sizeof(slot_t), 9);
    row[i] = column;
  }
  
  board->grid = row;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      slot_t *slot = slot_new(0, false);
      board->grid[i][j] = slot;
    }
  }
  board->grid[0][0]->num = 2;
  board->grid[1][1]->num = 5;

  return board;
}

/***************** valid_input *****************/
bool valid_input(board_t *board, int num, int row, int column) {
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

/***************** board_set *****************/
void board_set(board_t *brd, int num, int row, int col)
{
    // assertp(brd,"[board.c, board_set] ");
    brd->grid[row][col]->num = num;
}

/***************** slot_get *****************/
slot_t *slot_get(board_t *brd, int row, int col)
{
    slot_t *slot;
    slot = brd->grid[row][col];
    if (slot == NULL) {
        fprintf(stderr, "[board.c, board_set] Slot does not exist. \n");
        return NULL;
    } else {
        printf("%d \n", slot->num);
        return slot;
    }
}

/***************** board_print *****************/
void board_print(board_t *brd)
{
    for (int i=0; i < 9; i++){
        for (int j=0; j < 0; j++){
            int num;
            num = (brd->grid[i][j]->num);
            if (num == 0){
                fprintf(stderr,"[board.c, board_print] Error, slot has not been assigned a number \n");
                exit(1);
            } else{
                printf("%d ", num);
            }
        }
        printf("\n");
    }
}

/***************** board_delete *****************/
void board_delete(board_t *brd)
{
    for (int i=0; i < 9; i++){
        for (int j=0; j < 0; j++){
            count_free(brd->grid[i][j]);
        }
    }
    count_free(brd);
}

/***************** board_iterate *****************/
void board_iterate(board_t *brd, void *arg, void (*itemfunc)(void *arg, void *item) )
{

}

int main () {
  board_t *board = board_new();
  if (valid_input(board, 5, 1, 2)) {
    printf("valid input\n");
  }
  else {
    printf("invalid input\n");
  }
}