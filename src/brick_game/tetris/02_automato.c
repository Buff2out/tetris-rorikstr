#include "01_automato.h"

static GameState_t g_state = {0};

GameState_t* get_game_state(void) {
    static int initialized = 0;
    if (!initialized) {
        g_state.state = GameOver;
        initialized = 1;
    }
    return &g_state;
}