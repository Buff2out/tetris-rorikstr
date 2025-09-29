#include "01_automato.h"
#include <stdlib.h>
#include "../../logging.h"

GameState_t* get_game_state(void) {
    LOG_FUNCTION_START("get_game_state", "");
    
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

        // Инициализируем начальные значения
        state.info->speed = 1;
        state.info->score = 0;
        state.info->level = 1;
        state.info->pause = 0;
        
        // Инициализируем следующую фигуру
        state.next.sprite = rand() % FIGURE_COUNT;
        state.next.rotation = 0;
        const int (*shape)[4] = get_figure_shape(state.next.sprite, 0);
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                state.next.mtrx[i][j] = shape[i][j];

        state.state = GameOver;
        initialized = 1;
    }
    
    LOG_FUNCTION_END("get_game_state", "state=%d", state.state);
    return &state;
}

void terminate_and_free() {
    LOG_FUNCTION_START("terminate_and_free", "");
    
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
    
    LOG_FUNCTION_END("terminate_and_free", "");
}