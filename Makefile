CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99

fsm: src/fsm.c
	$(CC) -o bin/$@ $< $(CFLAGS)

debug: src/fsm.c
	$(CC) -g -o bin/$@ $< $(CFLAGS)
