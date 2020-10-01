CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99

libfsm: src/libfsm.c
	$(CC) -o bin/$@ $< $(CFLAGS)

debug: src/libfsm.c
	$(CC) -g -o bin/$@ $< $(CFLAGS)
