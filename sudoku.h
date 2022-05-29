/* 
 * sudoku.h - header file
 * 
 * The 'sudoku' module is split into two major modes: 'solve' and 'create'. The 'solve' 
 * mode will take an unsolved sudoku puzzle through stdin, solve the puzzle, and output 
 * the solution to stdout. The 'create' mode will take no stdin and instead create a new 
 * sudoku puzzle that will be outputted to stdout.
 * 
 *
 * DataNiners: Ashley Liang, Matthew Kim, Lucy Korte, Ryan Kim
 * CS50, 22S
 */

#include <stdio.h>
#include <stdlib.h>
#include "board.h"


/**************** functions ****************/

/***************** sudoku_create *****************/
/* creates a unique, solvable sudoku
 */
void sudoku_create();

/***************** board_new *****************/
/* solves a solvable sudoku, otherwise prints "nonsolvable sudoku"
 */
void sudoku_solve();
