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

void sudoku_solve(board_t* board) {
    /*
    1. Build sudoku puzzle from stdin
    2. Recurse through every slot
    */
    
}

bool solve_recurse() {
    /*
    1. for each slot; check if it changeable or not
        2. if changeable:
            solve_recurse(row, col, slot):
            int i = 1
            while (recurse_helper(i) returns false)
                if (i == 9), quit (error)
                i++

    */
    slot_t* *slist[]; // holds a list of all the non-given slots in order

    solve_recurse(board, row, col);

    if (row == 9) {

    }

    for (int i = 1; i < 10; i++) {
        if (valid_input(board, i, row, num)) {
            if (solve_recurse(board, row, col)) {
                board[row][col]->num = i;
                return true;
            }
        }
        
    }
    

    if (board[row][col]->given) {
        // go to next slot
        if (row < 8) {
            
        }
    }

    while (!valid_input(board, ans, row, col)) {
        if (ans == 9) {
            return false;
        }
        ans++;
    }
    if (solve_recurse(board, ans, row, col)) {
        board[row][col]->num = ans;
        return true;
    }
    else {
        solve_recurse(board, ans+1, row, col);
    }

    if (ans < 9 && solve_recurse(board, ans++, row, col)) {

    }


    else if (ans < 9) {
        solve_recurse(board, ans++, )
    }

    if (valid_input(board, ans, row, col) && row == 8 && col == 8) {
        return true;
    }


    
    while (!valid_input(board, ans, row, col)) {
        if (ans == 9) {
            return false;
        }
        ans++
    }

    if (row < 8) {
        solve_recurse(board, 1, row++, col);
    }
    else if (col < 8) {
        solve_recurse(board, 1, 0, col++);
    }
    else {

    }
    solve_recurse(board, 1, row++)



    if (valid_input(board, ans, row, col)) {
        if (row == 8 && col == 8) {
            return true;
        }
        if (row < 9) {
            solve_recurse(board, 1, row++, col);
        }
        else if (col < 9) {
            solve_recurse(board, 1, 0, col++)
        }
    }
    else {
        solve_recurse(board, ans++, row, col);
    }
}

void recurse_helper() {
    /*
    int i = 1

    */
}

sudoku_t* build_sudoku() {
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