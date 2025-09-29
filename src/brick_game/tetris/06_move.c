// brick_game/tetris/06_move.c
#include <time.h>
#include "01_automato.h"
#include "../../logging.h"

long long get_time_ms() {
    return (long long)time(NULL) * 1000;
}

void do_move(void) {
    GameState_t* state = get_game_state();
    LOG_FUNCTION_START("do_move", "");

    // Добавляем проверку, чтобы избежать деления на ноль
    if (state->info->speed <= 0) {
        state->info->speed = 1;  // Устанавливаем минимальное значение
    }

    long long current_time = get_time_ms();
    int delay = (state->moving_type == ToDown) ? 50 : (1000 / state->info->speed);

    if (current_time - state->last_time < delay) {
        LOG_FUNCTION_END("do_move", "not enough time passed, delay=%d", delay);
        return;  // ещё не время
    }
    state->last_time = current_time;

    // Двигаем вниз
    state->curr.y++;
    if (check_collision()) {
        state->curr.y--;  // откат
        state->state = Attaching;  // переход в Attaching
    }
    
    LOG_FUNCTION_END("do_move", "curr=(%d,%d), state=%d", 
                     state->curr.x, state->curr.y, state->state);
}