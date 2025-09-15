/* Реализация заголовочного файла Конечного Абстрактного автомата Mealy*/

#ifndef MEALY_H
#define MEALY_H

#include <stddef.h>
#include <stdint.h>

#define NUM_STATES 5
#define NUM_INPUTS 5
#define NUM_OUTPUTS 5
#define SEQUENCE_LENGTH 5

typedef uint8_t state_t; /* Переименнованые типы для хранения состояния,
                            входного/выходного символа */
typedef uint8_t input_t;
typedef uint8_t output_t;

typedef struct { /* Структура таблици перехода  */
  state_t next_state;
  output_t output;
} mealy_transition_t;

typedef struct { /* Структура автомата Мили  */
  state_t current_state;
  state_t initial_state;

  const mealy_transition_t **transition_table;

  uint8_t num_states;
  uint8_t num_inputs;
  uint8_t num_outputs;
} mealy_automaton_t;

void init_mealy_automat(mealy_automaton_t *mealy_automat, state_t initial_state,
                        const mealy_transition_t **transiotion_table,
                        uint8_t num_states, uint8_t num_inputs,
                        uint8_t num_outputs); /* Инициализация автомата Мили  */

output_t
mealy_process_input(mealy_automaton_t *mealy_automat,
                    input_t input); /* Процесс получаения выходного значения  */

void mealy_reset(
    mealy_automaton_t *mealy_automat); /* Функция сброса автомата Мили  */

state_t get_current_state(
    const mealy_automaton_t
        *mealy_automat); /* Функция получения текующего состояния */

output_t
mealy_final_output(const mealy_automaton_t *mealy_automat, const input_t *input,
                   size_t sequence_length); /* Функция получения выходного
                                               значения автомата Мили  */

void __mealy_get_reaction(
    const mealy_automaton_t *mealy_automat, const input_t *input,
    size_t input_size,
    output_t *output); /* Функция получения реакции автомата Мили  */

#endif // MEALY_H
