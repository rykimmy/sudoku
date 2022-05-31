# Makefile for indexer
#
# Ashley Liang, CS50 Spring 2022


#edit for the right programs
PROG = sudoku 
OBJS = board.o sudoku.o 
LIBS = libcs50/libcs50-given.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -Ilibcs50
CC = gcc
VFLAGS = --leak-check=full --show-leak-kinds=all
MAKE = make

all: $(PROG)

# board: board.o $(LIBS)
# 	$(CC) $(CFLAGS) $^ -o $@ 

sudoku: sudoku.o board.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@ 

test: sudoku
	./testing.sh &> testing.out

.PHONY: all test valgrind clean

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)
	