#include "01_automato.h"

void userInput(UserAction_t action, bool hold) {
    (void)hold;
    GameState_t* state = get_game_state();

    int should_process = 1;
    
    // Проверка паузы
    if (state->info->pause) {
        if (action == Left || action == Right || action == Down || 
            action == Up || action == Action || action == Start) {
            should_process = 0;
        }
    }
    
    // Блокируем движения во время Attaching (до завершения задержки)
    if (state->state == Attaching && !state->attach_completed) {
        if (action == Left || action == Right || action == Down || 
            action == Up || action == Action) {
            should_process = 0;
        }
    }

    if (should_process) {
        switch (action) {
            case Start:
                if (state->info->score >= state->info->high_score) {
                    state->info->high_score = state->info->score;
                    save_high_score(state->info->high_score);
                }
                state->info->high_score = load_high_score();
                state->state = Init;
                state->down_key_was_released = 1;
                break;
            case Terminate:
                if (state->info->score > state->info->high_score) {
                    state->info->high_score = state->info->score;
                    save_high_score(state->info->high_score);
                }
                terminate_and_free();
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
                if (state->down_key_was_released) {
                    state->state = Moving;
                    state->moving_type = ToDown;
                    state->down_key_was_released = 0;
                }
                break;
            case Up:
                state->down_key_was_released = 1;
                break;
            case Pause:
                if (!state->info->pause) {
                    state->pause_start_time = get_current_time_ms();
                } else {
                    long long pause_duration = get_current_time_ms() - state->pause_start_time;
                    state->last_move_time += pause_duration;
                    // Корректируем attach_start_time если мы в Attaching
                    state->attach_start_time += (state->state == Attaching) * pause_duration;
                }
                state->info->pause = !state->info->pause;
                break;
            default:
                break;
        }
    }
}

GameInfo_t updateCurrentState() {
    GameState_t* state = get_game_state();
    
    int should_update = (!state->info->pause || state->state == GameOver);
    if (should_update) {
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
    }

    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            state->info->field[i][j] = state->field[i][j];
        }
    }

    Figure_t* fig = &state->curr;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (fig->mtrx[i][j]) {
                int x = fig->x + j;
                int y = fig->y + i;
                if (y >= 0 && y < FIELD_HEIGHT && x >= 0 && x < FIELD_WIDTH) {
                    state->info->field[y][x] = 1;
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state->info->next[i][j] = state->next.mtrx[i][j];
        }
    }
    
    return *state->info;
}
