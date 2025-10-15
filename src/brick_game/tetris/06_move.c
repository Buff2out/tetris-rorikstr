#include "01_automato.h"

int get_milliseconds_to_wait(void) {
    GameState_t* state = get_game_state();
    int result = 0;
    
    if (state->moving_type == ToDown) {
        result = 30;
    } else {
        int base_delay = 1100 - (state->info->speed * 100);
        result = (base_delay > 100) ? base_delay : 100;
    }
    
    return result;
}

void do_move(void) {
    GameState_t* state = get_game_state();
    
    long long current_time = get_current_time_ms();
    int ms_to_wait = get_milliseconds_to_wait();
    
    int should_move = (current_time - state->last_move_time >= ms_to_wait);
    
    if (should_move) {
        state->last_move_time = current_time;
        
        state->curr.y++;
        int has_collision = check_collision();
        
        if (has_collision) {
            state->curr.y--;
            state->state = Attaching;
        }
    }
}
