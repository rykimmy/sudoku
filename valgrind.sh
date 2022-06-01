#!/bin/bash
# Matthew, Ashley, Lucy, Ryan
# valgrind.sh
# 5/31/22
#
# general valgrind tests for sudoku.c

###### valgrind test ######

echo "-----------Memory Test-----------"
VALGRIND='valgrind --leak-check=full --show-leak-kinds=all'

## solve ##
# Testing with three solvable boards, one incorrect board, and an empty board
$VALGRIND ./sudoku solve < testBoards/tb1
$VALGRIND ./sudoku solve < testBoards/tb2
$VALGRIND ./sudoku solve < testBoards/tb3
$VALGRIND ./sudoku solve < testBoards/nosolution
$VALGRIND ./sudoku solve < testBoards/empty

## create ##
$VALGRIND ./sudoku create easy
$VALGRIND ./sudoku create medium
$VALGRIND ./sudoku create hard

## fuzz ##
$VALGRIND ./fuzz check testBoards/solved
$VALGRIND ./fuzz filled testBoards/unsolved testBoards/solved