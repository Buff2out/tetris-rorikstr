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
TESTDIR = test
GCOV_DIR = gcov_report
DVI_DIR = dvi

# Файлы
TETRIS_SRC = $(shell find $(TETRISDIR) -name "*.c")
TETRIS_OBJ = $(TETRIS_SRC:.c=.o)
CLI_SRC = $(shell find $(CLIDIR) -name "*.c")
CLI_OBJ = $(CLI_SRC:.c=.o)

LIB_TETRIS = $(BUILDDIR)/libtetris.a
TARGET = $(BUILDDIR)/tetris_bin.out
TEST_TARGET = $(BUILDDIR)/test.out

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
	mkdir -p $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)/tetris

uninstall:
	rm -f $(BINDIR)/tetris

clean:
	rm -rf $(CLI_OBJ) $(TETRIS_OBJ) $(TARGET) $(LIB_TETRIS) $(TEST_TARGET)
	rm -rf $(TETRISDIR)/*.d $(CLIDIR)/*.d
	rm -rf $(GCOV_DIR) $(DVI_DIR)

test: $(LIB_TETRIS)
	$(CC) $(CFLAGS) $(TESTDIR)/test.c -L$(BUILDDIR) -ltetris $(LDFLAGS) -o $(TEST_TARGET)
	./$(TEST_TARGET)

gcov_report: CFLAGS += --coverage
gcov_report: LDFLAGS += --coverage
gcov_report: clean test
	@mkdir -p $(GCOV_DIR)
	gcov $(TETRIS_SRC) -o $(TETRISDIR)
	lcov --capture --directory . --output-file $(GCOV_DIR)/coverage.info
	lcov --remove $(GCOV_DIR)/coverage.info '/usr/*' '*/nix/store/*' -o $(GCOV_DIR)/coverage.info
	genhtml $(GCOV_DIR)/coverage.info --output-directory $(GCOV_DIR)
	mv *.gcov $(GCOV_DIR)/ 2>/dev/null || true
	@echo "Report: $(GCOV_DIR)/index.html"

dvi:
	@mkdir -p $(DVI_DIR)
	@cp doc.md $(DVI_DIR)/ 2>/dev/null || echo "doc.md not found"
	@if command -v doxygen >/dev/null 2>&1 && [ -f Doxyfile ]; then \
		doxygen Doxyfile; \
	fi
	@echo "Documentation in $(DVI_DIR)/"

dist: clean
	tar -czf tetris.tar.gz Makefile $(TETRISDIR) $(CLIDIR) $(TESTDIR) README.md doc.md

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
