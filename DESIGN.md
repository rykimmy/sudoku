# Sudoku Design Spec

### Sections
1. User interface
2. Inputs and outputs
3. Functional decomposition into modules
4. Pseudo code
5. Dataflow through modules
6. Major data structures
7. Testing plan


### User Interface

./sudoku create [easy, medium, hard] or ./sudoku solve

We anticipate the following user interface:

The user will interact with the sudoku module when calling the program to execute with `./sudoku`. The program takes 1-2 arguments (_create_ takes 2 arguments and _solve_ takes 1).
```
./sudoku mode difficulty_level
```
where *mode* is either “create” or “solve” that dictates how the program will run.  The argument `create` will prompt the program to build a new sudoku puzzle while the argument `solve` will instruct the program to solve a sudoku puzzle that the user is required to provide through stdin.
*difficulty_level* is an argument for the _create_ mode that takes "easy", "medium", or "hard" and creates a puzzle according to that difficulty.

For example:
```
./sudoku create hard
```


### Inputs and Outputs

Inputs and outputs will be described according to the two major modes: _create_ and _solve_.

*Create*
The _creator_ will take the difficulty level written as "easy" "medium" or "hard" as a command-line argument. It will output a newly created puzzle to stdout.

*Solve*
The _solver_ will take a sudoku puzzle through prompted user input through stdin. The program will then output the solved puzzle through stdout.


### Functional Decomposition Into Modules

We anticipate the following modules and/or functions:

**Sudoku**

*sudoku_solve*, which is the overall solver function that calls the functions to build/solve the sudoku and prints the resulting board if the puzzle is solvable.

*sudoku_create*, which is the overall sudoku creating function that generates a random puzzle given a difficulty level

*build_sudoku*, which reads a sudoku puzzle from stdin and converts it to the board struct.

*solver*, which will take a non-empty, non-solved sudoku puzzle and use a recursive backtracking method to solve the sudoku looping from 1 to 9.

*solver_backward*, which will take a non-empty, non-solved sudoku puzzle and use a recursive backtracking method to solve the sudoku looping from 9 to 1.

*unique_solution*, which tests if a puzzle has more than one solution.

*random_list*, which makes a list 1 through 9, but shuffled.

*remove_slots*, which removes a specified number of slots from a completed puzzle while ensuring the resulting puzzle has a unique solution.

*solver_random*, which takes a non-empty, non-solved sudoku puzzle and uses a recursive backtracking method to solve the sudoku looping through a randomized array of numbers 1 through 9.


**Board**

*board_new*, which initializes a new board struct to hold a sudoku puzzle.

*board_set*, which sets a specificed slot to a given number.

*board_get*, which gets the number at a specified slot.

*valid_input*, which checks if the most recently inserted number works is valid (unique number 1-9 horizontally, vertically, and per block).

*empty_location*, which loops through the board––from the top left to the bottom right––and returns true when it finds an empty slot. It also adjusts the given *row* and *col* variables such that they will hold the corresponding values of the empty slot.

*board_print*, which prints the final board struct to stdout.

*board_delete*, which deletes the board struct

*board_copy*, which creates a copy of the board


### Pseudo Code

* Parse arguments
   * Ensure 1-2 arguments: first argument is "create" or "solve". If the first argument is "create", the second argument is "easy", "medium", or "hard". If the arguments aren't valid, exit the program non-zero. Otherwise, call *sudoku_create* or *sudoku_solve* accordingly

* Sudoku_solve:
* Read from stdin to build partially-filled sudoku puzzle
* Recurse through every empty slot:
    * Starting from one and going until 9:
        * Check if the number is valid for the current puzzle (unique in row, col, sub-box)
        * If it valid, insert that number, continue to the next non-given slot and repeat
        * If it doesn't fit, increment the number being checked/possibly inserted
    * If none of the numbers work, reset the number to 0, return false which will backtrack to previous non-given slot and continue where left off.
* Once the sudoku finishes solving, print out the final board. If the sudoku is unsolvable, print "sudoku not solvable"

* sudoku_create:
* create an empty board
* create variables for the difficulty-level
* 'solve' an empty sudoku board by putting random numbers in each slot until the puzzle is finished or there is a slot where no number can be put
    * Use the sudoku solver process but with a list of shuffled numbers between 1 and 9 rather than trying numbers 1 to 9.
* once the puzzle is finished/complete, remove a certain number of slots corresponding to the difficulty level
    * set the slot to 0 and check if the board still has a unique solution. if it does, keep the slot empty, if not, put the original number back
* print sudoku
* delete the board


### Dataflow Through Modules

main → sudoku_solve or sudoku_create

Solver: sudoku_solve → build_sudoku (calls board_new and board_set) → recursively (solver → empty_location → valid_input → board_set → solver) → board_print → board_delete

The `solver` will use *sudoku_solve*, which calls on *build_sudoku* to read from stdin and create the sudoku board, calling *board_new* to initialize the board and *board_set* to set the slots to the numbers given from stdin. *build_sudoku* returns a board to *sudoku_solve*. *sudoku_solve* will then call *solver* on the board, which recursively checks for an empty location using *empty_location* on the board and input numbers (checking with *valid_input* before *board_set*). Once the *solver* has successfully completed the puzzle, *board_print* will output the finished puzzle to stdout.

Creator: board_new → recursively (solver_random → empty_location → random_list → valid_input → board_set → solver_random) → remove_slots (calls board_get, board_set, and unique_solution(calls board_copy, solver, solver_backward, board_get, and board_delete)) → board_print → board_delete

The `creator` will call *sudoku_create*, which first creates an empty board with *board_new*. It then randomly solves the empty board using *solver_random*. *solver_random* recursively calls *empty_location* to find the location of empty slots, *random_list* to generate a shuffled list of numbers 1-9, *valid_input* to check if the current number the program is trying in the shuffled list fulfills the sudoku requirements, and *board_set* to set that number in the board. Once the board is solved, *sudoku_create* calls *remove_slots*. *remove_slot* calls *board_get* to get the number in a random slot and *board_set* to set the slot to 0. It then checks if that puzzle has a unique solution by calling *unique_solution*. *unique_solution* creates two copies of the board with *board_copy*, solving one with *solver* and the other with *solver_backward*. If the solutions are not the same, *unique_solution* returns false and *remove_slots* sets the slot back to the original number. Finally, *sudoku_create* calls *board_print* and *board_delete* to print and delete the board.


### Major Data Structures

We anticipate the following data structures:

*board*
This struct represents the entire sudoku board. It will hold an array of 9 arrays of 9 slots (int data type) each, which holds all the tiles on the sudoku board.


### Testing Plan

Integration Testing
* Test for command-line arguments
* Test with incorrect number of arguments
* Test solve with easy board
* Test solve with difficult board
* Test solve on empty board
* Test solve for an unsolvable board
* Test create easy board
* Test create medium board
* Test create hard board
* Valgrind ./sudoku create
* Valgrind ./sudoku solve 


Fuzz Testing
* Fuzz testing will use ./sudoku create and solve to create random puzzles and test ./sudoku solve's ability to solve them
* The Fuzz test will also test the validity of each sudoku puzzle created

