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
#include "board.c"

bool solver(board_t* sudoku);
board_t *build_sudoku(); 

// void sudoku_create() {
    


//     else if (ans < 9) {
//         solve_recurse(board, ans++, )
//     }

//     if (valid_input(board, ans, row, col) && row == 8 && col == 8) {
//         return true;
//     }


    
//     while (!valid_input(board, ans, row, col)) {
//         if (ans == 9) {
//             return false;
//         }
//         ans++
//     }

//     if (row < 8) {
//         solve_recurse(board, 1, row++, col);
//     }
//     else if (col < 8) {
//         solve_recurse(board, 1, 0, col++);
//     }
//     else {

//     }
//     solve_recurse(board, 1, row++)



//     if (valid_input(board, ans, row, col)) {
//         if (row == 8 && col == 8) {
//             return true;
//         }
//         if (row < 9) {
//             solve_recurse(board, 1, row++, col);
//         }
//         else if (col < 9) {
//             solve_recurse(board, 1, 0, col++)
//         }
//     }
//     else {
//         solve_recurse(board, ans++, row, col);
//     }
// }

///////////////////////////////////////////
/****************** solve ****************/
///////////////////////////////////////////

/***************** sudoku_solve *****************/
/*
Solves a sudoku puzzle.

Takes:
    nothing
Returns:
    true, if successfully solved
    false, if error
Uses:
    build_sudoku - reads from stdin and builds the sudoku board
    solver - recursive function that goes through and solves the puzzle
    board_print - prints the sudoku board after it's been successfully solved
*/

void sudoku_solve() {
    board_t* sudoku = build_sudoku();
    if (solver(sudoku)) {
        board_print(sudoku);
    }
    else {
        fprintf(stderr, "sudoku not solvable");
    }
}

/***************** build_sudoku *****************/
/*
Creates a new board struct and reads from stdin to correctly format the provided sudoku puzzle.

Takes:
    nothing
Returns:
    board_t* – the sudoku board filled with the given numbers
*/
board_t *build_sudoku() 
{
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

/***************** solver *****************/
/*
Solver takes a non-empty non-solved sudoku board and recursively runs through each slot using a backtracking method to solve the puzzle.

Takes:
    board_t* – a pointer to a non-empty non-solved sudoku puzzle
Returns:
    true, if successfully solved
    false, if error
*/
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