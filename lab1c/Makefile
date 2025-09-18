
CC = gcc
CFLAGS = -Wall -std=c99 -I. -g
BIN_DIR = bin

# Утилиты для Мили
UTILS_MEALY_SOURCES = utils/utils_mealy.c
UTILS_MEALY_OBJECTS = $(UTILS_MEALY_SOURCES:.c=.o)

# Утилиты для Мура
UTILS_MOORE_SOURCES = utils/utils_moore.c
UTILS_MOORE_OBJECTS = $(UTILS_MOORE_SOURCES:.c=.o)

# Файлы для Мили
MEALY_SOURCES = mealy/mealy.c mealy/main_mealy.c
MEALY_OBJECTS = $(MEALY_SOURCES:.c=.o)
MEALY_TARGET = $(BIN_DIR)/mealy_simulator

# Файлы для Мура
MOORE_SOURCES = moore/moore.c moore/main_moore.c
MOORE_OBJECTS = $(MOORE_SOURCES:.c=.o)
MOORE_TARGET = $(BIN_DIR)/moore_simulator

# Цели по умолчанию
all: mealy moore

# Создание директории для бинарников
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Компиляция утилит Мили
utils/%.o: utils/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция файлов Мили
mealy/%.o: mealy/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция утилит Мура
utils/%.o: utils/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция файлов Мура
moore/%.o: moore/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Сборка симулятора Мили
mealy: $(BIN_DIR) $(UTILS_MEALY_OBJECTS) $(MEALY_OBJECTS)
	$(CC) $(CFLAGS) -o $(MEALY_TARGET) $(UTILS_MEALY_OBJECTS) $(MEALY_OBJECTS)
	@echo "✅ Автомат Мили скомпилирован: $(MEALY_TARGET)"

# Сборка симулятора Мура
moore: $(BIN_DIR) $(UTILS_MOORE_OBJECTS) $(MOORE_OBJECTS)
	$(CC) $(CFLAGS) -o $(MOORE_TARGET) $(UTILS_MOORE_OBJECTS) $(MOORE_OBJECTS)
	@echo "✅ Автомат Мура скомпилирован: $(MOORE_TARGET)"

# Запуск симулятора Мили (компиляция + запуск)
run-mealy: mealy
	@echo "🚀 Запуск автомата Мили..."
	./$(MEALY_TARGET)

# Запуск симулятора Мура (компиляция + запуск)
run-moore: moore
	@echo "🚀 Запуск автомата Мура..."
	./$(MOORE_TARGET)

# Компиляция только Мили (отдельно)
mealy-only: $(BIN_DIR) $(UTILS_MEALY_OBJECTS) $(MEALY_OBJECTS)
	$(CC) $(CFLAGS) -o $(MEALY_TARGET) $(UTILS_MEALY_OBJECTS) $(MEALY_OBJECTS)
	@echo "✅ Автомат Мили скомпилирован: $(MEALY_TARGET)"

# Компиляция только Мура (отдельно)
moore-only: $(BIN_DIR) $(UTILS_MOORE_OBJECTS) $(MOORE_OBJECTS)
	$(CC) $(CFLAGS) -o $(MOORE_TARGET) $(UTILS_MOORE_OBJECTS) $(MOORE_OBJECTS)
	@echo "✅ Автомат Мура скомпилирован: $(MOORE_TARGET)"

# Очистка
clean:
	rm -rf $(BIN_DIR)
	rm -f $(UTILS_MEALY_OBJECTS) $(UTILS_MOORE_OBJECTS) $(MEALY_OBJECTS) $(MOORE_OBJECTS)
	@echo "🧹 Очистка завершена"

.PHONY: all mealy moore run-mealy run-moore mealy-only moore-only clean
