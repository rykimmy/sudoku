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
#include "libcs50/bag.h"


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

///////////////////////////////////////////
/****************** create ****************/
///////////////////////////////////////////

/*
General Pseuo Code:
1. Fill all the diagonal 3x3 matrices.

2. Fill recursively rest of the non-diagonal matrices.
   For every cell to be filled, we try all numbers until
   we find a safe number to be placed.  
   
3. Once matrix is fully filled, remove K elements
   randomly to complete game.
*/
bool sudoku_create()
{   
    // Setup
    board_t* board = board_new();
    int empty_slots = 40;       // can change this later based on the difficulty_level
    int emptied = 0;
    
    // Randomly sets the slots of the diagonal matrices
    fill_matrix(board, 0, 3);
    fill_matrix(board, 3, 6);
    fill_matrix(board, 6, 9);
    
    // Fills in the rest of the slots --> have to check whether this will work (do we need to set the bool of each of the matrices slots as true?)
    if (!sudoku_solve(board)) {
        fprintf(stderr, "sudoku_create failed: sudoku_solve returned false\n");
        return false;
    }
    
    // Remove elements randomly to complete the game
    remove_slots(board, empty_slots, emptied);
}

void fill_matrix(board_t* board, int min_range, int max_range)
{
    // Initializing the bag to hold numbers 1-9
    bag_t* numbers = bag_new();
    for (int i = 1; i < 10; i++) {
        bag_insert(numbers, i);
    }
    
    // Randomly set each slot to one of the numbers in the bag (1-9)
    for (int i = min_range; i < max_range; i++) {
        for (int j = min_range; j < max_range; j++) {
            int slot_num = bag_extract(numbers);
            board[i][j]->num = slot_num;    // or if we get rid of slot then board[i][j] = slot_num;
            board[i][j]->given = true;
        }
    }
    
    // Cleanup
    bag_delete(numbers);
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
        if (rand_num % 9 == 0 && board[row][col]->num != 0) {
            board[row][col] = 0;
            // one of the other based on slot
            board[row][col]->num = 0;
            board[row][col]->given = false;
            
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

int main () {
    board_t *sudoku = build_sudoku();
   
    if (unique_solution(sudoku)) {
        printf("unique solution\n");
    }
    else {
        printf("multiple solutions\n");
    }
}