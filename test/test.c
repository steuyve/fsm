#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include "../src/fsm.h"

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

	free(line);

	exit(EXIT_SUCCESS);
}
