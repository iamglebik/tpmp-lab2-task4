CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
TARGET = bin/program
SOURCES = src/main.c src/pensioner.c
OBJECTS = $(SOURCES:src/%.c=obj/%.o)

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	$(CC) -o $@ $^

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean check distcheck

clean:
	rm -f obj/*.o bin/program
	rm -f data/pensioners_over_5_years.txt

check: $(TARGET)
	./$(TARGET)

distcheck: check

all: $(TARGET)
