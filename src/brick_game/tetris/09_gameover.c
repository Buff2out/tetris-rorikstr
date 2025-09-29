#include "01_automato.h"
#include "../../logging.h"

void do_gameover(void) {
    GameState_t* state = get_game_state();
    
    // Сохраняем рекорд, если текущий рекорд побит
    if (state->info->score > state->info->high_score) {
        state->info->high_score = state->info->score;
        save_high_score(state->info->high_score);
    }
    
    // Сброс next в пустую фигуру
    const int (*shape)[4] = empty_fig();
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            state->next.mtrx[i][j] = shape[i][j];
    
    LOG_FUNCTION_END("do_gameover", "");
}

int is_game_over() {
    GameState_t* state = get_game_state();
    // Проверяем, есть ли блоки в верхних рядах
    for (int j = 0; j < FIELD_WIDTH; ++j) {
        if (state->field[0][j] || state->field[1][j]) {
            LOG_FUNCTION_END("is_game_over", "game over detected");
            return 1;
        }
    }
    
    return 0;
}