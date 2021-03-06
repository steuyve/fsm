/**
 * Define a finite state machine and run it with input from stdin.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include "fsm.h"

struct fsm_state REJECT_STATE = {"REJECT", 0};

void show_state(struct fsm_state *state)
{
	printf("Final state: %s; Accepting: %d\n", state->name, state->accepting);
}

void convert_code(enum eval_codes code)
{
	switch (code) {
		case NORMAL:
			fprintf(stderr, "NORMAL\n");
			break;
		case NO_ALPHABET_FOUND:
			fprintf(stderr, "NO ALPHABET FOUND\n");
			break;
		case NOT_IN_ALPHABET:
			fprintf(stderr, "NOT IN ALPHABET\n");
			break;
		case NO_TRANSITION_FOUND:
			fprintf(stderr, "NO TRANSITION FOUND\n");
			break;
		default:
			fprintf(stderr, "UNRECOGNIZED CODE\n");
			break;
	}
}

int in_alphabet(char input, const char *alphabet)
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
	struct state_transition *curr_trans;
	for (curr_trans = machine->table; curr_trans != NULL; curr_trans = curr_trans->next) {
		if (input == curr_trans->input && current == curr_trans->in_state) {
			return curr_trans->out_state;
		}
	}

	return &REJECT_STATE;
}

int eval_fsm(struct fsm *machine, const char *input)
{
	if (machine->alphabet == NULL) return NO_ALPHABET_FOUND;
	struct fsm_state *curr_state = machine->initial;
	for (size_t i = 0; i < strlen(input); i++) {
		if (!in_alphabet(input[i], machine->alphabet)) return NOT_IN_ALPHABET;
		curr_state = step_fsm(machine, curr_state, input[i]);
		if (curr_state == &REJECT_STATE) return NO_TRANSITION_FOUND;
	}

	machine->final_state = curr_state;
	return NORMAL;
}

void destroy_fsm(struct fsm *machine)
{
	free(machine->initial);
	free(machine->final_state);
	struct state_transition *tmp;
	while (machine->table != NULL) {
		tmp = machine->table;
		machine->table = machine->table->next;
		free(tmp);
	}
}
