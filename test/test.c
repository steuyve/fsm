#include <stdlib.h>
#include <stdio.h>
#include "../src/fsm.h"

void astarbstar(struct fsm *machine)
{
	// The example below shows the building and execution of a FSM that accepts the language a*b*.
	struct fsm_state *ps0 = (struct fsm_state *)malloc(sizeof(struct fsm_state));
	ps0->name = "s0";
	ps0->accepting = 1;
	struct fsm_state *ps1 = (struct fsm_state *)malloc(sizeof(struct fsm_state));
	ps1->name = "s1";
	ps1->accepting = 1;

	struct state_transition *s02s0 = (struct state_transition *)malloc(sizeof(struct state_transition));
	s02s0->input = 'a';
	s02s0->in_state = ps0;
	s02s0->out_state = ps0;

	struct state_transition *s02s1 = (struct state_transition *)malloc(sizeof(struct state_transition));
	s02s1->input = 'b';
	s02s1->in_state = ps0;
	s02s1->out_state = ps1;

	struct state_transition *s12s1 = (struct state_transition *)malloc(sizeof(struct state_transition));
	s12s1->input = 'b';
	s12s1->in_state = ps1;
	s12s1->out_state = ps1;

	struct state_transition *table = (struct state_transition *)malloc(3 * sizeof(struct state_transition));
	table[0] = *s02s0;
	table[1] = *s02s1;
	table[2] = *s12s1;

	machine->alphabet = "ab";
	machine->initial = ps0;
	machine->num_transitions = 3;
	machine->table = table;
}

void abstar(struct fsm *machine)
{
	// The example below shows the building of a FSM that accepts the language (ab)*.
	struct fsm_state *ps0 = (struct fsm_state *)malloc(sizeof(struct fsm_state));
	ps0->name = "s0";
	ps0->accepting = 1;
	struct fsm_state *ps1 = (struct fsm_state *)malloc(sizeof(struct fsm_state));
	ps1->name = "s1";
	ps1->accepting = 0;

	struct state_transition *s02s1 = (struct state_transition *)malloc(sizeof(struct state_transition));
	s02s1->input = 'a';
	s02s1->in_state = ps0;
	s02s1->out_state = ps1;

	struct state_transition *s12s0 = (struct state_transition *)malloc(sizeof(struct state_transition));
	s12s0->input = 'b';
	s12s0->in_state = ps1;
	s12s0->out_state = ps0;

	struct state_transition *table = (struct state_transition *)malloc(2 * sizeof(struct state_transition));
	table[0] = *s02s1;
	table[1] = *s12s0;

	machine->alphabet = "ab";
	machine->initial = ps0;
	machine->num_transitions = 2;
	machine->table = table;
}

int main(void)
{
	struct fsm *machine = (struct fsm *)malloc(sizeof(struct fsm));
	printf("Testing final state for empty machine on input \"\\n\" should be REJECT and should NOT be accepting.\n");
	show_state(eval_fsm(machine, "\n"));

	printf("Making machine a*b*...\n");
	astarbstar(machine);
	printf("Testing final state for machine a*b* on input \"\\n\" should be REJECT and should NOT be accepting.\n");
	show_state(eval_fsm(machine, "\n"));
	printf("Testing final state for machine a*b* on input \"aaa\" should be s0 and should be accepting.\n");
	show_state(eval_fsm(machine, "aaa"));
	printf("Testing final state for machine a*b* on input \"bbb\" should be s1 and should be accepting.\n");
	show_state(eval_fsm(machine, "bbb"));
	printf("Testing final state for machine a*b* on input \"abb\" should be s1 and should be accepting.\n");
	show_state(eval_fsm(machine, "abb"));
	printf("Testing final state for machine a*b* on input \"aba\" should be REJECT and should NOT be accepting.\n");
	show_state(eval_fsm(machine, "aba"));

	printf("Making machine (ab)*...\n");
	abstar(machine); 
	printf("Testing final state for machine (ab)* on input \"\\n\" should be REJECT and should NOT be accepting.\n");
	show_state(eval_fsm(machine, "\n"));
	printf("Testing final state for machine (ab)* on input \"abab\" should be s0 and should be accepting.\n");
	show_state(eval_fsm(machine, "abab"));
	printf("Testing final state for machine (ab)* on input \"aba\" should be s1 and should NOT be accepting.\n");
	show_state(eval_fsm(machine, "aba"));

	/*
	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;
	while ((linelen = getline(&line, &linecap, stdin)) != -1) {
		show_state(eval_fsm(&ab_machine, line, linelen - 1));
	}

	free(line);
	*/

	exit(EXIT_SUCCESS);
}
