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
#include <stdbool.h>
#include <time.h>
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
        if (valid_input(sudoku, row, col, num)) {

            //tentatively set
            board_set(sudoku, row, col, num);

            //continue with solving, if works, return true, success
            if (solver(sudoku)) {
                return true;
            }
            //doesn't work, go back to 0
            board_set(sudoku, row, col, 0);
        }
    }

    return false;
}
\

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
        if (valid_input(sudoku, row, col, num)) {

            //tentatively set
            board_set(sudoku, row, col, num);
        
            //continue with solving, if works, return true, success
            if (solver(sudoku)) {
                return true;
            }
            //doesn't work, go back to 0
            board_set(sudoku, row, col, 0);
        
        }
    }
    return false;
}

/***************** unique_solution *****************/
/*
Unique_solution tests if a puzzle has more than one solution

Takes:
    board_t* – a pointer to a sudoku puzzle
Returns:
    true, if the puzzle has one solution
    false, if the puzzle has multiple solutions
*/
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
                  board_set(sudoku, i, j, num);
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

///////////////////////////////////////////
/****************** create ****************/
///////////////////////////////////////////

/***************** random_list *****************/
/*
Random_list makes a randomized list of numbers 1 - 9

Takes:
    No parameters
Returns:
    A randomized list of numbers 1 - 9
*/
int *random_list() {
    int *list = calloc(sizeof(int), 9);
    for (int i = 1; i < 10; i++) {
        list[i - 1] = i;
    }
    srand(time(NULL) + rand());
    for (int j = 0; j < 9; j++) {
        int swap = rand() % (9 - j);
        int temp = list[swap];
        list[swap] = list[8 - j];
        list[8 - j] = temp;
    }
    return list;
}



void remove_slots(board_t* board, int empty_slots, int emptied)
{
    srand(time(0));
    
    int row = 0;
    int col = 0;
    while (emptied < empty_slots) {
        
        // Generate random number
        int rand_num = rand();
        
        // If random number matches and the current slot is not already set to 0, set it to 0
        if (rand_num % 9 == 0 && board_get(board, row, col) != 0) {
            int copy = board_get(board, row, col);
            board_set(board, row, col, 0);
            // one of the other based on slot
            if (!unique_solution(board)) {
                board_set(board, row, col, copy);
                continue;
            }
            
            // Increment the number of slots we have emptied
            emptied++;
        }
        
        // Update row, col
        if (row < 8) {
            row++;
        }
        else if (col < 8) {
            row = 0;
            col++;
        }
        else {
            row = 0;
            col = 0;
        }
    }
}

/***************** solver_random *****************/
/*
Solver_random takes a non-empty non-solved sudoku board and recursively runs through each slot using a backtracking method to solve the puzzle.
Solver_random tries numbers based on a randomized list, to generate puzzles that differ every time

Takes:
    board_t* – a pointer to a non-empty non-solved sudoku puzzle
Returns:
    true, if successfully solved
    false, if error
*/
static bool solver_random(board_t* sudoku, int *list)
{
    int row, col;

    //goes through sudoku, checks if there are empty spots
    //if empty, parameter keeps the row/column through param
    if (!empty_location(sudoku, &row, &col)) {
        return true;
    }


    //using the row/column values from empty_location()
    free(list);
    list = random_list();
    for (int i = 0; i < 9; i++) {
        
        if (valid_input(sudoku, row, col, list[i])) {
            //tentatively set
            board_set(sudoku, row, col, list[i]);
    

            //continue with solving, if works, return true, success
            if (solver_random(sudoku, list)) {
                return true;
            }
            //doesn't work, go back to 0
            board_set(sudoku, row, col, 0);
        
        }
    }

    return false;
}

bool sudoku_solve_random(board_t* sudoku) {
    int *list = random_list();
    if (solver_random(sudoku, list)) {
      
        return true;
    }
    else {
        fprintf(stderr, "sudoku not solvable\n");
        return false;
    }
}



board_t* sudoku_create()
{   
    // Setup
    board_t* board = board_new();
    int empty_slots = 50;       // can change this later based on the difficulty_level
    int emptied = 0;
    
    // Fills in the rest of the slots --> have to check whether this will work (do we need to set the bool of each of the matrices slots as true?)
    if (!sudoku_solve_random(board)) {
        fprintf(stderr, "sudoku_create failed: sudoku_solve returned false\n");
        return false;
    }
    
    // Remove elements randomly to complete the game
    remove_slots(board, empty_slots, emptied);
    board_print(board);
    return board;
}

int main () {
    board_t *board = sudoku_create();
    if (unique_solution(board)) {
        printf("worked\n");
    }
    sudoku_solve(board);
}