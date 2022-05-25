/* 
 * board.c - 'board' module for Sudoky
 *
 *
 * Data Niners CS50 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/////////////////////////////////
/********** Local Types ********/
/////////////////////////////////

typedef struct slot {
  int num;                        // integer key provided by caller                 
  bool given;                     // boolean signifying a given number
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

void board_set(board_t *brd, int num, int row, int col)
{
    // assertp(brd,"[board.c, board_set] ");
    brd->grid[row][col]->num = num;
}

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

void board_print()
{

}

void board_delete()
{

}

void board_iterate()
{

}


int main () {
    board_t *board = board_new();
    board_set(board, 5, 3, 5);
    slot_get(board, 3 ,5);
}