#include "01_automato.h"

void do_attaching(void) {
    GameState_t* state = get_game_state();
    long long current_time = get_current_time_ms();
    
    // Если только что вошли в Attaching - размещаем фигуру и запускаем таймер
    if (!state->attach_completed) {
        // Первый вход в Attaching
        if (state->attach_start_time == 0) {
            place_figure();
            clear_lines();
            state->attach_start_time = current_time;
            state->attach_completed = 0;
        }
        
        // Проверяем, прошло ли 350мс
        if (current_time - state->attach_start_time >= ATTACH_DELAY_MS) {
            state->attach_completed = 1;
            state->attach_start_time = 0;  // Сбрасываем таймер
            
            // Проверяем game over и переходим
            int game_over = is_game_over();
            
            if (game_over) {
                state->state = GameOver;
            } else {
                state->state = Spawn;
            }
            
            state->attach_completed = 0;  // Сбрасываем флаг для следующего attach
        }
        // Иначе остаёмся в Attaching и ждём
    }
}

int check_collision() {
    GameState_t* state = get_game_state();
    Figure_t* fig = &state->curr;
    int collision_detected = 0;

    for (int i = 0; i < 4 && !collision_detected; ++i) {
        for (int j = 0; j < 4 && !collision_detected; ++j) {
            if (fig->mtrx[i][j]) {
                int x = fig->x + j;
                int y = fig->y + i;

                int out_of_bounds = (x < 0 || x >= FIELD_WIDTH || y >= FIELD_HEIGHT);
                int hits_placed_block = (y >= 0 && state->field[y][x]);
                
                if (out_of_bounds || hits_placed_block) {
                    collision_detected = 1;
                }
            }
        }
    }
    
    return collision_detected;
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
                    state->field[y][x] = 2;
                }
            }
        }
    }
}

void shift_lines_down(int from_row) {
    GameState_t* state = get_game_state();
    for (int y = from_row; y > 0; --y) {
        for (int x = 0; x < FIELD_WIDTH; ++x) {
            state->field[y][x] = state->field[y - 1][x];
        }
    }
    for (int x = 0; x < FIELD_WIDTH; ++x) {
        state->field[0][x] = 0;
    }
}

void clear_lines() {
    GameState_t* state = get_game_state();
    int lines_cleared = 0;

    for (int i = FIELD_HEIGHT - 1; i >= 0; --i) {
        int full = 1;
        
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            if (state->field[i][j] != 2) {
                full = 0;
            }
        }
        
        if (full) {
            shift_lines_down(i);
            lines_cleared++;
            i++;
        }
    }

    if (lines_cleared > 0) {
        int points[] = {0, POINTS_ONE_LINE, POINTS_TWO_LINES, POINTS_THREE_LINES, POINTS_FOUR_LINES};
        state->info->score += points[lines_cleared];
        
        if (state->info->score > state->info->high_score) {
            state->info->high_score = state->info->score;
        }
        
        int new_level = (state->info->score / SCORE_PER_LEVEL) + 1;
        if (new_level > MAX_LEVEL) {
            new_level = MAX_LEVEL;
        }
        
        if (new_level > state->info->level) {
            state->info->level = new_level;
            state->info->speed = new_level + (new_level / 2);
        }
    }
}
