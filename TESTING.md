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


* In bash, have the creator produce a puzzle every second because the solver will read the puzzle before the creator has had time to write the puzzle down
- this output uses n = 5
```
f005dwj@babylon1:~/cs50/labs/project-dataniners$ ./fuzz.sh 5
------- Print Board 5 -------
Solving sudoku puzzle
3 4 7 1 8 9 2 5 6 
1 8 9 2 6 5 7 4 3 
6 5 2 4 7 3 1 9 8 
7 3 6 8 5 1 4 2 9 
8 1 5 9 4 2 3 6 7 
2 9 4 7 3 6 8 1 5 
5 2 3 6 1 8 9 7 4 
9 7 8 5 2 4 6 3 1 
4 6 1 3 9 7 5 8 2 
passed!
------- Print Board 4 -------
Solving sudoku puzzle
2 3 8 1 5 7 4 9 6 
1 7 4 9 2 6 3 5 8 
9 5 6 4 8 3 2 1 7 
5 1 2 3 6 8 9 7 4 
6 4 9 5 7 1 8 3 2 
7 8 3 2 4 9 5 6 1 
3 6 1 8 9 4 7 2 5 
4 9 5 7 1 2 6 8 3 
8 2 7 6 3 5 1 4 9 
passed!
------- Print Board 3 -------
Solving sudoku puzzle
6 9 8 7 4 3 5 2 1 
1 4 2 9 8 5 3 7 6 
3 7 5 6 1 2 8 9 4 
4 5 1 2 6 8 9 3 7 
7 8 3 1 5 9 4 6 2 
2 6 9 3 7 4 1 8 5 
9 2 4 5 3 6 7 1 8 
8 3 7 4 2 1 6 5 9 
5 1 6 8 9 7 2 4 3 
passed!
------- Print Board 2 -------
Solving sudoku puzzle
2 7 8 1 3 6 9 5 4 
9 1 5 7 2 4 3 6 8 
3 4 6 5 8 9 7 1 2 
1 8 2 9 5 3 4 7 6 
5 9 4 6 7 1 2 8 3 
6 3 7 8 4 2 1 9 5 
8 2 9 3 6 7 5 4 1 
7 5 3 4 1 8 6 2 9 
4 6 1 2 9 5 8 3 7 
passed!
------- Print Board 1 -------
Solving sudoku puzzle
4 1 7 6 8 2 3 9 5 
5 2 6 7 9 3 1 8 4 
9 8 3 5 1 4 7 6 2 
6 3 8 2 4 9 5 1 7 
2 7 4 1 5 8 6 3 9 
1 5 9 3 7 6 2 4 8 
7 9 1 8 6 5 4 2 3 
8 6 2 4 3 7 9 5 1 
3 4 5 9 2 1 8 7 6 
passed!
```

# Valgrind Testing
* valgrind.sh includes valgrind testing in bash script
```
f005dwj@babylon1:~/cs50/labs/project-dataniners$ ./valgrind.sh
-----------Memory Test-----------
==32596== Memcheck, a memory error detector
==32596== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==32596== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==32596== Command: ./sudoku solve
==32596== 
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
==32596== 
==32596== HEAP SUMMARY:
==32596==     in use at exit: 0 bytes in 0 blocks
==32596==   total heap usage: 13 allocs, 13 frees, 9,620 bytes allocated
==32596== 
==32596== All heap blocks were freed -- no leaks are possible
==32596== 
==32596== For counts of detected and suppressed errors, rerun with: -v
==32596== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==32597== Memcheck, a memory error detector
==32597== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==32597== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==32597== Command: ./sudoku solve
==32597== 
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
==32597== 
==32597== HEAP SUMMARY:
==32597==     in use at exit: 0 bytes in 0 blocks
==32597==   total heap usage: 13 allocs, 13 frees, 9,620 bytes allocated
==32597== 
==32597== All heap blocks were freed -- no leaks are possible
==32597== 
==32597== For counts of detected and suppressed errors, rerun with: -v
==32597== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==32607== Memcheck, a memory error detector
==32607== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==32607== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==32607== Command: ./sudoku solve
==32607== 
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
==32607== 
==32607== HEAP SUMMARY:
==32607==     in use at exit: 0 bytes in 0 blocks
==32607==   total heap usage: 13 allocs, 13 frees, 9,620 bytes allocated
==32607== 
==32607== All heap blocks were freed -- no leaks are possible
==32607== 
==32607== For counts of detected and suppressed errors, rerun with: -v
==32607== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
./valgrind.sh: line 18: testBoards/wrong: No such file or directory
==32619== Memcheck, a memory error detector
==32619== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==32619== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==32619== Command: ./sudoku solve
==32619== 
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
==32619== 
==32619== HEAP SUMMARY:
==32619==     in use at exit: 0 bytes in 0 blocks
==32619==   total heap usage: 13 allocs, 13 frees, 9,620 bytes allocated
==32619== 
==32619== All heap blocks were freed -- no leaks are possible
==32619== 
==32619== For counts of detected and suppressed errors, rerun with: -v
==32619== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==32629== Memcheck, a memory error detector
==32629== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==32629== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==32629== Command: ./sudoku create easy
==32629== 
Creating new sudoku puzzle
0 0 8 0 9 2 1 6 4 
0 1 0 4 0 0 3 7 9 
7 0 0 0 3 0 8 0 2 
0 0 7 0 4 3 5 0 6 
4 8 0 0 0 0 9 0 7 
1 0 0 0 7 0 4 8 3 
3 0 6 0 1 4 2 0 0 
8 5 0 0 2 0 6 0 0 
0 0 0 9 0 0 7 0 5 
==32629== 
==32629== HEAP SUMMARY:
==32629==     in use at exit: 0 bytes in 0 blocks
==32629==   total heap usage: 7,535 allocs, 7,535 frees, 272,896 bytes allocated
==32629== 
==32629== All heap blocks were freed -- no leaks are possible
==32629== 
==32629== For counts of detected and suppressed errors, rerun with: -v
==32629== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==32642== Memcheck, a memory error detector
==32642== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==32642== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==32642== Command: ./sudoku create medium
==32642== 
Creating new sudoku puzzle
0 0 0 7 0 0 4 0 0 
0 0 7 6 3 1 8 5 9 
0 0 0 0 8 0 0 3 0 
0 0 0 0 0 0 6 0 0 
0 0 0 9 1 3 0 4 7 
4 0 0 0 7 0 0 8 1 
3 0 0 0 0 7 1 6 5 
6 0 2 1 5 0 3 0 4 
1 0 5 0 0 0 0 9 8 
==32642== 
==32642== HEAP SUMMARY:
==32642==     in use at exit: 0 bytes in 0 blocks
==32642==   total heap usage: 3,572 allocs, 3,572 frees, 130,308 bytes allocated
==32642== 
==32642== All heap blocks were freed -- no leaks are possible
==32642== 
==32642== For counts of detected and suppressed errors, rerun with: -v
==32642== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==32645== Memcheck, a memory error detector
==32645== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==32645== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==32645== Command: ./sudoku create hard
==32645== 
Creating new sudoku puzzle
5 0 0 0 0 1 9 0 6 
0 0 0 0 0 0 7 4 0 
0 7 0 0 0 0 3 0 0 
0 0 1 2 0 0 0 0 3 
0 9 0 0 0 0 0 7 0 
0 0 0 1 3 7 4 5 9 
3 0 0 7 0 0 0 0 0 
1 0 0 0 4 9 0 3 2 
2 4 9 0 0 0 0 6 7 
==32645== 
==32645== HEAP SUMMARY:
==32645==     in use at exit: 0 bytes in 0 blocks
==32645==   total heap usage: 5,578 allocs, 5,578 frees, 202,620 bytes allocated
==32645== 
==32645== All heap blocks were freed -- no leaks are possible
==32645== 
==32645== For counts of detected and suppressed errors, rerun with: -v
==32645== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0) 
```

