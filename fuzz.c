/* 
 * fuzz.c - module that helps with fuzz testing
 * 
 * This module will check the validity of solved sudoku puzzle
 * 
 *
 * DataNiners: Ashley Liang, Matthew Kim, Lucy Korte, Ryan Kim
 * CS50, 22S
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libcs50/memory.h"
#include "../libcs50/file.h"
#include "board.h"

static void check_puzzle(char *filename);
static void check_duplicates(board_t *board);
static void check_sum(board_t *board);



static void check_puzzle(char *filename){
     // open file
     FILE *fp;
     fp = assertp(fopen(filename, "r"), "error opening file \n");
     if (lines_in_file(fp) != 8){ // returns 8 if there are 9 rows
          fprintf(stderr, "Error: Puzzle does not have 9 rows \n");
          exit(1);
     }

     // setup variables
     board_t *board = board_new(); // new board
     char *line;
     int slot = 0;
     int total = 0;
     int row = 0;

     // Check row sum and add to a board
     while ((line = freadlinep(fp)) != NULL) {
          if (strlen(line) != 17){
               fprintf(stderr, "Error: Puzzle does not have 9 columns \n");
               exit(2);
          }
          char *token = strtok(line, " ");
          int col = 0; // index

          while (token != NULL) {
               sscanf(token, "%d", &slot); // convert from string to integer
               board_set(board, row, col, slot); // create the board
               token = strtok(NULL, " ");
               total = total + slot; // add the slot to the total
               col += 1;
          }
          if (total != 45){
               fprintf(stderr, "Error: Puzzle row does not add up to 45 \n");
               exit (2);
          }
          row += 1; // update row
          col = 0; // reset column
          total = 0; // reset total 
          printf("row is valid! \n");
          free(line);
     }
     check_duplicates(board);
 
}

static void check_duplicates(board_t *board)
{
     
}

int main (const int argc, char *argv[]) {
     if (argc != 2){
          fprintf(stderr, "too many arguments: please use file as parameter ./fuzz file \n");
          exit(3);
     } 
     char *filename = argv[1];
     check_puzzle(filename);
     printf("passed \n");
} 