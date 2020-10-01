CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99

.DEFAULT_GOAL := test

fsm: src/fsm.c
	$(CC) $(CFLAGS) -c -o bin/fsm.o src/fsm.c

test: fsm
	$(CC) $(CFLAGS) -o bin/test bin/fsm.o test/test.c
