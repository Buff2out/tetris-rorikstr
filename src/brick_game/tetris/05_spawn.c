#include "01_automato.h"
#include <stdlib.h>

void do_spawn(void) {
    GameState_t* state = get_game_state();
    // Присваиваем curr = next
    state->curr = state->next;
    state->curr.x = FIELD_WIDTH / 2 - 2;
    state->curr.y = 0;

    // Генерим следующую фигуру
    state->next.type = rand() % FIGURE_COUNT;
    state->next.rotation = 0;
    const int (*shape)[4] = get_figure_shape(state->next.type, 0);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            state->next.mtrx[i][j] = shape[i][j];

    // Проверка на GameOver
    if (check_collision()) {
        state->state = GameOver;
        return;
    }

    state->state = Move;
}