/* 
 * fuzz.c - module that helps with fuzz testing
 * 
 * This module will check the validity of solved sudoku puzzle
 * 
 *
 * DataNiners: Ashley Liang, Matthew Kim, Lucy Korte, Ryan Kim
 * What this module tests: Valid sudoku board
 * How?
 *  - sum of rows, columns, and subsquares are each equal to 45
 *  - the solved sudoku board has not changed any previosuly given values
 * CS50, 22S
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libcs50/memory.h"
#include "libcs50/file.h"
#include "libcs50/counters.h"
#include "board.h"

/**** function declarations ****/
board_t *create_puzzle(char *filename);
static void check_duplicates(board_t *board);
static void check_sum(board_t *board);
static bool check_changed_givens(board_t *original, board_t *check);

/***************** Main *****************/
/**
 * Input: either use keyword 'filled' or 'check' to get two types of responses
 * 'filled' will require a solvable sudoku board and its completed self. Will return whether the sudoku solver has accidentally covered over given values
 * 'check' will require a solved sudoku board and will see if the board is valid.
**/
int main (const int argc, char *argv[]) {
     if (argc < 1 || argc > 4){
          fprintf(stderr, "Please input: ./fuzz ['filled','check'] ['file1'] ['file2'] \n");
          exit(3);
     } 

     // Check to see if the board has been filled in correctly (hasn't changed already filled cells)
     if (strcmp(argv[1], "filled") == 0) {
          char *created = argv[2]; // file created by sudoku create
          char *solved = argv[3]; // file created by sudoku solve
          // boards for create and solve
          board_t *board_created = create_puzzle(created); 
          board_t *board_solved = create_puzzle(solved);

          // check if the solver successfully filled in the correct slots
          if (check_changed_givens(board_created, board_solved) == true){ 
               printf("Solver -successfully- filled in the correct slots! \n");
               board_delete(board_created);
               board_delete(board_solved);
          } else {
               fprintf(stderr, "Solver -failed- to filled in the correct slots \n");
               board_delete(board_created);
               board_delete(board_solved);
               exit(5);
          }

     } else if (strcmp(argv[1], "check") == 0) {
          char *filename = argv[2];
          board_t *board = create_puzzle(filename);
          // run the duplicate and sum tests
          check_duplicates(board);
          check_sum(board);
          printf("Solver has no duplicate or sum errors!! \n");
          board_delete(board);
     } else {
          fprintf(stderr, "Please input: ./fuzz ['filled','check'] ['file1'] ['file2'] \n");
          exit(3);
     }

     printf("passed \n");
     
} 

/***************** Create_Puzzle *****************/
/**
 *  input: Assume filename of existing puzzle
 *  output: Board created by reading the file
**/
board_t *create_puzzle(char *filename){
     // open file
     FILE *fp;
     fp = assertp(fopen(filename, "r"), "error opening file \n");

     // setup variables
     board_t *board = board_new(); // new board
     char *line;
     int slot = 0;
     int row = 0;

     // Check row sum and add to a board
     while ((line = freadlinep(fp)) != NULL) {
          char *token = strtok(line, " ");
          int col = 0; // index

          while (token != NULL) {
               sscanf(token, "%d", &slot); // convert from string to integer
               board_set(board, row, col, slot); // create the board
               token = strtok(NULL, " ");
               col += 1;
          }
          row += 1; // update row
          col = 0; // reset column
          count_free(line);
          // if reaches here, row is valid
     }
     fclose(fp);
     return board;
}

/***************** Check_Duplicates *****************/
/**
 * loops through each row and colum to check for duplicates
 * loops through each subsquare to check for duplicates. Uses a counters struct to keep track of numbers.
 * Input: solved sudoku board
 * Output: exit program if finds error
**/
static void check_duplicates(board_t *board)
{
     // checking the rows
     for (int k = 0; k < 9; k++){
          // check each column
          for (int i = 0; i < 9; i++){
               // compare to other slots in the colum
               for (int j = 0; j < 9 ; j++) {
                    if ((board_get(board, k, i) == board_get(board, k, j))&& (i != j)){
                         fprintf(stderr, "There are duplicates in row %d \n", k);
                         exit(4);
                    }
                    if ((board_get(board, i, k) == board_get(board, j, k))&& (i != j)){
                         fprintf(stderr, "There are duplicates in column %d \n", k);
                         exit(4);
                    }
               }
          }
     }
     // check for duplicated within subsquare
     for (int row = 0; row < 9; row += 3){// start at the 1st row
          for (int col=0; col < 9; col +=3){
               // the subsquare
               counters_t *counters = counters_new();
               for(int i = row; i < row + 3; i++){
                    for(int j = col; j < col + 3; j++){
                         int slot = board_get(board, i, j);
                         // if the slot value has not been added to the counters
                         if (counters_get(counters, slot) == 0){
                              counters_add(counters, slot);
                         } else{
                              fprintf(stderr, "number already exists in the subsquare! \n");
                         }
                    }
               }
               counters_delete(counters);
          }
     }
}

/***************** Check_Sum *****************/
/**
 * input: completed sudoku board
 * Output: error if the sum of a row, column, or subsquare is not equal to 45
**/
static void check_sum(board_t *board)
{
     // check each row adds up
     for (int k = 0; k < 9; k++){
          int total = 0; // initialize total
          // check each column
          for (int i = 0; i < 9; i++){
               int slot = board_get(board, k, i); // set slot
               total = total + slot; // add slot to total
               slot = 0; // reset slot
          }
          if (total != 45){
               fprintf(stderr, "Error: Puzzle row does not add up to 45 \n");
               exit (2);
          }
     }
     
     // check each column adds up
     for (int k = 0; k < 9; k++){
          int total = 0; // initialize total
          // check each row
          for (int i = 0; i < 9; i++){
               int slot = board_get(board, k, i); // set slot
               total = total + slot; // add slot to total
               slot = 0; // reset slot
          }
          if (total != 45){
               fprintf(stderr, "Error: Puzzle column does not add up to 45 \n");
               exit (2);
          }
     }
     // check for the subquare sums being different
     for (int row = 0; row < 9; row += 3){// start at the 1st row
          for (int col=0; col < 9; col +=3){
               // the subsquare
               int total = 0;
               for (int i = row; i < row + 3; i++){
                    for (int j = col; j < col + 3; j++){
                         int slot = board_get(board, i, j);
                         // if the slot value has not been added to the counters
                         total = total + slot;
                    }
               }
               // check if the sum is equal to 45
               if (total != 45){
                    fprintf(stderr, "Sum of subsquare not equal to 45 \n");
                    exit(6);
               }
          }
     }

}

/***************** Check_Changed_Givens *****************/
/**
 * Compares the original and the solved board and returns false if a given number was changed
**/
static bool check_changed_givens(board_t *original, board_t *check) {
     for (int i = 0; i < 9; i++){
          for (int j = 0; j < 9; j++) {
               if (board_get(original, i, j) != 0) {
                    if (board_get(original, i, j) != board_get(check, i, j)) {
                         return false;
                    }
               }
          }
     }
     return true;
}