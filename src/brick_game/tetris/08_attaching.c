#include "01_automato.h"

void do_attaching(void) {
    GameState_t* state = get_game_state();
    // Закрепляем фигуру на поле
    place_figure();

    // Удаляем линии
    clear_lines();

    // Проверяем GameOver
    int is_gameov = 0;
    if (is_game_over()) {
        state->state = GameOver;
    } else {
        state->state = Spawn;
    }
}

int check_collision() {
    GameState_t* state = get_game_state();
    Figure_t* fig = &state->curr;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (fig->mtrx[i][j]) {
                int x = fig->x + j;
                int y = fig->y + i;

                if (x < 0 || x >= FIELD_WIDTH || y >= FIELD_HEIGHT) {
                    return 1;  // коллизия
                }
                if (y >= 0 && state->field[y][x]) {
                    return 1;  // коллизия с другой фигурой
                }
            }
        }
    }
    return 0;  // нет коллизии
}

void place_figure() {
    GameState_t* state = get_game_state();
    Figure_t* fig = &state->curr;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (fig->mtrx[i][j]) {
                int x = fig->x + j;
                int y = fig->y + i;
                if (y >= 0 && y < FIELD_HEIGHT && x >= 0 && x < FIELD_WIDTH) {
                    state->field[y][x] = 2;  // закреплённая фигура
                }
            }
        }
    }
}

void clear_lines() {
    GameState_t* state = get_game_state();
    int lines_cleared = 0;

    for (int i = FIELD_HEIGHT - 1; i >= 0; --i) {
        int full = 1;
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            if (state->field[i][j] != 2) {
                full = 0;
                break;
            }
        }
        if (full) {
            // Сдвигаем строки вниз
            for (int y = i; y > 0; --y) {
                for (int x = 0; x < FIELD_WIDTH; ++x) {
                    state->field[y][x] = state->field[y - 1][x];
                }
            }
            // Очищаем верхнюю строку
            for (int x = 0; x < FIELD_WIDTH; ++x) {
                state->field[0][x] = 0;
            }
            lines_cleared++;
            i++;  // проверяем эту строку снова
        }
    }

    // Начисление очков
    if (lines_cleared > 0) {
        int points[] = {0, 100, 300, 700, 1500};
        state->info.score += points[lines_cleared];
        if (state->info.score / 600 > state->info.level - 1) {
            state->info.level++;
            state->info.speed = state->info.level;
        }
    }
}