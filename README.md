# About

A small library written in C for implementing and running finite state machines.

The main header file to include if you want to use it is `fsm.h`. 

# Installation

Clone this repository with

```
git clone https://github.com/steuyve/fsm.git
cd fsm
```

Then run `make` or `make test` (they point to the same goal) to run tests.

# API and Usage

The main struct provided is the `fsm` struct. Internally it looks like this:

```
struct fsm {
    const char *alphabet
    struct fsm_state *initial;
    struct fsm_state *final_state;
    struct state_transition *table;
};
```

where `alphabet` points to the machine's input alphabet (input is assumed to be one character long at a time), `initial` is the machine's initial state, `final_state` is the machine's final state, and `table` points to a linked list of state transitions that determine what input state transitions to what output state under what input. See the `src/fsm.h` file to see more.

Once you specify a `fsm` machine. Call `eval_fsm()` to run it with a string input. If successful, `eval_fsm()` will return zero and you can show the machine's final state with a call to `show_state()`. Nonzero values returned by `eval_fsm()` are errors and can be decoded to a string with `convert_code()`.
