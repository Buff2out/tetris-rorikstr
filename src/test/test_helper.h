#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <check.h>
#include "../brick_game/tetris/01_automato.h"

// Хелпер для очистки поля
static inline void clear_test_field(void) {
    GameState_t* state = get_game_state();
    for (int i = 0; i < FIELD_HEIGHT; i++)
        for (int j = 0; j < FIELD_WIDTH; j++)
            state->field[i][j] = 0;
}

// Хелпер для очистки матрицы фигуры
static inline void clear_figure_matrix(void) {
    GameState_t* state = get_game_state();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            state->curr.mtrx[i][j] = 0;
}

// Хелпер для заполнения линии
static inline void fill_line(int row) {
    GameState_t* state = get_game_state();
    for (int j = 0; j < FIELD_WIDTH; j++) {
        state->field[row][j] = 2;
    }
}

// Setup функция (вызывается перед каждым тестом)
static inline void test_setup(void) {
    GameState_t* state = get_game_state();
    clear_test_field();
    state->info->score = 0;
    state->info->level = 1;
    state->info->speed = 1;
}

#endif
