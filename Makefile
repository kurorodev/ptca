CXX = g++
CXXFLAGS = -Wall -std=c++11 -I.
BIN_DIR = bin

# Общие объектные файлы
COMMON_SOURCES = common/automaton.cpp
COMMON_OBJECTS = $(COMMON_SOURCES:.cpp=.o)

# Файлы для Мили
MEALY_SOURCES = mealy/mealy.cpp
MEALY_OBJECTS = $(MEALY_SOURCES:.cpp=.o)
MEALY_TARGET = $(BIN_DIR)/mealy_simulator

# Файлы для Мура
MOORE_SOURCES = moore/moore.cpp
MOORE_OBJECTS = $(MOORE_SOURCES:.cpp=.o)
MOORE_TARGET = $(BIN_DIR)/moore_simulator

# Цели по умолчанию
all: mealy moore

# Создание директории для бинарников
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Компиляция общего кода
$(COMMON_OBJECTS): $(COMMON_SOURCES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Компиляция Мили
$(MEALY_OBJECTS): $(MEALY_SOURCES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Компиляция Мура
$(MOORE_OBJECTS): $(MOORE_SOURCES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Сборка симулятора Мили
mealy: $(BIN_DIR) $(COMMON_OBJECTS) $(MEALY_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(MEALY_TARGET) $(COMMON_OBJECTS) $(MEALY_OBJECTS) mealy/main_mealy.cpp

# Сборка симулятора Мура
moore: $(BIN_DIR) $(COMMON_OBJECTS) $(MOORE_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(MOORE_TARGET) $(COMMON_OBJECTS) $(MOORE_OBJECTS) moore/main_moore.cpp

# Очистка
clean:
	rm -rf $(BIN_DIR)
	rm -f $(COMMON_OBJECTS) $(MEALY_OBJECTS) $(MOORE_OBJECTS)

.PHONY: all mealy moore clean