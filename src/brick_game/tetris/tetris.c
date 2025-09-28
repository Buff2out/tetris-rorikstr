// src/brick_game/tetris/tetris.c
#include "tetris.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static GameInfo_t game_info = {0};
static bool initialized = false;  // Добавляем эту переменную

void init_game_info() {
    if (game_info.field == NULL) {
        game_info.field = malloc(FIELD_HEIGHT * sizeof(int*));
        for (int i = 0; i < FIELD_HEIGHT; i++) {
            game_info.field[i] = malloc(FIELD_WIDTH * sizeof(int));
        }
    }
    
    if (game_info.next == NULL) {
        game_info.next = malloc(4 * sizeof(int*));
        for (int i = 0; i < 4; i++) {
            game_info.next[i] = malloc(4 * sizeof(int));
        }
    }
    
    // Инициализация полей
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            game_info.field[i][j] = 0;
        }
    }
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            game_info.next[i][j] = 0;
        }
    }
}

void userInput(UserAction_t action, bool hold) {
    if (!initialized) {
        init_game_info();
        init_game();
        initialized = true;
    }
    
    GameStateData* state = get_game_state();

    if (action == Start) {
        if (state->game_over) {
            init_game(); // Перезапуск игры
        } else if (!state->paused) {
            state->paused = true;
        } else {
            state->paused = false;
        }
        return;
    }
    
    if (action == Pause) {
        state->paused = !state->paused;
        return;
    }
    
    if (action == Terminate) {
        return;
    }

    if (state->game_over || state->paused) {
        return;
    }

    if (state->figure_active && !state->game_over) {
        int old_x = state->current_figure.x;
        int old_y = state->current_figure.y;
        int old_rot = state->current_figure.rotation;

        switch (action) {
            case Left:
                state->current_figure.x--;
                break;
            case Right:
                state->current_figure.x++;
                break;
            case Down:
                state->current_figure.y++;
                break;
            case Up:
                state->current_figure.rotation = (state->current_figure.rotation + 1) % 4;
                break;
            case Action:  // Это может быть вращение или сброс
                if (hold) {
                    // Быстрый сброс вниз
                    while (!check_collision()) {
                        state->current_figure.y++;
                    }
                    state->current_figure.y--; // Вернуть на место перед столкновением
                    place_figure();
                } else {
                    state->current_figure.rotation = (state->current_figure.rotation + 1) % 4;
                }
                break;
            default:
                break;
        }

        if (check_collision()) {
            // Возвращаем старые значения
            state->current_figure.x = old_x;
            state->current_figure.y = old_y;
            state->current_figure.rotation = old_rot;
        } else if (action == Down) {
            // Если перемещение вниз успешно, обновляем время падения
            state->drop_time = time(NULL) * 1000;
        }
    }
}

GameInfo_t updateCurrentState() {
    if (!initialized) {
        init_game_info();
        init_game();
        initialized = true;
    }
    
    GameStateData* state = get_game_state();
    
    if (!state->game_over && !state->paused) {
        long long current_time = time(NULL) * 1000;
        if (current_time - state->drop_time >= state->speed) {
            int old_y = state->current_figure.y;
            state->current_figure.y++;
            
            if (check_collision()) {
                state->current_figure.y = old_y;
                place_figure();
            } else {
                state->drop_time = current_time;
            }
        }
    }
    
    // Обновляем game_info.field из state->game_field
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            game_info.field[i][j] = state->game_field[i][j];
        }
    }
    
    // Добавляем активную фигуру на поле для отображения (если не game_over)
    if (state->figure_active && !state->game_over) {
        Figure* f = &state->current_figure;
        const int (*shape)[4] = get_figure_shape(f->type, f->rotation);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (shape[i][j]) {
                    int x = f->x + j;
                    int y = f->y + i;
                    if (x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT) {
                        game_info.field[y][x] = 1;
                    }
                }
            }
        }
    }
    
    // Обновляем next
    const int (*next_shape)[4];
    if (state->game_over) {
        // При game_over показываем пустую фигуру
        next_shape = empty_fig();
    } else {
        next_shape = get_figure_shape(state->next_figure.type, state->next_figure.rotation);
    }
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            game_info.next[i][j] = next_shape[i][j];
        }
    }
    
    // Обновляем остальные поля
    game_info.score = state->score;
    game_info.high_score = state->high_score;
    game_info.level = state->level;
    game_info.speed = state->speed;
    game_info.pause = state->paused ? 1 : 0;
    
    return game_info;
}