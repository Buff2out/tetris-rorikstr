#include "01_automato.h"

void do_init(void) {
    GameState_t* g_state = get_game_state();
    GameInfo_t* g_info = get_game_info();
    // Очистка поля
    for (int i = 0; i < FIELD_HEIGHT; ++i)
        for (int j = 0; j < FIELD_WIDTH; ++j)
            g_state->field[i][j] = 0;

    g_info->score = 0;
    g_info->level = 1;
    g_info->speed = 1;
    g_state->state = Spawn;
}