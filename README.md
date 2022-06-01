# Sudoku
## Group 9 DataNiners: Ashley Liang, Matthew Kim, Lucy Korte, Ryan Kim

The `sudoku`, composed of two modes, _create_ and _solve_, create a unique sudoku puzzle and solves a user-inputted sudoku puzzle, respectively. The `sudoku` also has various levels of difficulty that the user can adjust to their liking. 

## Usage

To use the _solve_ mode, run `./sudoku solve`. To use the _create_ mode, run `./sudoku create [easy, medium, hard]` where easy/medium/hard corresponds to the difficulty level of the sudoku created. 

## Input/Output Format

The `sudoku` program takes numbers separated by whitespace. This means that the user can format the numbers as a 9x9 square of numbers separated by numbers and new lines, or the user can just input 81 numbers separated by whitespace on one line.
The `sudoku` program will print out the sudoku as 9x9 square with 9 lines and 9 numbers on each line separated by a space. The _solve_ mode will output a full sudoku board filled with non-zero numbers and the _create_ mode will output a partialy-filled sudoku where the 0s will represent the empty slots.

### Implementation

Details of the implementation of `sudoku` can be found in IMPLEMENTATION.md

### Assumptions

The user-inputted `sudoku` only contains numbers and whitespaces. The total number of numbers inputted correspond correctly to a 9x9 sudoku board (81 numbers including the empty 0s).

### Files

* `Makefile` - compilation procedure
* `board.c` - the implementation of the board API
* `board.h` - the board API interface
* `sudoku.c` - the sudoku implementation
* `sudoku.h` - the sudoku interface
* `fuzztest.sh` - testing sudoku
* `testing.sh` - test driver
* `TESTING.md` - testing results
* `extracredit.py` - extra credit graphics in python
* `cs1lib.py` - library for extra credit graphics

### Extra Credit 

We implemented easy, medium, and hard modes for creating a puzzle.

Additionally, we created a graphical interface for the Sudoku board in Python. The python code creates a puzzle using the same algorithm we implemented in C, then displays it. Then, the user can click on a square and input a number from stdin that will be displayed on the screen. If the user presses the space bar, then clicking on squares displays the correct answer in a square.

### Compilation

To compile, simply `make`.

### Testing
* All tests redirect to [file].out

To test, simply `make test`.

To test with valgrind, `make valgrind`.

To test, run `make fuzzTest` to run a fuzz test with n = 3

Can also test individual files using fuzz.c
- use commands like `./fuzz ['filled','check'] ['file1'] ['file2']`
