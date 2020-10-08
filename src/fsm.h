#ifndef FSM_H
#define FSM_H

enum eval_codes {
	NORMAL,
	NO_ALPHABET_FOUND,
	NOT_IN_ALPHABET,
	NO_TRANSITION_FOUND
};

struct fsm_state {
	char *name;
	int accepting;
};

extern struct fsm_state REJECT_STATE;

struct state_transition {
	char input;
	struct fsm_state *in_state;
	struct fsm_state *out_state;
	struct state_transition *next;
};

struct fsm {
	const char *alphabet;
	struct fsm_state *initial;
	struct fsm_state *final_state;
	struct state_transition *table;
};

void show_state(struct fsm_state *);

void convert_code(enum eval_codes);

int in_alphabet(char, const char *);

struct fsm_state *step_fsm(struct fsm *, struct fsm_state *, int);

int eval_fsm(struct fsm *, const char *);

void destroy_fsm(struct fsm *);

#endif
