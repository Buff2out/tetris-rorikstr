#include "01_automato.h"
#include <stdlib.h>

void userInput(UserAction_t action, bool hold) {
    GameState_t* g_state = get_game_state();
    GameInfo_t* g_info = get_info_state();

    switch (action) {
        case Start:
            g_state->state = Init;
            break;
        case Terminate:
            if (g_info->score > g_info->high_score) {
                g_info->high_score = g_info->score;
            }
            break;
        case Left:
            g_state->state = Moving;
            g_state->moving_type = LeftDown;
            break;
        case Right:
            g_state->state = Moving;
            g_state->moving_type = RightDown;
            break;
        case Action:
            g_state->state = Moving;
            g_state->moving_type = Rotate;
            break;
        case Down:
            // Ускорение падения — будет обрабатываться в do_move
            break;
        default:
            break; // pause и down - не нужны в backend логике.
    }
}

GameInfo_t updateCurrentState() {
    GameState_t* g_state = get_game_state();
    switch (g_state->state) {
        case Start:
            do_init();
            break;
        case Spawn:
            do_spawn();
            break;
        case Move:
            do_move();
            break;
        case Moving:
            do_moving();
            break;
        case Attaching:
            do_attaching();
            break;
        case GameOver:
            do_gameover();
            break;
    }

    GameInfo_t info = {0};
    info.field = (int**)g_state->field;
    info.next = (int**)g_state->next.mtrx;  // теперь next.mtrx
    info.pause = 0;
    return info;
}