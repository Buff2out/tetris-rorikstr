#include "01_automato.h"

void clear_field(void) {
    GameState_t* state = get_game_state();
    for (int i = 0; i < FIELD_HEIGHT; ++i)
        for (int j = 0; j < FIELD_WIDTH; ++j)
            state->field[i][j] = 0;
}

void reset_game_stats(void) {
    GameState_t* state = get_game_state();
    state->info->score = 0;
    state->info->level = 1;
    state->info->speed = 1;
    state->last_move_time = get_current_time_ms();
}

void do_init(void) {
    clear_field();
    reset_game_stats();
    generate_next_figure();
    get_game_state()->state = Spawn;
}
