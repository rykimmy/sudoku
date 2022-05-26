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

void sudoku_create() {
    

}

bool sudoku_solve() {
    board_t* sudoku = build_sudoku();
    if (sudoku_solve(sudoku)) {
        board_print(sudoku);
    }
    else {
        fprintf(stderr, "sudoku not solvable");
    }
}

board_t *build_sudoku() {
    board_t* sudoku = board_new();
    int num;
    while (scanf("%d", &num) == 1) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                //only need to set if not 0 because automatically 0 and false
                if (num != 0) {
                    board_set(sudoku, i, j, num, true);
                }
            }
        }
    }
    return sudoku;
}

bool solver(board_t* sudoku)
{
    int row, col;

    //goes through sudoku, checks if there are empty spots
    //if empty, parameter keeps the row/column through param
    if (!empty_location(sudoku, &row, &col)) {
        return true;
    }

    //using the row/column values from empty_location()
    for (int num = 1; num < 10; num++) {
        if (valid_input(sudoku, row, col, num)) {
            //tentatively set
            board_set(sudoku, row, col, num, false);

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