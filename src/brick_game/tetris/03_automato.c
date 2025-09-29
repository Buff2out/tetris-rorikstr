#include "01_automato.h"

static GameState_t g_state = {0};

GameState_t* get_game_state(void) {
    static GameInfo_t instance = {0};
    static int is_init = 0;
    if (!is_init) {
        g_state.state = GameOver;
        is_init = 1;
    }
    return &g_state;
}