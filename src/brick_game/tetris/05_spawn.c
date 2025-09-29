#include "01_automato.h"
#include <stdlib.h>
#include "../../logging.h"

void do_spawn(void) {
    LOG_FUNCTION_START("do_spawn", "");
    
    GameState_t* state = get_game_state();
    
    // Устанавливаем текущую фигуру из следующей (или генерируем первую)
    state->curr = state->next;
    state->curr.x = FIELD_WIDTH / 2 - 2;
    state->curr.y = 0;

    // Генерим новую следующую фигуру
    state->next.sprite = rand() % FIGURE_COUNT;
    state->next.rotation = 0;
    const int (*shape)[4] = get_figure_shape(state->next.sprite, 0);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            state->next.mtrx[i][j] = shape[i][j];

    // Проверка на GameOver
    if (check_collision()) {
        state->state = GameOver;
        LOG_FUNCTION_END("do_spawn", "collision detected, state=%d", state->state);
        return;
    }

    state->state = Move;
    
    LOG_FUNCTION_END("do_spawn", "curr=(%d,%d), next_sprite=%d, state=%d", 
                     state->curr.x, state->curr.y, state->next.sprite, state->state);
}