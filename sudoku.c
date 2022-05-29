/* 
 * sudoku.c - Sudoku module that holds the APIs for the sudoku 'create' and 'solve' functionality
 * 
 * The 'sudoku' module is split into two major modes: 'solve' and 'create'. The 'solve' mode will take an unsolved sudoku puzzle through stdin, solve the puzzle, and output the solution to stdout. The 'create' mode will take no stdin and instead create a new sudoku puzzle that will be outputted to stdout.
 * 
 *
 * DataNiners: Ashley Liang, Matthew Kim, Lucy Korte, Ryan Kim
 * CS50, 22S
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

///////////////////////////////////////////
/****************** Solve ****************/
///////////////////////////////////////////

/***************** solver *****************/
/*
Solver takes a non-empty non-solved sudoku board and recursively runs through each slot using a backtracking method to solve the puzzle.

Takes:
    board_t* – a pointer to a non-empty non-solved sudoku puzzle
Returns:
    true, if successfully solved
    false, if error
*/
static bool solver(board_t* sudoku)
{
    int row, col;

    //goes through sudoku, checks if there are empty spots
    //if empty, parameter keeps the row/column through param
    if (!empty_location(sudoku, &row, &col)) {
        
        return true;
    }


    //using the row/column values from empty_location()
    for (int num = 1; num < 10; num++) {
        // printf("trying %d in row %d col %d\n", num, row, col);
        if (valid_input(sudoku, row, col, num)) {

            //tentatively set
            // sudoku->grid[row][col]->num = num;
            board_set(sudoku, row, col, num, false);
            // printf("put %d in row %d col %d\n", num, row, col);
            
            // board_print(sudoku);
            // printf("------------------\n");

            //continue with solving, if works, return true, success
            if (solver(sudoku)) {
                return true;
            }
            //doesn't work, go back to 0
            // sudoku->grid[row][col]->num = 0;
            board_set(sudoku, row, col, 0, false);
            // printf("COLUMN = %d\n", col);
        }
    }

    return false;
}

/***************** sudoku_solve *****************/
/*
sudoku_solve works as the driving function behind the 'solver' and calls on the necessary functions to buid and solve the sudoku puzzle.

Takes:
    board_t* – a pointer to a non-empty non-solved sudoku puzzle
Returns:
    true, if successfully solved
    false, if error
*/
bool sudoku_solve(board_t* sudoku) {
    
    if (solver(sudoku)) {
        board_print(sudoku);
        return true;
    }
    else {
        fprintf(stderr, "sudoku not solvable\n");
        return false;
    }
}

/***************** build_sudoku *****************/
/*
build_sudoku reads from stdin and builds a sudoku board.

Takes:
    nothing
Returns:
    A sudoku puzzle ready to be solved.
*/
board_t *build_sudoku() 
{
    board_t* sudoku = board_new();
    int num;
      for (int i = 0; i < 9; i++) {
          for (int j = 0; j < 9; j++) {
              //only need to set if not 0 because automatically 0 and false
              if (scanf("%d", &num) == 1) {
                  board_set(sudoku, i, j, num, true);
              }
          }
      }
    return sudoku;
}

///////////////////////////////////////////
/****************** create ****************/
///////////////////////////////////////////

/*
General Pseuo Code:
1. Fill all the diagonal 3x3 matrices.
- when randomly inputting to the three matrices, we can use a bag to hold 1-9 and 'extract' to randomize
- we then check if each the number works (valid_input or can create another helper function that just checks for the box)
- do this for each of the three diagonal matrices, probably within a nested for-loop for each matrix

2. Fill recursively rest of the non-diagonal matrices.
   For every cell to be filled, we try all numbers until
   we find a safe number to be placed.  
3. Once matrix is fully filled, remove K elements
   randomly to complete game.
*/
void sudoku_create()
{
    board_t* board = board_new();
    
    srand(time(0));
    
    //
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            
        }
    }
}

int main () {
    board_t *sudoku = build_sudoku();
    sudoku_solve(sudoku);
}

    
   
    
    
    
