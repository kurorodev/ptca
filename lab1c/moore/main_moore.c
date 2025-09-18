#include "../utils/utils_moore.h"
#include "moore.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_STATES 5
#define NUM_INPUTS 5
#define NUM_OUTPUTS 5
#define SEQUENCE_LENGTH 10

int main(void) {
  moore_automation_t m;

  state_t *transitions = malloc(NUM_STATES * NUM_INPUTS * sizeof(state_t));
  output_t *outputs = malloc(NUM_STATES * sizeof(output_t));
  if (!transitions || !outputs) {
    fprintf(stderr, "Ошибка: не удалось выделить память\n");
    free(transitions);
    free(outputs);
    return 1;
  }

  init_random();

  generate_random_moore_transition_table(transitions, NUM_STATES, NUM_INPUTS);
  generate_random_moore_output_table(outputs, NUM_STATES, NUM_OUTPUTS);

  moore_init(&m, 0, transitions, outputs, NUM_STATES, NUM_INPUTS, NUM_OUTPUTS);

  input_t inputs[SEQUENCE_LENGTH];
  generate_random_input_sequence(inputs, SEQUENCE_LENGTH, NUM_INPUTS);

  output_t out_seq[SEQUENCE_LENGTH + 1];
  int written = moore_simulate(&m, inputs, SEQUENCE_LENGTH, out_seq);
  if (written < 0) {
    fprintf(stderr,
            "Ошибка: moore_simulate вернул %d - проверь входы/таблицы\n",
            written);
    print_moore_tables(transitions, outputs, NUM_STATES, NUM_INPUTS);
    free(transitions);
    free(outputs);
    return 2;
  }

  print_moore_tables(transitions, outputs, NUM_STATES, NUM_INPUTS);
  print_sequence("Inputs", inputs, SEQUENCE_LENGTH);
  print_sequence("Outputs", out_seq, (size_t)written);

  free(transitions);
  free(outputs);
  return 0;
}
