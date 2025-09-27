CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
INCLUDES = -I../lab1c/mealy -I../lab1c/moore -I../lab1c/utils

# Все исходные файлы
SRCS = main.c \
       ../lab1c/mealy/mealy.c \
       ../lab1c/moore/moore.c \
       ../lab1c/utils/utils_mealy.c \
       ../lab1c/utils/utils_moore.c  # Добавляем utils_moore.c

# Соответствующие объектные файлы
OBJS = main.o \
       mealy.o \
       moore.o \
       utils_mealy.o \
       utils_moore.o

TARGET = converter

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(TARGET)

# Правило для main.o
main.o: main.c
	$(CC) $(CFLAGS) $(INCLUDES) -c main.c -o main.o

# Правила для файлов из других директорий
mealy.o: ../lab1c/mealy/mealy.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ../lab1c/mealy/mealy.c -o mealy.o

moore.o: ../lab1c/moore/moore.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ../lab1c/moore/moore.c -o moore.o

utils_mealy.o: ../lab1c/utils/utils_mealy.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ../lab1c/utils/utils_mealy.c -o utils_mealy.o

utils_moore.o: ../lab1c/utils/utils_moore.c  # Добавляем правило для utils_moore.o
	$(CC) $(CFLAGS) $(INCLUDES) -c ../lab1c/utils/utils_moore.c -o utils_moore.o

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
