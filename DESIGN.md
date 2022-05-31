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

*solver*, which will take a non-empty, non-solved sudoku puzzle and use a recursive backtracking method to solve the sudoku looping from 1 to 9.

*solver_backward*, which will take a non-empty, non-solved sudoku puzzle and use a recursive backtracking method to solve the sudoku looping from 9 to 1.

*unique_solution*, which tests if a puzzle has more than one solution.

*build_sudoku*, which reads a sudoku puzzle from stdin and converts it to the board struct.

*sudoku_solve*, which calls the functions to build/solve the sudoku and prints the resulting board if the puzzle is solvable.

*random_list*, which makes a shuffled list of numbers 1 through 9.

*remove_slots*, which removes a specified number of slots from a completed puzzle while ensuring the resulting puzzle has a unique solution.

*solver_random*, which takes a non-empty, non-solved sudoku puzzle and uses a recursive backtracking method to solve the sudoku looping through a randomized array of numbers 1 through 9.

*sudoku_create*, which is the overall sudoku creating function that generates a random puzzle given a difficulty level


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
* Fill in a puzzle by putting random numbers in each slot until the puzzle is finished or there is a slot where no number can be put
* Use backtracking if there is a slot with no possible answer
* Once the puzzle is finished, select a certain number of random slots. If removing the slot results in a puzzle with more than one possible solution, put the number back and pick a new random slot. Once enough slots have been removed, return the puzzle to the caller
* Print sudoku


### Dataflow Through Modules

Solver: sudoku_solve → build_sudoku → solver → empty_location → valid_input → board_print

The `solver` will use *sudoku_solve*, which calls on *build_sudoku* to read from stdin and create the sudoku board. *sudoku_solve*, after creating the board, will then call on *solver* to recursively input numbers and use a backtracking method to solve the puzzle. *solver* will use *empty_location* to find the next empty slot that has to be filled as well as *valid_input* to check if a particular number fits into the noted slot. Once the *solver* has successfully completed the puzzle, *board_print* will output to stdout the finished puzzle.

Creator: → valid_input → compare_solutions → print_sudoku

The `creator` will call *creator*, which will use *valid_input* to make a properly formatted and randomized Sudoku puzzle. Then, `creator` will select slots at random, remove the number held there, and call *count_solutions*. If there is more than one solution, `creator` will put the number back into the slot and try a new slot. `creator` will continue this pattern until enough slots are empty (as specified by the difficulty level). Then, *print_sudoku* will display to stdout the solutions of the puzzle.


### Major Data Structures

We anticipate the following data structures:

*board*
This struct represents the entire sudoku board. It will hold an array of 9 arrays of 9 slots each, which holds all the tiles on the sudoku board.


### Testing Plan

Unit Testing
* Test *valid_input* for cases which should return a valid input and cases which should not
* Test *count_solutions*
* Test *read_puzzle*
* Test *print_puzzle*
* Test ./sudoku create, printing out the intermediate solved puzzle and then the final puzzle with numbers taken out
* Test ./sudoku solve for a unique puzzle, printing out the input puzzle and then printing out the final puzzle


Integration Testing
* Test for command-line arguments
* Test with incorrect number of arguments
* Test with no difficulty level
* Test with invalid difficulty level
* Test ./sudoku solve with a puzzle with one solution
* Test ./sudoku solve with a puzzle with multiple solutions
* Valgrind ./sudoku create
* Valgrind ./sudoku solve 


Fuzz Testing
* Fuzz testing will use ./sudoku create and solve to create random puzzles and test ./sudoku solve's ability to solve them

