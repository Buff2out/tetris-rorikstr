.PHONY: all clean install uninstall test gcov_report dvi dist run style format

CC ?= gcc
CFLAGS ?= -Wall -Wextra -Werror -std=c11 -g -D_POSIX_C_SOURCE=199309L -MMD -MP
CHECK_CFLAGS ?= -I/usr/include/check

# Проверяем наличие библиотек
CHECK_LIBS_AVAILABLE := $(shell ldconfig -p 2>/dev/null | grep -q libsubunit && echo yes || echo no)

ifeq ($(CHECK_LIBS_AVAILABLE),yes)
    LDFLAGS ?= -lcheck -lrt -lpthread -lm -lncurses -lsubunit
else
    LDFLAGS ?= -lcheck -lrt -lpthread -lm -lncurses
endif

BUILDDIR = build
TETRISDIR = brick_game/tetris
CLIDIR = gui/cli

# Файлы
TETRIS_SRC = $(shell find $(TETRISDIR) -name "*.c")
TETRIS_OBJ = $(TETRIS_SRC:.c=.o)
CLI_SRC = $(shell find $(CLIDIR) -name "*.c")
CLI_OBJ = $(CLI_SRC:.c=.o)

LIB_TETRIS = $(BUILDDIR)/libtetris.a
TARGET = $(BUILDDIR)/tetris_bin.out

# Установка
PREFIX ?= $(HOME)/.local
BINDIR = $(PREFIX)/bin

all: $(TARGET)

$(LIB_TETRIS): $(TETRIS_OBJ)
	mkdir -p $(BUILDDIR)
	ar rcs $@ $^

$(TARGET): $(LIB_TETRIS) $(CLI_OBJ)
	$(CC) $(CLI_OBJ) -L$(BUILDDIR) -ltetris -o $@ $(LDFLAGS)

brick_game/tetris/%.o: brick_game/tetris/%.c
	$(CC) $(CFLAGS) -c $< -o $@

gui/cli/%.o: gui/cli/%.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	install -m 755 $(TARGET) $(BINDIR)/tetris_bin.out

uninstall:
	rm -f $(BINDIR)/tetris_bin.out

clean:
	rm -rf $(CLI_OBJ) $(TETRIS_OBJ) $(TARGET) $(LIB_TETRIS)
	rm -rf $(BUILDDIR)/*.gcda $(BUILDDIR)/*.gcno *.gcda *.gcno *.gcov $(TETRISDIR)/*.d $(CLIDIR)/*.d
	rm -rf coverage.info coverage_report

test: $(LIB_TETRIS)
	$(CC) $(CFLAGS) test/test.c -L$(BUILDDIR) -ltetris $(LDFLAGS) -o $(BUILDDIR)/test.out
	./$(BUILDDIR)/test.out

gcov_report: CFLAGS += --coverage
gcov_report: LDFLAGS += --coverage
gcov_report: clean $(TARGET)
	@echo "Note: Run automated tests for proper coverage"
	gcov $(TETRIS_SRC)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report
	@echo "Coverage report: coverage_report/index.html"

dvi:
	doxygen Doxyfile 2>/dev/null || echo "Doxyfile not found"

dist: clean
	tar -czf tetris.tar.gz Makefile $(TETRISDIR) $(CLIDIR) README.md

run: $(TARGET)
	./$(TARGET)

style:
	@if [ -f .clang-format ]; then \
		clang-format -n $(TETRIS_SRC) $(CLI_SRC); \
	else \
		echo ".clang-format not found"; \
	fi

format:
	@if [ -f .clang-format ]; then \
		clang-format -i $(TETRIS_SRC) $(CLI_SRC); \
	else \
		echo ".clang-format not found"; \
	fi

-include $(TETRIS_OBJ:.o=.d) $(CLI_OBJ:.o=.d)