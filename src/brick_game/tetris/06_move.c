// brick_game/tetris/06_move.c
#include <time.h>
#include "01_automato.h"
#include "../../logging.h"

long long get_time_ms() {
    return (long long)time(NULL) * 1000;
}

void do_move(void) {
    GameState_t* state = get_game_state();
    LOG_FUNCTION_START("do_move", "speed=%d, moving_type=%d, current_pos=(%d,%d)", 
                       state->info->speed, state->moving_type, state->curr.x, state->curr.y);

    // Рассчитываем, сколько кадров должно пройти между движениями
    int frames_to_wait = (state->moving_type == ToDown) ? 1 : (1000 / state->info->speed);

    // Проверяем, прошло ли достаточно кадров
    if (state->frame_count - state->last_move_frame < frames_to_wait) {
        LOG_FUNCTION_END("do_move", "not enough frames passed, frame_count=%lld, last_move_frame=%lld, frames_to_wait=%d", 
                         state->frame_count, state->last_move_frame, frames_to_wait);
        return;
    }

    // Обновляем время последнего движения
    state->last_move_frame = state->frame_count;

    // Двигаем вниз
    state->curr.y++;
    if (check_collision()) {
        state->curr.y--;  // откат
        state->state = Attaching;  // переход в Attaching
    }
    
    LOG_FUNCTION_END("do_move", "moved to (%d,%d), state=%d", 
                     state->curr.x, state->curr.y, state->state);
}