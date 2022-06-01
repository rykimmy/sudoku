# Sudoku Testing Specs

# testing.sh output
* Runs basic tests that show sudoku builds a correct board and then solves pre determine boards
## Tests for...
1. Valid inputs for create and solve
2. Correct solver output
3. Correct create output
- for create output, tests both easy, medium, and hard
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
* uses bash to do a fuzz test that creates a new random sudoku puzzle and then pipes it into solver.
* uses a C module 'fuzz' to compare the 'create' sudoku puzzle and the 'solver' sudoku puzzle to see if the solver changed any given numbers from 'create'. In addition, this module parses through each sudoku puzzle to validate it. The types of validation are mentioned below
1. sum of each row and column is equal to 45
2. sum of each subsquare is equal to 45
3. each row and column do not have duplicate numbers
4. each subsquare does not have duplicate numbers

## Assumptions
* sudoku.c already has a function to test for unique solutions for each board it creates, so we do not need to test for unique solutions.
* Inputed sudoku boards to the fuzz testing modules are already formatted properly through sudoku.c

* Below is the bash output. The creator produces a puzzle every second.
- this output uses n = 3
```
f005dwj@babylon1:~/cs50/labs/project-dataniners$ ./fuzz.sh 3
------- Print Board 3 -------
---create---
8 1 3 6 7 2 5 9 4 
0 0 0 0 1 0 0 0 0 
0 6 2 9 0 3 7 8 0 
0 4 9 0 8 0 0 2 0 
0 2 0 7 0 0 8 0 6 
6 8 7 0 2 0 9 4 0 
9 0 0 1 3 0 0 0 2 
0 0 0 0 9 7 6 5 8 
0 7 0 0 0 0 0 1 0 
---solved---
8 1 3 6 7 2 5 9 4 
7 9 5 8 1 4 2 6 3 
4 6 2 9 5 3 7 8 1 
3 4 9 5 8 6 1 2 7 
5 2 1 7 4 9 8 3 6 
6 8 7 3 2 1 9 4 5 
9 5 6 1 3 8 4 7 2 
1 3 4 2 9 7 6 5 8 
2 7 8 4 6 5 3 1 9 
---fuzzTest---
Solver has no duplicate or sum errors!! 
passed 
Solver -successfully- filled in the correct slots! 
passed 
------- Print Board 2 -------
---create---
1 0 0 0 9 0 2 0 4 
0 0 0 7 0 4 0 0 0 
0 4 3 2 0 0 0 6 9 
0 0 0 5 6 0 0 4 8 
0 5 0 0 8 1 6 0 0 
0 0 0 0 3 0 0 0 0 
0 0 0 0 0 0 7 0 0 
4 0 0 0 2 9 3 8 5 
5 0 0 0 7 0 0 2 1 
---solved---
1 8 5 3 9 6 2 7 4 
6 2 9 7 1 4 8 5 3 
7 4 3 2 5 8 1 6 9 
2 3 1 5 6 7 9 4 8 
9 5 7 4 8 1 6 3 2 
8 6 4 9 3 2 5 1 7 
3 1 2 8 4 5 7 9 6 
4 7 6 1 2 9 3 8 5 
5 9 8 6 7 3 4 2 1 
---fuzzTest---
Solver has no duplicate or sum errors!! 
passed 
Solver -successfully- filled in the correct slots! 
passed 
------- Print Board 1 -------
---create---
0 0 4 0 5 0 9 2 0 
5 0 0 2 0 0 0 6 4 
0 8 0 0 0 6 0 0 3 
0 0 1 6 0 0 4 5 8 
0 9 0 4 0 2 0 1 0 
0 6 0 1 8 0 0 0 9 
2 4 0 5 0 3 7 0 6 
0 1 0 0 0 0 3 0 0 
9 0 0 7 6 0 0 8 0 
---solved---
6 7 4 3 5 8 9 2 1 
5 3 9 2 7 1 8 6 4 
1 8 2 9 4 6 5 7 3 
3 2 1 6 9 7 4 5 8 
8 9 5 4 3 2 6 1 7 
4 6 7 1 8 5 2 3 9 
2 4 8 5 1 3 7 9 6 
7 1 6 8 2 9 3 4 5 
9 5 3 7 6 4 1 8 2 
---fuzzTest---
Solver has no duplicate or sum errors!! 
passed 
Solver -successfully- filled in the correct slots! 
passed
```

# Valgrind Testing
* valgrind.sh includes valgrind testing in bash script
- Tests for memory leaks when using sudoku.c commands 'create' and 'solve'
- Tests for memory leaks in fuzz.c
```
f005dwj@babylon1:~/cs50/labs/project-dataniners$ ./valgrind.sh
-----------Memory Test-----------
==49987== Memcheck, a memory error detector
==49987== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==49987== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==49987== Command: ./sudoku solve
==49987== 
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
==49987== 
==49987== HEAP SUMMARY:
==49987==     in use at exit: 0 bytes in 0 blocks
==49987==   total heap usage: 13 allocs, 13 frees, 9,620 bytes allocated
==49987== 
==49987== All heap blocks were freed -- no leaks are possible
==49987== 
==49987== For counts of detected and suppressed errors, rerun with: -v
==49987== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==49988== Memcheck, a memory error detector
==49988== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==49988== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==49988== Command: ./sudoku solve
==49988== 
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
==49988== 
==49988== HEAP SUMMARY:
==49988==     in use at exit: 0 bytes in 0 blocks
==49988==   total heap usage: 13 allocs, 13 frees, 9,620 bytes allocated
==49988== 
==49988== All heap blocks were freed -- no leaks are possible
==49988== 
==49988== For counts of detected and suppressed errors, rerun with: -v
==49988== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==50150== Memcheck, a memory error detector
==50150== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==50150== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==50150== Command: ./sudoku solve
==50150== 
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
==50150== 
==50150== HEAP SUMMARY:
==50150==     in use at exit: 0 bytes in 0 blocks
==50150==   total heap usage: 13 allocs, 13 frees, 9,620 bytes allocated
==50150== 
==50150== All heap blocks were freed -- no leaks are possible
==50150== 
==50150== For counts of detected and suppressed errors, rerun with: -v
==50150== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==50178== Memcheck, a memory error detector
==50178== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==50178== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==50178== Command: ./sudoku solve
==50178== 
Solving sudoku puzzle
sudoku not solvable
==50178== 
==50178== HEAP SUMMARY:
==50178==     in use at exit: 0 bytes in 0 blocks
==50178==   total heap usage: 13 allocs, 13 frees, 9,620 bytes allocated
==50178== 
==50178== All heap blocks were freed -- no leaks are possible
==50178== 
==50178== For counts of detected and suppressed errors, rerun with: -v
==50178== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==50179== Memcheck, a memory error detector
==50179== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==50179== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==50179== Command: ./sudoku solve
==50179== 
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
==50179== 
==50179== HEAP SUMMARY:
==50179==     in use at exit: 0 bytes in 0 blocks
==50179==   total heap usage: 13 allocs, 13 frees, 9,620 bytes allocated
==50179== 
==50179== All heap blocks were freed -- no leaks are possible
==50179== 
==50179== For counts of detected and suppressed errors, rerun with: -v
==50179== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==50180== Memcheck, a memory error detector
==50180== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==50180== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==50180== Command: ./sudoku create easy
==50180== 
Creating new sudoku puzzle
3 0 0 8 4 1 0 0 0 
4 5 0 0 0 0 6 0 3 
0 0 0 0 5 3 8 7 4 
0 3 4 1 0 7 0 0 0 
1 0 7 2 8 4 0 0 6 
0 0 0 0 9 0 0 4 0 
0 0 0 9 7 0 3 6 0 
0 1 0 0 3 6 4 0 8 
0 6 3 4 1 8 7 9 0 
==50180== 
==50180== HEAP SUMMARY:
==50180==     in use at exit: 0 bytes in 0 blocks
==50180==   total heap usage: 8,116 allocs, 8,116 frees, 293,812 bytes allocated
==50180== 
==50180== All heap blocks were freed -- no leaks are possible
==50180== 
==50180== For counts of detected and suppressed errors, rerun with: -v
==50180== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==50194== Memcheck, a memory error detector
==50194== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==50194== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==50194== Command: ./sudoku create medium
==50194== 
Creating new sudoku puzzle
0 6 0 0 0 0 0 2 0 
5 3 0 8 0 0 0 7 1 
9 0 0 0 0 5 0 0 8 
1 0 6 5 3 0 7 9 0 
3 0 0 2 7 8 0 1 0 
2 0 0 0 0 0 0 0 3 
0 0 7 6 0 0 0 0 0 
0 1 2 0 5 7 3 0 4 
6 9 0 0 0 2 1 5 0 
==50194== 
==50194== HEAP SUMMARY:
==50194==     in use at exit: 0 bytes in 0 blocks
==50194==   total heap usage: 4,385 allocs, 4,385 frees, 159,576 bytes allocated
==50194== 
==50194== All heap blocks were freed -- no leaks are possible
==50194== 
==50194== For counts of detected and suppressed errors, rerun with: -v
==50194== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==50195== Memcheck, a memory error detector
==50195== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==50195== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==50195== Command: ./sudoku create hard
==50195== 
Creating new sudoku puzzle
0 0 0 0 0 0 5 0 9 
0 0 0 0 0 5 2 0 0 
4 2 5 0 0 0 3 0 7 
0 0 0 6 2 3 0 7 0 
0 0 0 0 1 0 9 5 0 
1 0 7 0 0 8 6 0 0 
0 6 4 8 0 0 0 0 3 
8 0 3 0 7 6 4 0 0 
0 0 0 4 3 0 0 0 0 
==50195== 
==50195== HEAP SUMMARY:
==50195==     in use at exit: 0 bytes in 0 blocks
==50195==   total heap usage: 9,707 allocs, 9,707 frees, 351,264 bytes allocated
==50195== 
==50195== All heap blocks were freed -- no leaks are possible
==50195== 
==50195== For counts of detected and suppressed errors, rerun with: -v
==50195== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==50211== Memcheck, a memory error detector
==50211== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==50211== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==50211== Command: ./fuzz check testBoards/solved
==50211== 
Solver has no duplicate or sum errors!! 
passed 
==50211== 
==50211== HEAP SUMMARY:
==50211==     in use at exit: 0 bytes in 0 blocks
==50211==   total heap usage: 114 allocs, 114 frees, 12,350 bytes allocated
==50211== 
==50211== All heap blocks were freed -- no leaks are possible
==50211== 
==50211== For counts of detected and suppressed errors, rerun with: -v
==50211== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==50213== Memcheck, a memory error detector
==50213== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==50213== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==50213== Command: ./fuzz filled testBoards/unsolved testBoards/solved
==50213== 
Solver -successfully- filled in the correct slots! 
passed 
==50213== 
==50213== HEAP SUMMARY:
==50213==     in use at exit: 0 bytes in 0 blocks
==50213==   total heap usage: 47 allocs, 47 frees, 20,940 bytes allocated
==50213== 
==50213== All heap blocks were freed -- no leaks are possible
==50213== 
==50213== For counts of detected and suppressed errors, rerun with: -v
==50213== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

