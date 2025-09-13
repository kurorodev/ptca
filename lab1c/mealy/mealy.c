#include "mealy.h"

void init_mealy_automat(mealy_automaton_t *mealy_automat, state_t initial_state,
                        const mealy_transition_t **transiotion_table,
                        uint8_t num_states, uint8_t num_inputs,
                        uint8_t num_outputs) {
  if (mealy_automat == NULL || transiotion_table == NULL) {
    return;
  }

  mealy_automat->initial_state = initial_state;
  mealy_automat->transiotion_table = transiotion_table;
  mealy_automat->num_states = num_states;
  mealy_automat->num_inputs = num_inputs;
  mealy_automat->num_outputs = num_outputs;
}

output_t mealy_process_input(mealy_automaton_t *mealy_automat, input_t input) {
  if (mealy_automat == NULL)
    return (output_t)-1;

  if (input >= mealy_automat->num_inputs)
    return (output_t)-1;

  if (mealy_automat->current_state >= mealy_automat->num_states)
    return (output_t)-1;

  const mealy_transition_t *transition =
      &mealy_automat->transiotion_table[mealy_automat->current_state][input];

  if (transition == NULL)
    return (output_t)-1;

  if (transition->next_state >= mealy_automat->current_state)
    return (output_t)-1;

  if (transition->output >= mealy_automat->num_outputs)
    return (output_t)-1;

  output_t current_output = transition->output;

  mealy_automat->current_state = transition->next_state;

  return current_output;
}

void mealy_reset(mealy_automaton_t *mealy_automat) {

  if (mealy_automat == NULL)
    return;

  mealy_automat->current_state = 0;
  mealy_automat->initial_state = 0;
  mealy_automat->transiotion_table = NULL;
  mealy_automat->num_states = 0;
  mealy_automat->num_inputs = 0;
  mealy_automat->num_outputs = 0;
}

state_t get_current_state(const mealy_automaton_t *mealy_automat) {
  if (mealy_automat == NULL)
    return (state_t)-1;

  state_t current_state = mealy_automat->current_state;

  return current_state;
}

output_t mealy_final_output(const mealy_automaton_t *mealy_automat,
                            const input_t *input, size_t sequence_length) {

  if (mealy_automat == NULL || input == NULL || sequence_length == 0)
    return (output_t)-1;

  state_t current_state = mealy_automat->current_state;

  for (size_t i = 0; i < sequence_length - 1; i++) {
    if (input[i] >= mealy_automat->num_inputs)
      return (output_t)-1;

    const mealy_transition_t *transition =
        &mealy_automat->transiotion_table[current_state][input[i]];

    if (transition->next_state >= mealy_automat->num_states)
      return (output_t)-1;

    current_state = transition->next_state;
  }

  input_t last_input = input[sequence_length - 1];

  if (last_input >= mealy_automat->num_inputs)
    return (output_t)-1;

  const mealy_transition_t *final_transition =
      &mealy_automat->transiotion_table[current_state][last_input];

  if (final_transition->next_state >= mealy_automat->num_states)
    return (output_t)-1;

  return final_transition->output;
}
