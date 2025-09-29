#include "01_automato.h"

void do_attaching(void) {
    GameState_t* state = get_game_state();
    place_figure();
    clear_lines();
    if (is_game_over()) {
        state->state = GameOver;
    } else {
        state->state = Spawn;
    }
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
                    return 1;
                }
                if (y >= 0 && state->field[y][x]) {
                    return 1;
                }
            }
        }
    }
    return 0;
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
            for (int y = i; y > 0; --y) {
                for (int x = 0; x < FIELD_WIDTH; ++x) {
                    state->field[y][x] = state->field[y - 1][x];
                }
            }
            for (int x = 0; x < FIELD_WIDTH; ++x) {
                state->field[0][x] = 0;
            }
            lines_cleared++;
            i++;
        }
    }

    if (lines_cleared > 0) {
        int points[] = {0, 100, 300, 700, 1500};
        state->info->score += points[lines_cleared];
        if (state->info->score > state->info->high_score) {
            state->info->high_score = state->info->score;
        }
        int new_level = (state->info->score / 600) + 1;
        if (new_level > 10) new_level = 10;
        
        if (new_level > state->info->level) {
            state->info->level = new_level;
            
            state->info->speed = new_level * 10;
            return;
        }
    }
}