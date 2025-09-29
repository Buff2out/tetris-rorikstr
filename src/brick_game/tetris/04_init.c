#include "01_automato.h"

void do_init(void) {
    GameState_t* state = get_game_state();
    // Очистка поля
    for (int i = 0; i < FIELD_HEIGHT; ++i)
        for (int j = 0; j < FIELD_WIDTH; ++j)
            state->field[i][j] = 0;

    state->info->score = 0;
    state->info->level = 1;
    state->info->speed = 1;
    state->state = Spawn;
}