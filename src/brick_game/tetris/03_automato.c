#include "01_automato.h"

GameState_t* get_game_state(void) {
    static GameState_t state = {0};
    static int initialized = 0;
    if (!initialized) {
        state.state = GameOver;
        initialized = 1;
    }
    return &state;
}