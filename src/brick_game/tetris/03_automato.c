#include "01_automato.h"
#include <stdlib.h>

GameState_t* get_game_state(void) {
    static GameState_t state = {0};
    static int initialized = 0;

    if (!initialized) {
        // Выделяем память для GameInfo_t
        state.info = malloc(sizeof(GameInfo_t));

        // Выделяем память для field
        state.info->field = malloc(FIELD_HEIGHT * sizeof(int*));
        for (int i = 0; i < FIELD_HEIGHT; i++) {
            state.info->field[i] = malloc(FIELD_WIDTH * sizeof(int));
        }

        // Выделяем память для next
        state.info->next = malloc(4 * sizeof(int*));
        for (int i = 0; i < 4; i++) {
            state.info->next[i] = malloc(4 * sizeof(int));
        }

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