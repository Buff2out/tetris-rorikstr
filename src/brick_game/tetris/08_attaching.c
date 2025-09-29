#include "01_automato.h"
#include "../../logging.h"

void do_attaching(void) {
    GameState_t* state = get_game_state();
    // Закрепляем фигуру на поле
    place_figure();

    // Удаляем линии
    clear_lines();

    // Проверяем GameOver
    if (is_game_over()) {
        state->state = GameOver;
    } else {
        state->state = Spawn;
    }
    
    LOG_FUNCTION_END("do_attaching", "state=%d", state->state);
}

int check_collision() {
    GameState_t* state = get_game_state();
    Figure_t* fig = &state->curr;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (fig->mtrx[i][j]) {
                int x = fig->x + j;
                int y = fig->y + i;

                if (x < 0 || x >= FIELD_WIDTH || y >= FIELD_HEIGHT) {
                    return 1;  // коллизия
                }
                if (y >= 0 && state->field[y][x]) {
                    return 1;  // коллизия с другой фигурой
                }
            }
        }
    }
    
    LOG_FUNCTION_END("check_collision", "no collision");
    return 0;  // нет коллизии
}

void place_figure() {
    
    GameState_t* state = get_game_state();
    Figure_t* fig = &state->curr;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (fig->mtrx[i][j]) {
                int x = fig->x + j;
                int y = fig->y + i;
                if (y >= 0 && y < FIELD_HEIGHT && x >= 0 && x < FIELD_WIDTH) {
                    state->field[y][x] = 2;  // закреплённая фигура
                }
            }
        }
    }
}

void clear_lines() {
    
    GameState_t* state = get_game_state();
    int old_level = state->info->level;
    int old_speed = state->info->speed;
    
    int lines_cleared = 0;

    for (int i = FIELD_HEIGHT - 1; i >= 0; --i) {
        int full = 1;
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            if (state->field[i][j] != 2) {
                full = 0;
                break;
            }
        }
        if (full) {
            // Сдвигаем строки вниз
            for (int y = i; y > 0; --y) {
                for (int x = 0; x < FIELD_WIDTH; ++x) {
                    state->field[y][x] = state->field[y - 1][x];
                }
            }
            // Очищаем верхнюю строку
            for (int x = 0; x < FIELD_WIDTH; ++x) {
                state->field[0][x] = 0;
            }
            lines_cleared++;
            i++;  // проверяем эту строку снова
        }
    }

    // Начисление очков
    if (lines_cleared > 0) {
        int points[] = {0, 100, 300, 700, 1500};
        int old_score = state->info->score;
        state->info->score += points[lines_cleared];
        
        // Обновляем рекорд, если нужно
        if (state->info->score > state->info->high_score) {
            state->info->high_score = state->info->score;
        }
        
        // Увеличиваем уровень каждые 600 очков (максимум 10 уровней)
        int new_level = (state->info->score / 600) + 1;
        if (new_level > 10) new_level = 10;
        
        if (new_level > state->info->level) {
            state->info->level = new_level;
            
            // СУПЕР-УСКОРЕНИЕ! В 50 раз быстрее!
            state->info->speed = new_level * 50;
            
            LOG_FUNCTION_END("clear_lines", "lines_cleared=%d, score=%d->%d, level=%d->%d, speed=%d->%d", 
                             lines_cleared, old_score, state->info->score, old_level, state->info->level, 
                             old_speed, state->info->speed);
            return;
        }
    }
    
    // Добавим лог, даже если линии не очищались
    LOG_FUNCTION_END("clear_lines", "lines_cleared=%d, score=%d->%d, level=%d->%d, speed=%d->%d", 
                     lines_cleared, state->info->score, state->info->score, old_level, state->info->level, 
                     old_speed, state->info->speed);
}