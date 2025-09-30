#include "01_automato.h"

void set_current_figure_from_next(void) {
    GameState_t* state = get_game_state();
    state->curr = state->next;
    state->curr.x = FIELD_WIDTH / 2 - 2;
    state->curr.y = 0;
    state->moving_type = DoNothing;
}

void generate_next_figure(void) {
    GameState_t* state = get_game_state();
    state->next.sprite = rand() % FIGURE_COUNT;
    state->next.rotation = 0;
    const int (*shape)[4] = get_figure_shape(state->next.sprite, 0);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            state->next.mtrx[i][j] = shape[i][j];
}

void do_spawn(void) {
    set_current_figure_from_next();
    generate_next_figure();
    
    if (check_collision()) {
        get_game_state()->state = GameOver;
        return; // TODO
    }

    get_game_state()->state = Move;
}