#ifndef FSM_H
#define FSM_H

struct fsm_state {
	char *name;
	int accepting;
};

extern struct fsm_state REJECT_STATE;

struct state_transition {
	char input;
	struct fsm_state *in_state;
	struct fsm_state *out_state;
};

struct fsm {
	const char *alphabet;
	struct fsm_state *initial;
	struct fsm_state *final_state;
	int num_transitions;
	struct state_transition *table;
};

void show_state(struct fsm_state *);

int in_alphabet(int, const char *);

struct fsm_state *step_fsm(struct fsm *, struct fsm_state *, int);

int eval_fsm(struct fsm *, const char *);

#endif
