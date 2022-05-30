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
#include "board.h"


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

static bool solver_backward(board_t* sudoku)
{
    int row, col;

    //goes through sudoku, checks if there are empty spots
    //if empty, parameter keeps the row/column through param
    if (!empty_location(sudoku, &row, &col)) {
        
        return true;
    }


    //using the row/column values from empty_location()
    for (int num = 9; num > 0; num--) {
        // printf("trying %d in row %d col %d\n", num, row, col);
        if (valid_input(sudoku, row, col, num)) {

            //tentatively set
            // sudoku->grid[row][col]->num = num;
            // printf("putting %d at row %d col %d\n", num, row, col);
            board_set(sudoku, row, col, num, false);
            // printf("put %d in row %d col %d\n", num, row, col);
            
            // board_print(sudoku);
            // printf("------------------\n");

            //continue with solving, if works, return true, success
            if (solver(sudoku)) {
                return true;
            }
            //doesn't work, go back to 0
            board_set(sudoku, row, col, 0, false);
        
        }
    }
    return false;
}


bool unique_solution(board_t *sudoku) {
    board_t *copy_forward = board_copy(sudoku);
    board_t *copy_backward = board_copy(sudoku);
    solver(copy_forward);
    solver_backward(copy_backward);
    for (int i=0; i < 9; i++){
        for (int j=0; j < 9; j++){
            if (board_get(copy_forward, i, j) != board_get(copy_backward, i, j)) {
                return false;
            }
        }
    }
    return true;
}


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

bool sudoku_solve_backward(board_t* sudoku) {
    
    if (solver_backward(sudoku)) {
        board_print(sudoku);
        return true;
    }
    else {
        fprintf(stderr, "sudoku not solvable\n");
        return false;
    }
}

int main () {
    board_t *sudoku = build_sudoku();
   
    if (unique_solution(sudoku)) {
        printf("unique solution\n");
    }
    else {
        printf("multiple solutions\n");
    }
}