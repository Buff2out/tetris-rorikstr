#include "01_automato.h"

void userInput(UserAction_t action, bool hold) {
    (void)hold;  // заглушка
    GameState_t* state = get_game_state();

    switch (action) {
        case Start:
            state->state = Init;
            break;
        case Terminate:
            if (state->info.score > state->info.high_score) {
                state->info.high_score = state->info.score;
            }
            state->state = GameOver;
            break;
        case Left:
            state->state = Moving;
            state->moving_type = LeftDown;
            break;
        case Right:
            state->state = Moving;
            state->moving_type = RightDown;
            break;
        case Action:
            state->state = Moving;
            state->moving_type = Rotate;
            break;
        case Down:
            state->state = Moving;
            state->moving_type = ToDown;
            break;
        case Pause:
            state->info.pause = !state->info.pause;
            break;
        default:
            break;
    }
}

GameInfo_t updateCurrentState() {
    GameState_t* state = get_game_state();
    switch (state->state) {
        case Init:
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

    GameInfo_t info = state->info;
    info.field = (int**)state->field;
    info.next = (int**)state->next.mtrx;
    info.pause = 0;
    return info;
}