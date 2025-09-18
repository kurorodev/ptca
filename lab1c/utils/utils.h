#ifndef UTILS_H
#define UTILS_H
#include "../mealy/mealy.h"
#include <stdint.h>
#include <stdlib.h>

void init_random();

void print_sequence(const uint8_t *sequence, size_t length, const char *prefix);

void generate_random_mealy_transition_table(mealy_transition_t ***table,
                                            state_t num_states,
                                            input_t num_inputs,
                                            output_t num_outputs);

void free_mealy_transition_table(mealy_transition_t ***table,
                                 state_t num_states);

void generate_random_input_sequence(input_t *input, size_t length,
                                    input_t num_inputs);

void generate_mealy_transition_table(const mealy_transition_t **table,
                                     state_t num_states, input_t num_inputs);

void __print_mealy_transition_table(const mealy_transition_t **table,
                                    state_t num_states, input_t num_inputs);
#endif
