#include "01_automato.h"

int get_milliseconds_to_wait(void) {
    GameState_t* state = get_game_state();
    
    if (state->moving_type == ToDown) {
        return 30;
    }
    
    // Скорость от 1 до 10: 1000ms -> 100ms
    int base_delay = 1100 - (state->info->speed * 100);
    return base_delay > 100 ? base_delay : 100;
}

void do_move(void) {
    GameState_t* state = get_game_state();
    
    long long current_time = get_current_time_ms();
    int ms_to_wait = get_milliseconds_to_wait();
    
    if (current_time - state->last_move_time < ms_to_wait) {
        return;
    }
    
    state->last_move_time = current_time;
    
    state->curr.y++;
    if (check_collision()) {
        state->curr.y--;
        state->state = Attaching;
    }
}
