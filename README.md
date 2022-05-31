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

### Compilation

To compile, simply `make`.

### Testing

The `testing.sh` program includes hard-coded test cases. These are the following test cases:
1. Test the program with various forms of incorrect command-line arguments to ensure that its command-line parsing, and validation of those parameters, works correctly.

2. Test the crawler with a seedURL that points to a non-existent server.

3. Test the crawler with a seedURL that points to a non-internal server.

4. Test the crawler with a seedURL that points to a valid server but non-existent page.

5. Crawl a simple, closed set of cross-linked web pages (letters playground). Ensure that some page(s) are mentioned multiple times within a page, and multiple times across the set of pages. Ensure there is a loop (a cycle in the graph of pages). In such a little site, you know exactly what set of pages should be crawled, at what depths, and you know where your program might trip up.

6. Point the crawler at a page in that site (letters playground), and explore at depths 0, 1, 2, 3, 4, 5. Verify that the files created match expectations.

7. Repeat with a different seed page in that same site. If the site is indeed a graph, with cycles, there should be several interesting starting points.

8. Point the crawler at our Wikipedia playground. Explore at depths 0, 1, 2. (It takes a long time to run at depth 2 or higher!) Verify that the files created match expectations.

To test, redirecting the output to testing.out, simply `make test &> testing.out`.

To test with valgrind, `make valgrind`.