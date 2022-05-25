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

/**************** local types ****************/
typedef struct slot {
  int num;                        // integer key provided by caller                 
  bool given;                     // boolean signifying a given number
} slot_t;


/**************** global types ****************/
typedef struct board {
  slot_t ***grid;       
} board_t;


static slot_t *slot_new(int num, bool given) {
  slot_t *slot = malloc(sizeof(slot_t));
  slot->num = num;
  slot->given = given;
  return slot;
}

board_t *board_new() 
{
  board_t *board = malloc(sizeof(board_t));
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      slot_t *slot = slot_new(0, false);
      board->grid[i][j] = slot;
      // board->grid[i][j]->given = false;
      // board->grid[i][j]->num = 0;
    }
  }
  board->grid[0][0]->num = 2;

  return board;
}

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


int main () {
  board_t *board = board_new();
  if (valid_input(board, 2, 0, 1)) {
    printf("problem\n");
  }
  else {
    printf("test succeeded\n");
  }
}