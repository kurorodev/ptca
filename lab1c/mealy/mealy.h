#ifndef MILI_AUTOMATON_H
#define MILI_AUTOMATON_H

#include <stddef.h>
#include <stdint.h>

// Типы данных согласно определению автомата Мили (стр. 5)
typedef uint8_t state_t;  // Тип для состояний автомата (A = {a1, a2, ..., aM})
typedef uint8_t input_t;  // Тип для входных сигналов (Z = {z1, z2, ..., zF})
typedef uint8_t output_t; // Тип для выходных сигналов (W = {w1, w2, ..., wG})

// Структура перехода автомата Мили (стр. 6, формула 1.3)
typedef struct {
  state_t next_state; // Следующее состояние (δ функция)
  output_t output;    // Выходной сигнал (λ функция)
} mili_transition_t;

// Основная структура автомата Мили (стр. 5, формула 1.1)
typedef struct {
  state_t current_state; // Текущее состояние am(t)
  state_t initial_state; // Начальное состояние a1

  // Таблица переходов и выходов (стр. 7-8, таблица 1.3)
  const mili_transition_t **transition_table;

  // Мощности алфавитов (стр. 21 - 4-5 элементов)
  uint8_t num_states;  // M - количество состояний
  uint8_t num_inputs;  // F - количество входных сигналов
  uint8_t num_outputs; // G - количество выходных сигналов

} mili_automaton_t;

// Функция инициализации автомата
void mili_init(mili_automaton_t *automaton, state_t initial_state,
               const mili_transition_t **transition_table, uint8_t num_states,
               uint8_t num_inputs, uint8_t num_outputs);

// Функция обработки входного сигнала (стр. 6)
output_t mili_process_input(mili_automaton_t *automaton, input_t input);

// Функция сброса в начальное состояние
void mili_reset(mili_automaton_t *automaton);

// Функция получения текущего состояния
state_t mili_get_current_state(const mili_automaton_t *automaton);

// Функция заключительного состояния (стр. 9-10)
state_t mili_final_state(const mili_automaton_t *automaton,
                         const input_t *input_sequence, size_t sequence_length);

// Функция заключительного выхода (стр. 10)
output_t mili_final_output(const mili_automaton_t *automaton,
                           const input_t *input_sequence,
                           size_t sequence_length);

// Реакция автомата на входное слово (стр. 11, формула 1.5)
void mili_get_reaction(const mili_automaton_t *automaton,
                       const input_t *input_sequence, size_t sequence_length,
                       output_t *output_sequence);

// Вспомогательные макросы для создания таблицы переходов
#define MILI_TRANSITION(next, out) {next, out}
#define MILI_TABLE_ROW(...) {__VA_ARGS__}

// Константы для типичных размеров алфавитов (стр. 21)
#define DEFAULT_NUM_STATES 5
#define DEFAULT_NUM_INPUTS 5
#define DEFAULT_NUM_OUTPUTS 5

#endif // MILI_AUTOMATON_H
