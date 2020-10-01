/**
 * Define a finite state machine and run it with input from stdin.
 */

#define _POSIX_C_SOURCE 200809L

//#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include "fsm.h"

struct fsm_state REJECT_STATE = {"REJECT", 0};

void show_state(struct fsm_state *state)
{
	printf("Final state: %s; Accepting: %d\n", state->name, state->accepting);
}

int in_alphabet(int input, const char *alphabet)
{
	int i = 0;
	while (alphabet[i] != '\0') {
		if (input == alphabet[i]) {
			return 1;
		}
		i++;
	}
	
	return 0;
}

struct fsm_state *step_fsm(struct fsm *machine, struct fsm_state *current, int input)
{
	for (int i = 0; i < machine->num_transitions; i++) {
		if (input == machine->table[i].input && current == machine->table[i].in_state) {
			return machine->table[i].out_state;
		}
	}

	return &REJECT_STATE;
}

struct fsm_state *eval_fsm(struct fsm *machine, const char *input)
{
	struct fsm_state *curr_state = machine->initial;
	for (size_t i = 0; i < strlen(input); i++) {
		curr_state = step_fsm(machine, curr_state, input[i]);
	}

	return curr_state;
}

