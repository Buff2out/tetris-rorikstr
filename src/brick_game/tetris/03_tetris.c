#include "01_automato.h"
#include <stdlib.h>

void userInput(UserAction_t action, bool hold) {
    GameState_t* state = get_game_state();

    switch (action) {
        case Start:
            state->state = Start;
            break;
        case Terminate:
            if (state->score > state->high_score) {
                state->high_score = state->score;
            }
            exit(0);
            break;
        case Left:
        case Right:
        case Action:
            state->state = Moving;
            break;
        case Down:
            // Ускорение падения — будет обрабатываться в do_move
            break;
        case Pause:
            // Обработка на UI
            break;
    }
}

GameInfo_t updateCurrentState() {
    GameState_t* state = get_game_state();
    switch (state->state) {
        case Start:
            do_start();
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
    info.field = (int**)state->field;
    info.next = (int**)state->next.mtrx;  // теперь next.mtrx
    info.score = state->score;
    info.high_score = state->high_score;
    info.level = state->level;
    info.speed = state->speed;
    info.pause = 0;
    return info;
}