#include "01_automato.h"

void do_init(void) {
    GameState_t* state = get_game_state();
    
    // Очищаем поле
    for (int i = 0; i < FIELD_HEIGHT; ++i)
        for (int j = 0; j < FIELD_WIDTH; ++j)
            state->field[i][j] = 0;

    state->info->score = 0;
    state->info->level = 1;
    state->info->speed = 10;

    state->next.sprite = rand() % FIGURE_COUNT;
    state->next.rotation = 0;
    const int (*shape)[4] = get_figure_shape(state->next.sprite, 0);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            state->next.mtrx[i][j] = shape[i][j];

    state->state = Spawn;  // Переход в Spawn
}