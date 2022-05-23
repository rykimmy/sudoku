# Sudoku Design Spec

### Sections
1. User interface
2. Inputs and outputs

Inputs and outputs will be described according to the two major modes: ‘create’ and ‘solve’.

*Create*
The ‘creator’ will take no input aside from when calling the program to execute. It will output a newly created puzzle to stdout.

*Solve*
The ‘solver’ will take a sudoku puzzle through prompted user input through stdin. The program will then output the solved puzzle through stdout.

3. Functional decomposition into modules
4. Pseudo code
5. Dataflow through modules

Solver → read_puzzle → inserts number → valid_input → count_solutions → using compare_solution → print_solutions

The ‘solver’ will call *read_puzzle*, which reads a sudoku puzzle from stdin and converts it to a board struct. It will then iterate through the board and insert numbers, using a backtracker method to correctly input numbers into slots. The *valid_input* function will determine whether the number inserted is a guaranteed answer or a tentative answer that could be wrong. At the end, the *count_solutions* function checks how many solutions the sudoku puzzle contains and uses *compare_solutions* to differentiate between completed sudoku puzzles. *print_solutions* will display to stdout the solutions of the puzzle.

Creator → valid_input → compare_solutions → print_sudoku

The 'creator' will call *

6. Major data structures
7. Testing plan
