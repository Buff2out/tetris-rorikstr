#include "01_automato.h"

void do_gameover(void) {
    GameState_t* state = get_game_state();
    
    if (state->info->score > state->info->high_score) {
        state->info->high_score = state->info->score;
        save_high_score(state->info->high_score);
    }
    
    const int (*shape)[4] = empty_fig();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state->next.mtrx[i][j] = shape[i][j];
        }
    }
}

int is_game_over() {
    GameState_t* state = get_game_state();
    int game_over = 0;
    
    for (int j = 0; j < FIELD_WIDTH; ++j) {
        if (state->field[0][j] || state->field[1][j]) {
            game_over = 1;
        }
    }
    
    return game_over;
}
