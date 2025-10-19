.PHONY: all clean install uninstall test test_coverage gcov_report dvi dist run style format

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
TEST_SRC = $(filter-out $(TESTDIR)/test.c, $(shell find $(TESTDIR) -name "*.c"))

LIB_TETRIS = $(BUILDDIR)/libtetris.a
TARGET = $(BUILDDIR)/tetris_bin.out
TEST_TARGET = $(BUILDDIR)/test.out

# Установка
PREFIX ?= $(HOME)/.local
BINDIR = $(PREFIX)/bin

all: dvi dist install gcov_report run

run: clean $(TARGET)
	./$(TARGET)

install: $(TARGET)
	mkdir -p $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)/tetris
	@echo "installed $(BINDIR)/tetris"

uninstall:
	rm -f $(BINDIR)/tetris
	@echo "uninstalled $(BINDIR)/tetris"

clean:
	rm -rf $(CLI_OBJ) $(TETRIS_OBJ) $(TARGET) $(LIB_TETRIS) $(TEST_TARGET)
	rm -rf $(TETRISDIR)/*.d $(CLIDIR)/*.d
	rm -rf $(TETRISDIR)/*.gcda $(TETRISDIR)/*.gcno $(TETRISDIR)/*.gcov
	rm -rf $(GCOV_DIR) $(DVI_DIR)

test: clean $(LIB_TETRIS)
	$(CC) $(CFLAGS) $(TEST_SRC) -L$(BUILDDIR) -ltetris $(LDFLAGS) -o $(TEST_TARGET)
	./$(TEST_TARGET)

test_coverage: CFLAGS += --coverage
test_coverage: LDFLAGS += --coverage
test_coverage: clean $(LIB_TETRIS)
	$(CC) $(CFLAGS) $(TEST_SRC) -L$(BUILDDIR) -ltetris $(LDFLAGS) -o $(TEST_TARGET)
	./$(TEST_TARGET)

gcov_report: test_coverage
	@mkdir -p $(GCOV_DIR)/obj
	@find $(TETRISDIR) -name "*.gcda" -exec mv {} $(GCOV_DIR)/obj/ \;
	@find $(TETRISDIR) -name "*.gcno" -exec mv {} $(GCOV_DIR)/obj/ \;
	@cd $(GCOV_DIR) && for src in $(addprefix ../,$(TETRIS_SRC)); do \
		gcov $$src -o obj/ 2>/dev/null; \
	done
	lcov --capture --directory $(GCOV_DIR)/obj \
		--output-file $(GCOV_DIR)/coverage.info \
		--ignore-errors unused
	lcov --extract $(GCOV_DIR)/coverage.info '*/brick_game/tetris/*' \
		-o $(GCOV_DIR)/coverage.info \
		--ignore-errors unused
	genhtml $(GCOV_DIR)/coverage.info \
		--output-directory $(GCOV_DIR)
	@echo "Report: $(GCOV_DIR)/index.html"
	xdg-open $(GCOV_DIR)/index.html


dvi:
	@mkdir -p $(DVI_DIR)
	@echo "Generating documentation with Doxygen..."
	@if command -v doxygen >/dev/null 2>&1; then \
		doxygen Doxyfile && echo "HTML docs: $(DVI_DIR)/html/index.html"; \
	else \
		echo "Error: Doxygen not found. Install: nix-shell -p doxygen"; \
		echo "Copying doc.md as fallback..."; \
		cp doc.md $(DVI_DIR)/; \
	fi
	xdg-open $(DVI_DIR)/html/index.html

dist: clean
	tar -czf tetris.tar.gz Makefile $(TETRISDIR) $(CLIDIR) $(TESTDIR) README.md doc.md

style:
	@if [ -f ../materials/linters/.clang-format ]; then \
		clang-format -n $(TETRIS_SRC) $(CLI_SRC); \
	else \
		echo ".clang-format not found"; \
	fi

format:
	@if [ -f ../materials/linters/.clang-format ]; then \
		clang-format -i $(TETRIS_SRC) $(CLI_SRC); \
	else \
		echo ".clang-format not found"; \
	fi

$(LIB_TETRIS): $(TETRIS_OBJ)
	mkdir -p $(BUILDDIR)
	ar rcs $@ $^

$(TARGET): $(LIB_TETRIS) $(CLI_OBJ)
	$(CC) $(CLI_OBJ) -L$(BUILDDIR) -ltetris -o $@ $(LDFLAGS)

brick_game/tetris/%.o: brick_game/tetris/%.c
	$(CC) $(CFLAGS) -c $< -o $@

gui/cli/%.o: gui/cli/%.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(TETRIS_OBJ:.o=.d) $(CLI_OBJ:.o=.d)
