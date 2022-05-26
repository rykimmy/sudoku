# Makefile for indexer
#
# Ashley Liang, CS50 Spring 2022


#edit for the right programs
PROG = board sudoku sudoku_driver
OBJS = board.o sudoku.o sudoku_driver.o
LIBS = libcs50/libcs50.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50
CC = gcc
VFLAGS = --leak-check=full --show-leak-kinds=all
MAKE = make

board: board.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@ 

sudoku: sudoku.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@ 

sudoku_driver: sudoku_driver.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@ 

.PHONY: all test valgrind clean

all: $(PROG)

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)
	