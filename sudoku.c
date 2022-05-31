/* 
 * sudoku.c - Sudoku module that holds the APIs for the sudoku 'create' and 'solve' functionality
 * 
 * The 'sudoku' module is split into two major modes: 'solve' and 'create'. 
 * The 'solve' mode will take an unsolved sudoku puzzle through stdin, solve the puzzle, and output the solution to stdout. 
 * The 'create' mode will take no stdin and instead create a new sudoku puzzle that will be outputted to stdout.
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
* See sudoku.h for more information
*/
static bool solver(board_t* sudoku)
{
    int row, col;

    //goes through sudoku, checks if there are empty spots
    //if empty spot is found, row and col set to empty spot
    if (!empty_location(sudoku, &row, &col)) {
        return true;
    }


    //using the row/column values from empty_location()
    //loop through numbers 1 - 9
    for (int num = 1; num < 10; num++) {
        //check if number can be inputted
        if (valid_input(sudoku, row, col, num)) {

            //tentatively set
            board_set(sudoku, row, col, num);

            //continue with solving, if works, return true, success
            if (solver(sudoku)) {
                return true;
            }
            //doesn't work, reset slot to 0
            board_set(sudoku, row, col, 0);
        }
    }
    // puzzle not solvable
    return false;
}
\

/***************** solver_backward *****************/
/*
* See sudoku.h for more information
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
    //puzzle not solvable
    return false;
}

/***************** unique_solution *****************/
/*
* See sudoku.h for more information
*/
bool unique_solution(board_t *sudoku) {
    // make copies of the sudoku board to check for multiple solutions
    board_t *copy_forward = board_copy(sudoku);
    board_t *copy_backward = board_copy(sudoku);
    solver(copy_forward);
    solver_backward(copy_backward);
    // check if the puzzles are the same when solved with different solvers
    for (int i=0; i < 9; i++){
        for (int j=0; j < 9; j++){
            if (board_get(copy_forward, i, j) != board_get(copy_backward, i, j)) {
                board_delete(copy_forward);
                board_delete(copy_backward);
                return false;
            }
        }
    }
    // free memory
    board_delete(copy_forward);
    board_delete(copy_backward);
    return true;
}

/***************** build_sudoku *****************/
/*
* See sudoku.h for more information
*/
board_t *build_sudoku() 
{
    board_t* sudoku = board_new();
    int num;
    // loop through slots in board, read number from stdin
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (scanf("%d", &num) == 1) {
                board_set(sudoku, i, j, num);
            }
        }
    }
    return sudoku;
}

/***************** sudoku_solve *****************/
/*
* See sudoku.h for more information
*/
bool sudoku_solve(board_t* sudoku) {
    // print the solved board if the board is solvable
    if (solver(sudoku)) {
        board_print(sudoku);
        board_delete(sudoku);
        return true;
    }
    else {
        fprintf(stderr, "sudoku not solvable\n");
        board_delete(sudoku);
        return false;
    }
}


///////////////////////////////////////////
/****************** create ****************/
///////////////////////////////////////////

/***************** random_list *****************/
/*
* See sudoku.h for more information
*/
int *random_list() {
    int *list = calloc(sizeof(int), 9);
    if (list == NULL) {
        fprintf(stderr, "Error allocating memory\n");
    }
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


/***************** remove_slots *****************/
/*
* See sudoku.h for more information
*/
void remove_slots(board_t* board, int empty_slots, int emptied)
{
    srand(time(0));
    
    int row = 0;
    int col = 0;
    // continue emptying slots until correct number are emptied
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
* See sudoku.h for more information
*/
static bool solver_random(board_t* sudoku)
{
    int row, col;

    //goes through sudoku, checks if there are empty spots
    //if empty, parameter keeps the row/column through param
    if (!empty_location(sudoku, &row, &col)) {
        return true;
    }


    //using the row/column values from empty_location()
    for (int i = 0; i < 9; i++) {
        // create a random list to pull numbers from
        int *list = random_list();
        if (valid_input(sudoku, row, col, list[i])) {
            //tentatively set
            board_set(sudoku, row, col, list[i]);
           

            //continue with solving, if works, return true, success
            if (solver_random(sudoku)) {
                free(list);
                return true;
            }
            //doesn't work, go back to 0
            board_set(sudoku, row, col, 0);
        }
        free(list);
    }
    // puzzle not solvable
    return false;
}


/***************** sudoku_create *****************/
/*
* See sudoku.h for more information
*/
board_t* sudoku_create(int difficulty_level)
{   
    // Create empty board
    board_t* board = board_new();
    int empty_slots = difficulty_level;       // can change this later based on the difficulty_level
    int emptied = 0;
    
    // check if solver_random made a puzzle
    if (!solver_random(board)) {
        fprintf(stderr, "sudoku_create failed: sudoku_solve returned false\n");
        return false;
    }
    
    // Remove elements randomly to complete the game
    remove_slots(board, empty_slots, emptied);
    board_print(board);
    board_delete(board);
    return board;
}


/***********************************************/
int main (const int argc, char *argv[]) {
    int status = 0;
    int difficulty_level;
    
    // Parsing Arguments:


    // test number of arugments
    if (argc > 4 || argc < 2){
        fprintf(stderr, "invalid command-line arguments or usage: ./sudoku ['create', 'solve'] ['easy', 'medium', 'hard'] \n");
        return status;
    }
    // 'solve' mode
    if (strcmp(argv[1], "solve") == 0)
    {
        printf("Solving sudoku puzzle\n");
        board_t *sudoku = build_sudoku();
        sudoku_solve(sudoku);
    }
    // 'create' mode
    else if (strcmp(argv[1], "create") == 0)
    {
        // If a third argument is provided, check which difficulty
        if (argc == 3)
        {
            int easy = 40;
            int medium = 50;
            int hard = 55;
            if (strcmp(argv[2], "easy") == 0)
            {
                difficulty_level = easy;      // 40 empty slots
                printf("Creating new easy sudoku puzzle\n");
                sudoku_create(difficulty_level);
            }
            else if (strcmp(argv[2], "medium") == 0)
            {
                difficulty_level = medium;      // 45 empty slots
                printf("Creating new medium sudoku puzzle\n");
                sudoku_create(difficulty_level);
            }
            else if (strcmp(argv[2], "hard") == 0)
            {
                difficulty_level = hard;      // 50 empty slots
                printf("Creating new hard sudoku puzzle\n");
                sudoku_create(difficulty_level);
            }
            else
            {
                fprintf(stderr, "invalid command-line arguments or usage: ./sudoku ['create', 'solve'] ['easy', 'medium', 'hard'] \n");
                status++;
                return status;
            }
        }
        // If difficulty_level is not set by caller, naturally set to 'easy'
        else if (argc == 2)
        {
            difficulty_level = 40;
            printf("Creating new sudoku puzzle\n");
            sudoku_create(difficulty_level);
        }
        else
        {
            fprintf(stderr, "invalid command-line arguments or usage: ./sudoku ['create', 'solve'] ['easy', 'medium', 'hard'] \n");
            status++;
            return status;
        }
    }
    else
    {
        fprintf(stderr, "invalid command-line arguments or usage: ./sudoku ['create', 'solve'] ['easy', 'medium', 'hard']");
        status++;
        return status;
    }
    
    return status;
}
