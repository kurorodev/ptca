#ifndef UTILS_MOORE_H
#define UTILS_MOORE_H

#include "../moore/moore.h"
#include <stddef.h>

void init_random(void);

void generate_random_moore_transition_table(state_t *transitions,
                                            state_t num_states,
                                            input_t num_inputs);

void generate_random_moore_output_table(output_t *outputs, state_t num_states,
                                        output_t num_outputs);

void generate_random_input_sequence(input_t *inputs, size_t length,
                                    input_t num_inputs);

void print_sequence(const char *label, const uint8_t *sequence, size_t length);

void print_moore_tables(const state_t *transitions, const output_t *outputs,
                        state_t num_states, input_t num_inputs);

#endif
