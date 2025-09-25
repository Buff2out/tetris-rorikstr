CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -g
LDFLAGS = -lncurses
TETRISDIR = brick_game/tetris
CLIDIR = gui/cli

# Файлы
TETRIS_SRC = $(TETRISDIR)/tetris.c
CLI_SRC = $(CLIDIR)/main.c $(CLIDIR)/display.c
OBJ = $(TETRIS_SRC:.c=.o) $(CLI_SRC:.c=.o)

# Имя исполняемого файла
TARGET = tetris

# Установка
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

.PHONY: all install uninstall clean test gcov_report

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	install -m 755 $(TARGET) $(BINDIR)/

uninstall:
	rm -f $(BINDIR)/$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET) *.gcda *.gcno *.gcov

test:
	@echo "Running tests..."
	# Здесь будет вызов тестов, если они есть

gcov_report: CFLAGS += --coverage
gcov_report: clean $(TARGET)
	./$(TARGET)
	gcov $(TETRIS_SRC)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report
	@echo "Coverage report generated in coverage_report/index.html"