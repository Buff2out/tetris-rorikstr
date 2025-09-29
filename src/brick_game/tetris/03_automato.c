#include "01_automato.h"

int load_high_score() {
    FILE* file = fopen("high_score.txt", "r");
    int high_score = 0;
    if (file) {
        if (fscanf(file, "%d", &high_score) != 1) {
            high_score = 0;
        }
        fclose(file);
    }
    return high_score;
}

void save_high_score(int score) {
    FILE* file = fopen("high_score.txt", "w");
    if (file) {
        fprintf(file, "%d", score);
        fclose(file);
    }
}

GameState_t* get_game_state(void) {
    static GameState_t state = {0};
    static int initialized = 0;

    if (!initialized) {
        state.info = malloc(sizeof(GameInfo_t));
        state.info->field = malloc(FIELD_HEIGHT * sizeof(int*));
        for (int i = 0; i < FIELD_HEIGHT; i++) {
            state.info->field[i] = malloc(FIELD_WIDTH * sizeof(int));
        }

        state.info->next = malloc(4 * sizeof(int*));
        for (int i = 0; i < 4; i++) {
            state.info->next[i] = malloc(4 * sizeof(int));
        }
        state.info->speed = 10;
        state.info->score = 0;
        state.info->level = 1;
        state.info->pause = 0;
        state.frame_count = 0;
        state.last_move_frame = 0;
        state.info->high_score = load_high_score();

        state.state = GameOver;
        initialized = 1;
    }
    
    return &state;
}

void terminate_and_free() {
    GameState_t* state = get_game_state();

    if (state->info) {
        if (state->info->field != NULL) {
            for (int i = 0; i < FIELD_HEIGHT; i++) {
                if (state->info->field[i] != NULL) {
                    free(state->info->field[i]);
                    state->info->field[i] = NULL;
                }
            }
            free(state->info->field);
            state->info->field = NULL;
        }

        if (state->info->next != NULL) {
            for (int i = 0; i < 4; i++) {
                if (state->info->next[i] != NULL) {
                    free(state->info->next[i]);
                    state->info->next[i] = NULL;
                }
            }
            free(state->info->next);
            state->info->next = NULL;
        }

        free(state->info);
        state->info = NULL;
    }
}