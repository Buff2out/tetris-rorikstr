#include "01_automato.h"

int get_frames_to_wait(void) {
    GameState_t* state = get_game_state();
    if (state->moving_type == ToDown) {
        return 1; // TODO
    } else {
        return 1000 / state->info->speed; // TODO
    }
}

void do_move(void) {
    GameState_t* state = get_game_state();

    int frames_to_wait = get_frames_to_wait();

    if (state->frame_count - state->last_move_frame < frames_to_wait) {
        return; // TODO
    }

    state->last_move_frame = state->frame_count;

    state->curr.y++;
    if (check_collision()) {
        state->curr.y--;
        state->state = Attaching;
    }
}