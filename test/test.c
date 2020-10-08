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

	s02s0->next = s02s1;
	s02s1->next = s12s1;
	s12s1->next = NULL;

	machine->alphabet = "ab";
	machine->initial = ps0;
	machine->final_state = ps0;
	machine->table = s02s0;
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

	s02s1->next = s12s0;
	s12s0->next = NULL;

	machine->alphabet = "ab";
	machine->initial = ps0;
	machine->final_state = ps0;
	machine->table = s02s1;
}

int main(void)
{
	struct fsm *machine = (struct fsm *)malloc(sizeof(struct fsm));
	printf("Testing empty machine on input \"\\n\" should raise NO ALPHABET FOUND error.\n");
	enum eval_codes res = eval_fsm(machine, "\n");
	if (res == 0) {
		show_state(machine->final_state);
	} else {
		convert_code(res);
	}

	printf("Making machine a*b*...\n");
	astarbstar(machine);

	printf("Testing machine a*b* on input \"\\n\" should raise NOT IN ALPHABET error.\n");
	res = eval_fsm(machine, "\n");
	if (res == 0) {
		show_state(machine->final_state);
	} else {
		convert_code(res);
	}

	printf("Testing final state for machine a*b* on input \"aaa\" should be s0 and should be accepting.\n");
	res = eval_fsm(machine, "aaa");
	if (res == 0) {
		show_state(machine->final_state);
	} else {
		convert_code(res);
	}

	printf("Testing final state for machine a*b* on input \"bbb\" should be s1 and should be accepting.\n");
	res = eval_fsm(machine, "bbb");
	if (res == 0) {
		show_state(machine->final_state);
	} else {
		convert_code(res);
	}

	printf("Testing final state for machine a*b* on input \"abb\" should be s1 and should be accepting.\n");
	res = eval_fsm(machine, "abb");
	if (res == 0) {
		show_state(machine->final_state);
	} else {
		convert_code(res);
	}

	printf("Testing machine a*b* on input \"aba\" should raise NO TRANSITION FOUND error.\n");
	res = eval_fsm(machine, "aba");
	if (res == 0) {
		show_state(machine->final_state);
	} else {
		convert_code(res);
	}

	destroy_fsm(machine);

	printf("Making machine (ab)*...\n");
	abstar(machine); 

	printf("Testing machine (ab)* on input \"\\n\" should raise NOT IN ALPHABET error.\n");
	res = eval_fsm(machine, "\n");
	if (res == 0) {
		show_state(machine->final_state);
	} else {
		convert_code(res);
	}

	printf("Testing final state for machine (ab)* on input \"abab\" should be s0 and should be accepting.\n");
	res = eval_fsm(machine, "abab");
	if (res == 0) {
		show_state(machine->final_state);
	} else {
		convert_code(res);
	}

	printf("Testing final state for machine (ab)* on input \"aba\" should be s1 and should NOT be accepting.\n");
	res = eval_fsm(machine, "aba");
	if (res == 0) {
		show_state(machine->final_state);
	} else {
		convert_code(res);
	}
	
	destroy_fsm(machine);
	free(machine);
	exit(EXIT_SUCCESS);
}
