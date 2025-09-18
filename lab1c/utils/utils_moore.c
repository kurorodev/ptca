#include "utils_moore.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_random(void) { srand((unsigned)time(NULL)); }

void generate_random_moore_transition_table(state_t *transitions,
                                            state_t num_states,
                                            input_t num_inputs) {
  for (state_t s = 0; s < num_states; s++) {
    for (input_t in = 0; in < num_inputs; in++) {
      transitions[s * num_inputs + in] = rand() % num_states;
    }
  }
}

void generate_random_moore_output_table(output_t *outputs, state_t num_states,
                                        output_t num_outputs) {
  for (state_t s = 0; s < num_states; s++) {
    outputs[s] = (output_t)(rand() % num_outputs);
  }
}

void generate_random_input_sequence(input_t *inputs, size_t length,
                                    input_t num_inputs) {
  for (size_t i = 0; i < length; i++) {
    inputs[i] = rand() % num_inputs;
  }
}

void print_sequence(const char *label, const uint8_t *sequence, size_t length) {
  printf("%s: ", label);
  for (size_t i = 0; i < length; i++) {
    printf("%u", sequence[i]);
    if (i + 1 < length)
      printf(", ");
  }
  printf("\n");
}

void print_moore_tables(const state_t *transitions, const output_t *outputs,
                        state_t num_states, input_t num_inputs) {
  printf("\n=====ТАБЛИЦА ПЕРЕХОДОВ (b)=====\n");

  printf("     ");
  for (state_t s = 0; s < num_states; s++) {
    printf("  a%d", s);
  }
  printf("\n");

  for (input_t in = 0; in < num_inputs; in++) {
    printf("z%d |", in);
    for (state_t s = 0; s < num_states; s++) {
      state_t next = transitions[s * num_inputs + in];
      printf(" a%d", next);
    }
    printf("\n");
  }

  printf("\n=====ТАБЛИЦА ВЫХОДОВ (λ)=====\n");
  for (state_t s = 0; s < num_states; s++) {
    printf("λ(a%d) = w%d\n", s, outputs[s]);
  }
}
