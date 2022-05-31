## Sudoku Testing Specs

# testing.sh output
* Runs basic tests that show sudoku builds a correct board and then solves pre determine boards
```
f005dwj@plank:~/cs50/labs/project-dataniners$ ./testing.sh
Solving sudoku puzzle
7 1 6 4 2 5 8 3 9 
5 9 4 8 1 3 2 7 6 
2 8 3 7 6 9 4 1 5 
8 5 2 3 9 6 7 4 1 
6 4 7 1 5 8 9 2 3 
1 3 9 2 4 7 5 6 8 
4 6 8 9 3 2 1 5 7 
9 2 5 6 7 1 3 8 4 
3 7 1 5 8 4 6 9 2 
passed!
Solving sudoku puzzle
8 6 3 2 7 4 1 9 5 
5 4 7 9 1 6 2 3 8 
9 2 1 3 8 5 4 7 6 
6 7 9 4 3 2 5 8 1 
1 8 5 7 6 9 3 4 2 
4 3 2 1 5 8 7 6 9 
2 9 6 5 4 7 8 1 3 
3 5 4 8 9 1 6 2 7 
7 1 8 6 2 3 9 5 4 
passed!
Solving sudoku puzzle
2 9 5 7 4 3 8 6 1 
4 3 1 8 6 5 9 2 7 
8 7 6 1 9 2 5 4 3 
3 8 7 4 5 9 2 1 6 
6 1 2 3 8 7 4 9 5 
5 4 9 2 1 6 7 3 8 
7 6 3 5 3 4 1 8 9 
9 2 8 6 7 1 3 5 4 
1 5 4 9 3 8 6 7 2 
passed!
Solving sudoku puzzle
1 2 3 4 5 6 7 8 9 
4 5 6 7 8 9 1 2 3 
7 8 9 1 2 3 4 5 6 
2 1 4 3 6 5 8 9 7 
3 6 5 8 9 7 2 1 4 
8 9 7 2 1 4 3 6 5 
5 3 1 6 4 2 9 7 8 
6 4 2 9 7 8 5 3 1 
9 7 8 5 3 1 6 4 2 
passed!
no input
Solving sudoku puzzle
1 2 3 4 5 6 7 8 9 
4 5 6 7 8 9 1 2 3 
7 8 9 1 2 3 4 5 6 
2 1 4 3 6 5 8 9 7 
3 6 5 8 9 7 2 1 4 
8 9 7 2 1 4 3 6 5 
5 3 1 6 4 2 9 7 8 
6 4 2 9 7 8 5 3 1 
9 7 8 5 3 1 6 4 2 
passed!
./testing.sh: line 14: testBoards/null: No such file or directory
./testing.sh: line 14: testBoards/null: No such file or directory
usage: ./testing.sh ['solve','create'] ['difficulty'] \n
```
# fuzztest testing
* uses bash to do a fuzz test. essentially, creates a new random sudoku puzzle and then pipes it into solver.
d00