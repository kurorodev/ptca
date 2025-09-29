#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lab1c/mealy/mealy.h"
#include "../lab1c/moore/moore.h"
#include "../lab1c/utils/utils_mealy.h"
#include "../lab1c/utils/utils_moore.h"

int convert_mealy_to_moore(const mealy_automaton_t *mealy,
                           moore_automation_t *moore) {

  if (mealy == NULL || moore == NULL) {
    puts("ERROR MEALY OR MOORE EQUAL NULL");
    return -1;
  }

  uint8_t moore_states = mealy->num_states * mealy->num_outputs;

  state_t *transitions =
      malloc(moore_states * mealy->num_inputs * sizeof(state_t));
  output_t *output = malloc(moore_states * sizeof(output_t));

  if (transitions == NULL || output == NULL) {
    puts("ERROR ALLOCATE MEMORY FOR TRANSITIONS OR OUTPUT");
    free(transitions);
    free(output);
    return -1;
  }

  for (state_t i = 0; i < moore_states; i++) {
    output[i] = 0;
  }

  for (state_t mealy_state = 0; mealy_state < mealy->num_states;
       mealy_state++) {
    for (output_t output_val = 0; output_val < mealy->num_outputs;
         output_val++) {
      state_t moore_state = mealy_state * mealy->num_outputs + output_val;

      output[moore_state] = output_val;

      for (input_t input = 0; input < mealy->num_inputs; input++) {
        const mealy_transition_t *trans =
            &mealy->transition_table[mealy_state][input];

        if (trans->next_state >= mealy->num_states ||
            trans->output >= mealy->num_outputs) {
          printf("Ошибка: некорректный переход state=%d, input=%d\n",
                 mealy_state, input);
          free(transitions);
          free(output);
          return -1;
        }
        state_t next_moore_state =
            trans->next_state * mealy->num_outputs + trans->output;
        transitions[moore_state * mealy->num_inputs + input] = next_moore_state;
      }
    }
  }

  state_t init_moore_state = mealy->initial_state * mealy->num_outputs;

  moore_init(moore, init_moore_state, transitions, output, moore_states,
             mealy->num_inputs, mealy->num_outputs);

  return 0;
}

int main() {
  init_mealy_random();

  mealy_automaton_t mealy;
  mealy_transition_t **transition_table;

  generate_random_mealy_transition_table(&transition_table, NUM_STATES,
                                         NUM_INPUTS, NUM_OUTPUTS);

  init_mealy_automat(&mealy, 0, (const mealy_transition_t **)transition_table,
                     NUM_STATES, NUM_INPUTS, NUM_OUTPUTS);

  __print_mealy_transition_table((const mealy_transition_t **)transition_table,
                                 NUM_STATES, NUM_INPUTS);

  moore_automation_t moore;

  puts("Начало преобразования");
  if (convert_mealy_to_moore(&mealy, &moore) == 0) {
    puts("Преобразование завершено");
    print_moore_tables(moore.transitions, moore.outputs, moore.num_states,
                       moore.num_inputs);

    free(moore.transitions);
    free(moore.outputs);
  } else {
    puts("CONVERT IS ERROR!!!");
  };

  free_mealy_transition_table(&transition_table, NUM_STATES);

  exit(EXIT_SUCCESS);
}
