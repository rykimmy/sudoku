#!/bin/bash
# Matthew, Ashley, Lucy, Ryan
# testing.sh
# 5/30/22
#
# general tests for sudoku.c

###### functions ######

##___ Solve Board ___##
# input: board file in testBoards
# output: completed board
solveBoard() {
     ./sudoku solve < testBoards/$1
     if [ $? -eq 0 ]
     then
          echo "passed!"
     fi
}

##___ Create Board ___##
# input: difficulty type, 'easy', 'medium', 'hard'
# output: board with one solution that is solvable
createBoard() {
     ./sudoku create $1
}

###### Test Boards ######

## Test for solver Correctness ##
echo "test for 'solve' correctness"
solveBoard tb1 # test easy board
solveBoard tb2 # test hard board
solveBoard tb3 # test almost finished board
solveBoard empty # test for solving an empty board

#solveBoard wrong # test for solving a wrong board, ###### ARE WE TESTING FOR AN INCORRECT BOARD? ######

## Test for incorrect 'solve' inputs ##
echo "test for 'solve' inputs"
solveBoard # test no input
solveBoard null # test non-existent file
solveBoard null null # test too many inputs

## Test for board creation ##
echo "test for 'create' correctness"
createBoard easy # test easy board
createBoard medium # test medium board
createBoard hard # test hard board
createBoard hard # test for duplicate difference

## Test for incorrect 'create' inputs ##
echo "test for 'create' arguments"
createBoard super hard # too many words
createBoard killer # not correct input
createBoard easy money # correct first input but too many arguments