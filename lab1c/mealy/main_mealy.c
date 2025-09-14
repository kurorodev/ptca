#include "../utils/utils.h"
#include "mealy.h"
#include <stdio.h>

int main() {
  mealy_automaton_t mealy_automat;
  mealy_transition_t **transition_table = NULL;
  input_t input[SEQUENCE_LENGTH];

  generate_random_transition_table(&transition_table, NUM_STATES, NUM_INPUTS,
                                   NUM_OUTPUTS);

  generate_random_input_sequence(input, SEQUENCE_LENGTH, NUM_INPUTS);

  init_mealy_automat(&mealy_automat, 0,
                     (const mealy_transition_t **)transition_table, NUM_STATES,
                     NUM_INPUTS, NUM_OUTPUTS);

  __print_transition_table((const mealy_transition_t **)transition_table,
                           NUM_STATES, NUM_INPUTS);

  return 0;
}
