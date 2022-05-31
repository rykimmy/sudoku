#!/bin/bash
# Matthew, Ashley, Lucy, Ryan
# fuzztest.sh
# 5/30/22
#
# Fuzz test for sudoku.c


createBoard() {
     ./sudoku solve < testBoards/$1
}

###### Test Boards ######

createBoard tb1