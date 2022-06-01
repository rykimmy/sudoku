#!/bin/bash
# Matthew, Ashley, Lucy, Ryan
# fuzztest.sh
# 5/30/22
#
# Fuzz test for sudoku.c

########## INPUT ##########
# if more than 1 argument, then exit
if [ $# -gt 1 ]
then 
     echo "[fuzz.sh] too many arugments. Please type 'n' number of boards you would like to test"
     exit
else 
     num=$1 # set argument to number
fi

###### SETUP TEST FILES #####
# creating files for board to write
sB=testBoards/solvedBoard.txt # solved board
cB=testBoards/createdBoard.txt # created board, used to verify that the solver didn't change any numbers
rm -f $sB
rm -f $cB
touch $sB
touch $cB
chmod o+r $cB # give permission to access
chmod o+r $sB

######  FUNCTIONS  ######

##___ Solve Board ___##
# input: board file in testBoards directory
# output: completed board
solveBoard() {
     ./sudoku solve < $1
     if [ $? -eq 0 ]
     then
          echo "passed!"
     fi
}

##___ Create Board ___##
# input: one word with difficulty type, 'easy', 'medium', 'hard'
# output: board with one solution that is solvable
createBoard() {
     ./sudoku create $1
}

##___ Fuzz Test Board ___##
# input: board difficulty
# output: completed board that was created by board solve
testBoard() {
     createBoard $1 >> $cB # pipe output to file
     sed -i '1d' ./$cB # Do this because it auto prints 'creating new sudoku puzzle'. Will therefore delete first line
     solveBoard $cB  >> $sB # read from the file
     sed -i '1d' ./$sB
     sed -i '10d' ./$sB # Solved board also prints 'Passed' at the bottom so we need to delete
     echo "---create---"
     cat $cB
     echo "---solved---"
     cat $sB
     echo "---fuzzTest---"
     ./fuzz check $sB
     ./fuzz filled $cB $sB
}

###### Test Boards ######

while [ $num -ge 1 ]
do
     echo "------- Print Board $num -------"
     # rand=$(( $RANDOM % 3 + 1 )) # random number to decide if board is easy, medium, or hard
     if [ $(($num % 3)) -eq 0 ]
     then
          testBoard easy
     elif [ $(($num % 3)) -eq 1 ]
     then
          testBoard medium
     else
          testBoard hard
     fi
     num=$(( $num - 1 ))
     rm -f $cB
     rm -f $sB
     sleep 1 # waits half a second
done