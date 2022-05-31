# Implementation

This document describes the implementation of the 'sudoku' module.

### Pseudocode

The pseudocode for 'sudoku create' and 'sudoku solve' are described below:

1. Parse command-line arguments
    2. If first non-executable argument is "solve"
        3. Call the *solver*
    2. If first non-executable argument is "create"
        4. Set the *difficulty_level* according to the third command-line argument; if none is provided, automatically set to 'easy' mode
        5. Call the *creator*

#### Create

1. Using *board_new*, create a new sudoku board
2. Initialize the values of *empty_slots*, which is based on the *difficulty_level*, and *emptied*, which is set to 0 to mark the number of slots we have emptied.
3. Call on *solver_random* to solve the puzzle in a random fashion.
    4. If *solver_random* returns false, print error message and return false.
    5. Else if *solver_random* successfully solves the puzzle and returns true:
        6. Call *remove_slots* with the board, the number of slots to empty, and the number of empty slots, which will randomly remove the given number of slots from the puzle to make it solvable while also checking that the resulting puzzle only has one unique solution.
        7. Using *board_print*, output the generated sudoku puzzle to stdout.
        8. Delete the board using *board_delete*.

#### Solve

1. Use *build_sudoku* to read a puzzle from stdin and set up the given puzzle as a *board* struct.
2. Call on *sudoku_solve* to solve the puzzle, passing the sudoku puzzle from step 1.
    3. *sudoku_solve* calls on the *solver* to solve the puzzle using a recursive backtracking method.
    4. If the *solver* successfully solves the puzzle:
        5. Use *board_print* to print the solved puzle to stdout.
        6. Use *board_delete* to delete the puzzle
        7. Return true
    8. If the *solver* does not solve the puzzle and returns false:
        9. Print error message
        10. Use *board_delete* to delete the puzzle
        11. Return false

### Definition of detailed APIs, interfaces, function prototypes and their parameters

Below is a detailed description of our APIs for the `board` and `sudoku` modules.

#### board

*board_t *board_new()*

Creates and initializes a new sudoku 'board' struct. All slots in the grid are initially set to 0.

*void board_set(board_t *board, int row, int column, int num)*

Sets the number of a particular slot. Takes a board, the row and column of the particular slot to be set, and the number the slot will be set to.

*int board_get(board_t *board, int row, int column)*

Gets the number of a particular slot. Takes a board and the row and column of the particular slot to get. Returns the integer value of the specified slot.

*bool valid_input(board_t *board, int row, int column, int num)*

This function checks whether a number can fit into a particular slot. Given a board, the row and column of a slot, and the number to check, this function will check the number with its respective row, column, and box to see if the number fits into the slot. Returns true if the number can be placed into the noted slot, or false if it cannot.

*bool empty_location(board_t *board, int *row, int *col)*

This function iterates through each slot, beginning at the top left corner and ending at the bottom right corner. It takes a board and pointers to the row and column of each slot. Upon finding an empty slot (one that is 0), the function will return true; since the function works with pointers, the row and col values will automatically be set to the empty slot without having to return anything. The function returns false if it finds no empty slots, signalling that the puzzle is completed.

*void board_print(board_t *board)*

Given a board, this function prints to stdout the board formatted like a sudoku puzzle. Returns nothing.

*void board_delete(board_t *board)*

Given a board, this function deletes/frees the entire struct. Returns nothing.

*board_t *board_copy(board_t *original)*

Makes a copy of a given board, passed through the parameters, and returns a pointer to the copied board. The copied board will hold all the same numbers in the same slot locations.

#### sudoku

*static bool solver(board_t* sudoku)*

Takes a non-empty, non-solved sudoku board and recursively runs through each slot using a backtracking method to solve the puzzle. Inputs numbers from 1 - 9.

*static bool solver_backward(board_t* sudoku)*

Takes a non-empty, non-solved sudoku board and recursively runs through each slot using a backtracking method to solve the puzzle. Works the same as *solver* but goes backwards, starting with 9 and working down to 1 as opposed to starting with 1 and building up to 9. The specific use of this function is to test if a puzzle has multiple solutions.

*bool unique_solution(board_t *sudoku)*

Tests if a puzzle has more than one solution. Calls on other helper functions including *solver*, *solver_backward*, and *board_copy*.

*board_t *build_sudoku()*

Creates a new sudoku board and reads from stdin to initialize the board with given slot values. Returns a pointer to the sudoku board obtained through stdin.

*bool sudoku_solve(board_t* sudoku)*

Given a sudoku board to be solved, this driver function calls on other functions including *solver* to solve the puzzle and outputs the solution the stdin. Returns true if the sudoku puzzle was successfully solved; else, it returns false.

*int *random_list()*

Makes a randomized list of numbers 1 - 9. This function is used when creating a puzzle to randomize the numbers that are entered into slots as to avoid patterns when generating puzzles. Returns an array of numbers 1 - 9, shuffled in a randomized order.

*void remove_slots(board_t* board, int empty_slots, int emptied)*

Removes a specified number of slots from a completed sudoku puzzle to make it solvable. Takes the completed sudoku board, the number of slots to empty, and the number of slots already emptied. Also ensures the resulting puzzle is solvable by only one unique solution.

*static bool solver_random(board_t* sudoku)*

Takes a non-empty, non-solved sudoku board and recursively runs through each slot using a backtracking method to solve the puzzle. Tries numbers based on a randomized list in order to generate puzzles that differ every time. Allows the 'creator' to generate a random puzzle. Takes an empty sudoku board and returns true if successfully solved, false if error.

*void sudoku_create(int difficulty_level)*

Works as a driver function for 'create' as it generates a random puzzle given a difficulty level, which is provided through the parameters. The default difficulty level is 'easy' mode.

### Data structures

*board_t*, which holds a double pointer of integers representing the sudoku grid of numbers.

### Error handling and recovery

* The program will only exit with invalid command-line arguments

### Testing plan

