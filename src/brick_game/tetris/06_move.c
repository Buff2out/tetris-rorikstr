#include <time.h>
#include "01_automato.h"

long long get_time_ms() {
    return (long long)time(NULL) * 1000;
}

void do_move(void) {
    GameState_t* state = get_game_state();

    long long current_time = get_time_ms();

    int delay = (state->moving_type == ToDown) ? 50 : (1000 / state->info.speed);

    if (current_time - state->last_time < delay) {
        return;  // ещё не время
    }
    state->last_time = current_time;

    // Двигаем вниз
    state->curr.y++;
    if (check_collision()) {
        state->curr.y--;  // откат
        state->state = Attaching;  // переход в Attaching
    }
}