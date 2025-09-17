#include "moore.h"
#include <stdio.h>
#include <stdlib.h>

void moore_init(moore_automation_t *moore, state_t initial_state,
                state_t *transition_table, output_t *output_table,
                uint8_t num_states, uint8_t num_inputs, uint8_t num_outputs) {
  if (!moore)
    return;

  moore->current_state = initial_state;
  moore->initial_state = initial_state;

  moore->transitions = transition_table;
  moore->outputs = output_table;

  moore->num_states = num_states;
  moore->num_inputs = num_inputs;
  moore->num_outputs = num_outputs;
}

void moore_reset(moore_automation_t *moore) {
  if (!moore)
    return;
  moore->current_state = moore->initial_state;
}

int moore_set_transition(moore_automation_t *moore, state_t state,
                         input_t input, state_t next_state) {
  if (!moore)
    return -1;
  if (state >= moore->num_states)
    return -1;
  if (input >= moore->num_inputs)
    return -1;
  if (next_state >= moore->num_states)
    return -1;

  size_t idx = state * moore->num_inputs + input;
  moore->transitions[idx] = next_state;
  return 0;
}

int moore_set_output(moore_automation_t *moore, state_t state,
                     output_t output) {
  if (!moore)
    return -1;
  if (state >= moore->num_states)
    return -1;
  if (output >= moore->num_outputs)
    return -1;

  moore->outputs[state] = output;
  return 0;
}

output_t moore_get_output(const moore_automation_t *moore) {
  if (!moore)
    return 0;
  return moore->outputs[moore->current_state];
}

output_t moore_process_input(moore_automation_t *moore, input_t input) {
  if (!moore)
    return 0;
  if (input >= moore->num_inputs)
    return 0;

  size_t idx = moore->current_state * moore->num_inputs + input;
  state_t next = moore->transitions[idx];

  if (next >= moore->num_states) {
    return 0;
  }

  moore->current_state = next;
  return moore->outputs[moore->current_state];
}

int moore_simulate(moore_automation_t *moore, const input_t *inputs, size_t len,
                   output_t *outputs) {
  if (!moore || !outputs)
    return -1;

  moore_reset(moore);

  outputs[0] = moore->outputs[moore->current_state];

  for (size_t i = 0; i < len; i++) {
    input_t in = inputs[i];
    if (in >= moore->num_inputs)
      return -1;

    outputs[i + 1] = moore_process_input(moore, in);
  }

  return (int)(len + 1);
}
