CC=${ccomp}
CFLAGS=-Wall -Wextra -pedantic -std=c99

.DEFAULT_GOAL := test

fsm: src/fsm.c
	$(CC) $(CFLAGS) -c -o bin/fsm.o src/fsm.c

fsm-debug: src/fsm.c
	$(CC) $(CFLAGS) -g -c -o bin/fsm-debug.o src/fsm.c

test: fsm
	$(CC) $(CFLAGS) -o bin/test bin/fsm.o test/test.c

debug: fsm-debug
	$(CC) $(CFLAGS) -g -o bin/debug bin/fsm-debug.o test/test.c
