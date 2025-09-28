#include "tetris.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static GameInfo_t* get_game_info_instance() {
    static GameInfo_t instance = {0};
    static bool initialized = false;
    
    if (!initialized) {
        instance.field = malloc(FIELD_HEIGHT * sizeof(int*));
        for (int i = 0; i < FIELD_HEIGHT; i++) {
            instance.field[i] = malloc(FIELD_WIDTH * sizeof(int));
        }
        
        instance.next = malloc(4 * sizeof(int*));
        for (int i = 0; i < 4; i++) {
            instance.next[i] = malloc(4 * sizeof(int));
        }
        
        // Инициализация полей
        for (int i = 0; i < FIELD_HEIGHT; i++) {
            for (int j = 0; j < FIELD_WIDTH; j++) {
                instance.field[i][j] = 0;
            }
        }
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                instance.next[i][j] = 0;
            }
        }
        
        initialized = true;
    }
    
    return &instance;
}

void userInput(UserAction_t action, bool hold) {
    GameStateData* state = get_game_state();
    GameInfo_t* game_info = get_game_info_instance();

    switch (action) {
        case Terminate:
            // Освобождаем память при завершении
            if (game_info->field != NULL) {
                for (int i = 0; i < FIELD_HEIGHT; i++) {
                    if (game_info->field[i] != NULL) {
                        free(game_info->field[i]);
                        game_info->field[i] = NULL;
                    }
                }
                free(game_info->field);
                game_info->field = NULL;
            }
            
            if (game_info->next != NULL) {
                for (int i = 0; i < 4; i++) {
                    if (game_info->next[i] != NULL) {
                        free(game_info->next[i]);
                        game_info->next[i] = NULL;
                    }
                }
                free(game_info->next);
                game_info->next = NULL;
            }
            return; // ВАЖНО: выходим из функции, не делаем ничего после Terminate

        case Start:
            if (state->state == FSM_GameOver) {
                // Перезапуск игры после Game Over
                int saved_high_score = state->high_score;
                init_game();
                state->high_score = saved_high_score;
                // Не меняем состояние, пусть остается в Start до следующего нажатия
            } else if (state->state == FSM_Start) {
                // Начинаем игру из состояния Start
                state->state = FSM_Spawn;
            } else {
                // Для всех других состояний (Moving, Move) - ставим на паузу
                state->paused = !state->paused;
            }
            break;
                    
        case Pause:
            state->paused = !state->paused;
            break;

        default:
            if (state->state == FSM_GameOver || state->paused || state->state == FSM_Start) {
                break;
            }

            if ((state->state == FSM_Moving || state->state == FSM_Move) && !state->game_over) {
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
                    case Action:
                        if (hold) {
                            // Быстрый сброс вниз
                            while (!check_collision()) {
                                state->current_figure.y++;
                            }
                            state->current_figure.y--; // Вернуть на место перед столкновением
                            state->state = FSM_Attaching;
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
            break;
    }
}

GameInfo_t updateCurrentState() {
    GameStateData* state = get_game_state();
    GameInfo_t* game_info = get_game_info_instance();
    
    if (state->state != FSM_Start && !state->game_over && !state->paused) {
        long long current_time = time(NULL) * 1000;
        
        // Определяем интервал падения в зависимости от уровня
        int drop_interval = 1000 - (state->level - 1) * 50;
        if (drop_interval < 100) drop_interval = 100; // Минимальный интервал
        
        if (current_time - state->drop_time >= drop_interval) {
            state->state = FSM_Move; // Переходим к автоматическому движению
            state->drop_time = current_time;
        }
    }
    
    // Выполняем переходы FSM (но не в состоянии Start)
    if (state->state != FSM_Start) {
        fsm_transition();
    }
    
    // Обновляем game_info.field из state->game_field
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            game_info->field[i][j] = state->game_field[i][j];
        }
    }
    
    // Добавляем активную фигуру на поле для отображения (если не в Start или GameOver)
    if ((state->state == FSM_Moving || state->state == FSM_Move) && !state->game_over) {
        Figure* f = &state->current_figure;
        const int (*shape)[4] = get_figure_shape(f->type, f->rotation);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (shape[i][j]) {
                    int x = f->x + j;
                    int y = f->y + i;
                    // Проверяем границы перед записью
                    if (x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT) {
                        // Не перезаписываем уже зафиксированные блоки
                        if (state->game_field[y][x] == 0) {
                            game_info->field[y][x] = 1;
                        }
                    }
                }
            }
        }
    }
    
    // Обновляем next
    const int (*next_shape)[4];
    if (state->state == FSM_GameOver || state->state == FSM_Start) {
        // При game_over или в начальном состоянии показываем пустую фигуру
        next_shape = empty_fig();
    } else {
        next_shape = get_figure_shape(state->next_figure.type, state->next_figure.rotation);
    }
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            game_info->next[i][j] = next_shape[i][j];
        }
    }
    
    // Обновляем остальные поля
    game_info->score = state->score;
    game_info->high_score = state->high_score;
    game_info->level = state->level;
    game_info->speed = 0; // Заглушка
    game_info->pause = state->paused ? 1 : 0;
    
    return *game_info;
}