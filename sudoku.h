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
#include <stdbool.h>
#include <time.h>
#include "board.h"


/**************** functions ****************/
/***************** solver *****************/
/*
Solver takes a non-empty non-solved sudoku board and recursively runs through each slot using a backtracking method to solve the puzzle.
Solver inputs numbers working from 1 - 9

Takes:
    board_t* – a pointer to a non-empty non-solved sudoku puzzle
Returns:
    true, if successfully solved
    false, if error
*/
static bool solver(board_t* sudoku);

/***************** solver_backward *****************/
/*
Solver_backward takes a non-empty non-solved sudoku board and recursively runs through each slot using a backtracking method to solve the puzzle.
Solves puzzle by trying numbers looping from 9 down to 1
Used to test if a puzzle has multiple solutions

Takes:
    board_t* – a pointer to a non-empty non-solved sudoku puzzle
Returns:
    true, if successfully solved
    false, if error
*/
static bool solver_backward(board_t* sudoku);

/***************** unique_solution *****************/
/*
Unique_solution tests if a puzzle has more than one solution

Takes:
    board_t* – a pointer to a sudoku puzzle
Returns:
    true, if the puzzle has one solution
    false, if the puzzle has multiple solutions
*/
static bool unique_solution(board_t *sudoku);

/***************** build_sudoku *****************/
/*
Stores a puzzle inputted from stdin into a board_t struct

Takes:
    No parameters
Returns:
    A board struct holding inputted data
*/
static board_t *build_sudoku();

/***************** sudoku_solve *****************/
/*
Calls solver() and prints resulting board if the puzzle is solvable

Takes:
    A sudoku board
Returns:
    True if board is solved
    False if board cannot be solved
*/
static bool sudoku_solve(board_t* sudoku);

/***************** random_list *****************/
/*
Random_list makes a randomized list of numbers 1 - 9

Takes:
    No parameters
Returns:
    A randomized list of numbers 1 - 9
*/
static int *random_list();

/***************** remove_slots *****************/
/*
Remove slots removes a specified number of slots from a completed puzzle
Ensures resulting puzzle is solvable by only one solution

Takes:
    A sudoku board, a number of empty slots, and a number of slots emptied so far
Returns:
    Nothing
*/
static void remove_slots(board_t* board, int empty_slots, int emptied);

/***************** solver_random *****************/
/*
Solver_random takes a non-empty non-solved sudoku board and recursively runs through each slot using a backtracking method to solve the puzzle.
Solver_random tries numbers based on a randomized list, to generate puzzles that differ every time
Allows sudoku_create() to generate a random puzzle

Takes:
    board_t* – a pointer to a non-empty non-solved sudoku puzzle
Returns:
    true, if successfully solved
    false, if error
*/
static bool solver_random(board_t* sudoku);

/***************** sudoku_create *****************/
/*
Sudoku_create generates a random puzzle given a difficulty level
Default difficulty level is easy

Takes:
    A difficulty level to create sudoku
Returns:
    A sudoku puzzle
*/
static void sudoku_create(int difficulty_level);