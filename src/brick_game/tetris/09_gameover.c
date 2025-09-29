#include "01_automato.h"

void do_gameover(void) {
    GameState_t* state = get_game_state();
    // Сброс next в пустую фигуру
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            state->next.mtrx[i][j] = 0;
}