#include "mealy.h"
#include <stdio.h>

void init_mealy_automat(mealy_automaton_t *mealy_automat, state_t initial_state,
                        const mealy_transition_t **transition_table,
                        uint8_t num_states, uint8_t num_inputs,
                        uint8_t num_outputs) {
  if (mealy_automat == NULL || transition_table == NULL) {
    puts("Ошибка нет Мили автомата или transition_table");
    return;
  }

  mealy_automat->current_state = initial_state;
  mealy_automat->initial_state = initial_state;
  mealy_automat->transition_table = transition_table;
  mealy_automat->num_states = num_states;
  mealy_automat->num_inputs = num_inputs;
  mealy_automat->num_outputs = num_outputs;
}

output_t mealy_process_input(mealy_automaton_t *mealy_automat, input_t input) {
  if (mealy_automat == NULL)
    puts("Ошибка мили автомат равен NULL");
  return (output_t)-1;

  if (input >= mealy_automat->num_inputs)
    puts("Ошибка вход больше чем доступно у автомата");
  return (output_t)-1;

  if (mealy_automat->current_state >= mealy_automat->num_states)
    puts("Ошибка текущеее состояние больше чем количество состояний");
  return (output_t)-1;

  const mealy_transition_t *transition =
      &mealy_automat->transition_table[mealy_automat->current_state][input];

  if (transition == NULL)
    puts("Ошибка не создалась таблица перехода");
  return (output_t)-1;

  if (transition->next_state >= mealy_automat->current_state)
    puts("Ошибка состояние переходной таблицы больше чем текущее состояние "
         "автомата");
  return (output_t)-1;

  if (transition->output >= mealy_automat->num_outputs)
    puts("Ошибка выход переходной таблицы больше чем количество выходов у "
         "автомата");
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
  mealy_automat->transition_table = NULL;
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

  if (mealy_automat == NULL || input == NULL || sequence_length == 0 ||
      mealy_automat->transition_table == NULL) {
    puts("Ошибка: некорректные параметры");
    return (output_t)-1;
  }

  state_t current_state = mealy_automat->current_state;
  output_t final_output = (output_t)-1;

  // Проверим начальное состояние
  if (current_state >= mealy_automat->num_states) {
    printf("Ошибка: начальное состояние %d превышает количество состояний %d\n",
           current_state, mealy_automat->num_states);
    return (output_t)-1;
  }

  for (size_t i = 0; i < sequence_length; i++) {
    // Проверяем индексы перед доступом
    if (current_state >= mealy_automat->num_states ||
        input[i] >= mealy_automat->num_inputs) {
      printf("Ошибка: state=%d, input=%d (max states=%d, max inputs=%d)\n",
             current_state, input[i], mealy_automat->num_states,
             mealy_automat->num_inputs);
      return (output_t)-1;
    }

    const mealy_transition_t *transition =
        &mealy_automat->transition_table[current_state][input[i]];

    if (transition->next_state >= mealy_automat->num_states) {
      printf(
          "Ошибка: следующее состояние %d превышает количество состояний %d\n",
          transition->next_state, mealy_automat->num_states);
      return (output_t)-1;
    }

    if (transition->output >= mealy_automat->num_outputs) {
      printf("Ошибка: выход %d превышает количество выходов %d\n",
             transition->output, mealy_automat->num_outputs);
      return (output_t)-1;
    }

    // Сохраняем выход на каждом шаге (последний будет финальным)
    final_output = transition->output;
    current_state = transition->next_state;

    printf("Шаг %zu: вход=%d, состояние=%d -> выход=%d, след. состояние=%d\n",
           i, input[i], current_state, final_output, transition->next_state);
  }

  return final_output;
}
