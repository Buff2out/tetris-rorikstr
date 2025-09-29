// brick_game/tetris/06_move.c
#include "01_automato.h"

void do_move(void) {
    GameState_t* state = get_game_state();

    int frames_to_wait = (state->moving_type == ToDown) ? 1 : (1000 / state->info->speed);

    if (state->frame_count - state->last_move_frame < frames_to_wait) {
        return;
    }

    state->last_move_frame = state->frame_count;

    state->curr.y++;
    if (check_collision()) {
        state->curr.y--;
        state->state = Attaching;
    }
}