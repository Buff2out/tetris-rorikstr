// src/gui/cli/display.c
#include <ncurses.h>
#include "../../brick_game/tetris/tetris.h"

void display_game() {
    clear();

    GameStateData* state = getGameState();

    // Очистка поля
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            mvaddch(i + 1, j * 2 + 1, '.');
        }
    }

    // Если фигура активна — отображаем её
    if (state->figure_active) {
        Figure* f = &state->current_figure;
        const int (*shape)[4] = get_figure_shape(f->type, f->rotation);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (shape[i][j]) {
                    int x = f->x + j;
                    int y = f->y + i;
                    if (x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT) {
                        mvaddch(y + 1, x * 2 + 1, '$');
                    }
                }
            }
        }
    }

    refresh();
}