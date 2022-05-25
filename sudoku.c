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

void sudoku_solve() {
  
}

*sudoku_t build_sudoku() {
    sudoku_t* sudoku = sudoku_new();
    int num;
    while (scanf("%d", &num) == 1) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                //if isn't 0, meaning that it is a set number given by sudoku
                if (num != 0) {
                    slot_set(i, j, num, true);
                }
                else {
                    slot_set(i, j, num, false);
                }
            }
        }
    }
}