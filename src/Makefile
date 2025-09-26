.PHONY: all clean valgrind test style format gcov_report all install uninstall

# Автоопределение компилятора и флагов
CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=c11 -g
CHECK_CFLAGS ?= -I/usr/include/check

# Проверяем наличие библиотек
CHECK_LIBS_AVAILABLE := $(shell ldconfig -p 2>/dev/null | grep -q libsubunit && echo yes || echo no)

ifeq ($(CHECK_LIBS_AVAILABLE),yes)
    LDFLAGS ?= -lcheck -lrt -lpthread -lm -lncurses -lsubunit
else
    LDFLAGS ?= -lcheck -lrt -lpthread -lm -lncurses
endif

SRCDIR = .
TESTDIR = test
BUILDDIR = build

# src/Makefile
TETRISDIR = brick_game/tetris
CLIDIR = gui/cli

# Файлы
TETRIS_SRC = $(shell find $(TETRISDIR) -name "*.c")
CLI_SRC = $(shell find $(CLIDIR) -name "*.c")
ALL_SRC = $(TETRIS_SRC) $(CLI_SRC)
OBJ = $(ALL_SRC:.c=.o)

# Имя исполняемого файла
TARGET = tetris_bin

# Установка
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

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

style:
	@cp ../materials/linters/.clang-format .
	@clang-format -n *.c *.h
	@rm .clang-format

format:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h
	rm .clang-format