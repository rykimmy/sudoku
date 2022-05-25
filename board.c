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

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct slot {   
  int num_inserted;           
  bool set_number;       
} slot_t;

/**************** global types ****************/
typedef struct board {
  slot_t** arrays;
} board_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see board.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static slot_t *new_slot(int row, int column, int num);

/**************** board_new() ****************/
/* see board.h for description */
board_t *counters_new(void)
{
  //allocate memory for counters set
  board_t *board = count_malloc(sizeof(board_t));

  if (board == NULL) {
    return NULL;              // error allocating counters set
  } else {
    // initialize contents of counters structure
    int rows = 9;
    int columns = 9;
    board->arrays = count_calloc_assert(rows, columns * sizeof(slot_t*), "error creating array");
    //insert 9 arrays of 9 * slot into board
  }
}