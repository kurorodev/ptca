#include "utils.h"
#include <stdio.h>

void print_sequence(const char *name, const uint8_t *sequence, size_t length,
                    const char *prefix) {
  printf("%s", name);

  for (size_t i = 0; i < length; i++) {
    printf("%s%d", prefix, sequence[i]);
    if (i < length - 1)
      printf(", ");
  }
  printf("\n");
}

void generate_random_transition_table(mealy_transition_t ***table,
                                      state_t num_states, input_t num_inputs,
                                      output_t num_outputs) {
  *table =
      (mealy_transition_t **)malloc(num_states * sizeof(mealy_transition_t *));

  for (size_t i = 0; i < num_states; i++) {
    (*table)[i] =
        (mealy_transition_t *)malloc(num_inputs * sizeof(mealy_transition_t));

    for (size_t j = 0; j < num_inputs; j++) {
      (*table)[i][j].next_state = rand() % num_states;
      (*table)[i][j].output = rand() % num_outputs;
    }
  }
}

void free_transition_table(mealy_transition_t ***table, state_t num_states) {
  if (*table == NULL)
    return;

  for (size_t i = 0; i < num_states; i++) {
    free((*table)[i]);
  }
  free(*table);
  *table = NULL;
}

void generate_random_input_sequence(input_t *input, size_t length,
                                    input_t num_inputs) {
  for (size_t i = 0; i < length; i++) {
    input[i] = rand() % num_inputs;
  }
}

void __print_transition_table(const mealy_transition_t **table,
                              state_t num_states, input_t num_inputs) {
  printf("======ТАБЛИЦА ПЕРЕХОДОВ======\n");

  for (state_t state = 0; state < num_states; state++) {
    printf("a%d\t", state);
  }
  printf("\n");

  for (input_t input = 0; input < num_inputs; input++) {
    for (state_t state = 0; state < num_states; state++) {
      const mealy_transition_t *transition = &table[state][input];
      printf("a%d/w%d\t", transition->next_state, transition->output);
    }
    printf("\n");
  }
  return;
}
