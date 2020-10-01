/**
 * Define a finite state machine and run it with input from stdin.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct fsm_state {
	char *name;
	int accepting;
};

struct fsm_state REJECT_STATE = {"REJECT", 0};

struct state_transition {
	char input;
	struct fsm_state *in_state;
	struct fsm_state *out_state;
};

struct fsm {
	const char* alphabet;
	struct fsm_state *initial;
	int num_transitions;
	struct state_transition *table;
};

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

struct fsm_state *eval_fsm(struct fsm *machine, const char *input, ssize_t linelen)
{
	struct fsm_state *curr_state = machine->initial;
	for (int i = 0; i < linelen; i++) {
		curr_state = step_fsm(machine, curr_state, input[i]);
	}

	return curr_state;
}

int main(void)
{
	/*
	// The example below shows the building of a FSM that accepts the language (ab)*.
	struct fsm_state s_0 = {"s_0", 1};
	struct fsm_state s_1 = {"s_1", 0};

	struct state_transition a = {'a', &s_0, &s_1};
	struct state_transition b = {'b', &s_1, &s_0};

	struct fsm ab_machine = {"ab", &s_0, 2, NULL};
	struct state_transition *table = (struct state_transition *)malloc(2 * sizeof(struct state_transition));
	table[0] = a;
	table[1] = b;
	ab_machine.table = table;
	*/

	// The example below shows the building and execution of a FSM that accepts the language a*b*.
	struct fsm_state s0 = {"s0", 1};
	struct fsm_state s1 = {"s1", 1};
	struct state_transition s02s0 = {'a', &s0, &s0};
	struct state_transition s02s1 = {'b', &s0, &s1};
	struct state_transition s12s1 = {'b', &s1, &s1};
	struct fsm ab_machine = {"ab", &s0, 3, NULL};
	struct state_transition *table = (struct state_transition *)malloc(3 * sizeof(struct state_transition));
	table[0] = s02s0;
	table[1] = s02s1;
	table[2] = s12s1;
	ab_machine.table = table;

	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;
	while ((linelen = getline(&line, &linecap, stdin)) != -1) {
		show_state(eval_fsm(&ab_machine, line, linelen - 1));
	}

	exit(EXIT_SUCCESS);
}
