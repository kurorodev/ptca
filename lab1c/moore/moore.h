#ifndef MOORE_H
#define MOORE_H

#include <stddef.h>
#include <stdint.h>

#define NUM_STATES 5
#define NUM_INPUTS 5
#define NUM_OUTPUTS 5
#define SEQUENCE_LENGTH 10

typedef uint8_t state_t;
typedef uint8_t input_t;
typedef uint8_t output_t;

typedef struct { /*Структура автомата Мура*/
  state_t current_state;
  state_t input_state;

  state_t *transitions;
  output_t *outputs;

  uint8_t num_states;
  uint8_t num_outputs;
  uint8_t num_inputs;
} moore_automation_t;

void moore_init(moore_automation_t *moore, state_t initial_state,
                state_t *transitions, output_t *output_table,
                uint8_t num_states, uint8_t num_inputs, uint8_t num_outputs);

void moore_reset(moore_automation_t *moore);

int moore_set_transition(moore_automation_t *moore, state_t state,
                         input_t input, state_t next_state);

int moore_set_output(moore_automation_t *moore, state_t state, output_t output);

output_t moore_get_output(const moore_automation_t *moore);

output_t moore_process_input(moore_automation_t *moore, input_t input);

int moore_simulate(moore_automation_t *moore, const input_t *inputs, size_t len,
                   output_t *outputs);

#endif
