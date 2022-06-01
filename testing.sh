#!/bin/bash
# Matthew, Ashley, Lucy, Ryan
# testing.sh
# 5/30/22
#
# general tests for sudoku.c

###### functions ######

##___ Solve Board ___##
# input: board file in testBoards directory
# output: completed board
solveBoard() {
     ./sudoku solve < testBoards/$1
     if [ $? -eq 0 ]
     then
          echo "passed!"
     fi
}

##___ Create Board ___##
# input: one word with difficulty type, 'easy', 'medium', 'hard'
# output: board with one solution that is solvable
createBoard() {
     if [ $# -ge 2 ]
     then 
          echo "too many arguments"
     else
          ./sudoku create $1
     fi
}

###### Test Boards ######

## Test incorrect number of arguments
echo "wrong number of arguments"
./sudoku

## Test for solver Correctness ##
echo "-----------Test Solve-----------"
solveBoard tb1 # test easy board
solveBoard tb2 # test hard board
solveBoard tb3 # test almost finished board
solveBoard empty # test for solving an empty board
solveBoard no solution # test for a board with no solution

## Test for incorrect 'solve' inputs ##
echo "----------Test Solve Inputs-----------"
solveBoard # test no input
solveBoard null # test non-existent file
solveBoard null null # test too many inputs

## Test for board creation ##
echo "----------Test Create-----------"
createBoard easy # test easy board
createBoard medium # test medium board
createBoard hard # test hard board
# createBoard hard # test for duplicate difference

## Test for incorrect 'create' inputs ##
echo "----------Test Create Inputs-----------"
createBoard # no difficuty
createBoard super hard # too many words
createBoard killer # not correct input
createBoard easy money # correct first input but too many arguments