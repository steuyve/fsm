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
	const char *alphabet;
	struct fsm_state *initial;
	int num_transitions;
	struct state_transition *table;
};

void show_state(struct fsm_state *);

int in_alphabet(int, const char *);

struct fsm_state *step_fsm(struct fsm *, struct fsm_state *, int);

struct fsm_state *eval_fsm(struct fsm *, const char *, ssize_t);
