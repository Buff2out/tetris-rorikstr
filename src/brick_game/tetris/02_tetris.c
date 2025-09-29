#include "01_automato.h"
#include "../../logging.h"

void userInput(UserAction_t action, bool hold) {
    (void)hold;  // заглушка
    GameState_t* state = get_game_state();

    // Если игра на паузе, обрабатываются только определенные команды
    if (state->info->pause && 
        (action == Left || action == Right || action == Down || action == Up || 
         action == Action || action == Start)) {
        return;
    }

    switch (action) {
        case Start:
            // Загружаем рекорд при старте игры
            state->info->high_score = load_high_score();
            state->state = Init;
            break;
        case Terminate:
            // Сохраняем рекорд при выходе, если текущий рекорд побит
            if (state->info->score > state->info->high_score) {
                state->info->high_score = state->info->score;
                save_high_score(state->info->high_score);
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
            state->info->pause = !state->info->pause;
            break;
        default:
            break;
    }   
}

GameInfo_t updateCurrentState() {
    LOG_FUNCTION_START("updateCurrentState", "");
    
    GameState_t* state = get_game_state();

    state->frame_count++;
    
    // Обновляем логику игры только если игра не на паузе (кроме GameOver)
    if (!state->info->pause || state->state == GameOver) {
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

    // Подготовка данных для отображения
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            state->info->field[i][j] = state->field[i][j];
        }
    }

    // Накладываем активную фигуру на поле
    Figure_t* fig = &state->curr;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (fig->mtrx[i][j]) {
                int x = fig->x + j;
                int y = fig->y + i;
                if (y >= 0 && y < FIELD_HEIGHT && x >= 0 && x < FIELD_WIDTH) {
                    state->info->field[y][x] = 1;  // активная фигура
                }
            }
        }
    }

    // Копируем next
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state->info->next[i][j] = state->next.mtrx[i][j];
        }
    }

    LOG_FUNCTION_END("updateCurrentState", "score=%d, level=%d, state=%d", 
                     state->info->score, state->info->level, state->state);
    
    return *state->info;
}