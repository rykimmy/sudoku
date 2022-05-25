/* 
 * sudoku_dirver.c - A driver to execute the sudoku module.
 * 
 * Usage: ./sudoku_driver ['create', 'solve']
 * 
 * Input:
 *     command-line arguments
 *     sudoku puzzle (if using sudoku 'solve')
 * Output:
 *     'solve' -> outputs the solved sudoku puzzle
 *     'create' -> outputs a new sudoku puzzle
 * 
 * Assumptions:
 *     If calling 'solve', caller will pipe a valid sudoku puzzle instead of manually entering numbers
 *
 * DataNiners: Ashley Liang, Matthew Kim, Lucy Korte, Ryan Kim
 * CS50, 22S
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(const int argc, char *argv[]) {
    int status = 0;

    // Error checking --> number of arguments
    if (argc != 2) {
        fprintf(stderr, "Invalid number of arguments\n");
        status++;
        return status;
    }

    // Solve Mode
    if (strcmp(argv[1], "solve") == 0) {
        printf("Solving sudoku puzzle\n");
        // Run the function to solve
    }
    // Create Mode
    else if (strcmp(argv[1], "create") == 0) {
        printf("Creating new sudoku puzzle\n");
        // Run the function to create
    }
    // Error
    else {
        fprintf(stderr, "Invalid argument 1: must call 'create' or 'solve'\n");
        status++;
        return status;
    }
}