#include "01_automato.h"

int get_milliseconds_to_wait(void) {
    GameState_t* state = get_game_state();
    int result = 0;
    
    if (state->moving_type == ToDown) {
        result = INSTANT_DROP_DELAY_MS;
    } else {
        int base_delay = BASE_FALL_DELAY_MS - (state->info->speed * SPEED_MULTIPLIER_MS);
        result = (base_delay > SPEED_MULTIPLIER_MS) ? base_delay : SPEED_MULTIPLIER_MS;
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
