#include "tetris.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// static bool initialized = false;

static GameStateData* get_instance() {
    static GameStateData instance = {0};
    static bool initialized_local = false;
    
    if (!initialized_local) {
        // Инициализация экземпляра
        for (int i = 0; i < FIELD_HEIGHT; i++) {
            for (int j = 0; j < FIELD_WIDTH; j++) {
                instance.game_field[i][j] = 0;
            }
        }
        instance.score = 0;
        instance.high_score = 0;
        instance.level = 1;
        instance.speed = 1000;
        instance.figure_active = false;
        instance.game_over = false;
        instance.paused = false;
        initialized_local = true;
    }
    
    return &instance;
}

void init_game() {
    GameStateData* state = get_instance();
    
    // Инициализация игрового поля
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            state->game_field[i][j] = 0;
        }
    }
    
    srand((unsigned int)time(NULL));
    
    state->current_figure.type = get_random_figure();
    state->current_figure.x = FIELD_WIDTH / 2 - 2;
    state->current_figure.y = 0;
    state->current_figure.rotation = 0;
    
    state->next_figure.type = get_random_figure();
    state->next_figure.x = 0;
    state->next_figure.y = 0;
    state->next_figure.rotation = 0;
    
    state->figure_active = true;
    state->score = 0;
    state->high_score = 0;  // Позже можно загружать из файла
    state->level = 1;
    state->speed = 1000;
    state->drop_time = time(NULL) * 1000;
    state->game_over = false;
    state->paused = false;
}

static void clear_completed_lines() {
    GameStateData* state = get_instance();
    int lines_cleared = 0;
    int write_row = FIELD_HEIGHT - 1;
    
    // Проходим снизу вверх
    for (int read_row = FIELD_HEIGHT - 1; read_row >= 0; read_row--) {
        bool line_complete = true;
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (state->game_field[read_row][j] == 0) {
                line_complete = false;
                break;
            }
        }
        
        if (line_complete) {
            lines_cleared++;
        } else {
            // Копируем неполные строки вниз
            if (write_row != read_row) {
                for (int j = 0; j < FIELD_WIDTH; j++) {
                    state->game_field[write_row][j] = state->game_field[read_row][j];
                }
            }
            write_row--;
        }
    }
    
    // Заполняем пустые строки наверху
    for (int i = 0; i <= write_row; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            state->game_field[i][j] = 0;
        }
    }
    
    if (lines_cleared > 0) {
        // Обновляем счет в соответствии с количеством очищенных линий
        int points[] = {0, 100, 300, 700, 1500}; // 0, 1, 2, 3, 4 линии
        int score_points = 0;
        if (lines_cleared <= 4) {
            score_points = points[lines_cleared];
        } else {
            score_points = points[4]; // для > 4 линий
        }
        state->score += score_points * state->level;
        
        if (state->score > state->high_score) {
            state->high_score = state->score;
        }
        
        // Увеличиваем уровень каждые 600 очков, максимум 10
        int new_level = state->score / 600 + 1;
        if (new_level > 10) new_level = 10;
        if (new_level != state->level) {
            state->level = new_level;
            // Увеличиваем скорость (уменьшаем время падения)
            state->speed = 1000 - (state->level - 1) * 50;
            if (state->speed < 100) state->speed = 100;
        }
    }
}

int get_random_figure() {
    return rand() % FIGURE_COUNT;
}

bool check_collision() {
    GameStateData* state = get_instance();
    Figure* f = &state->current_figure;
    const int (*shape)[4] = get_figure_shape(f->type, f->rotation);
    bool collision = false;
    
    for (int i = 0; !collision && i < 4; i++) {
        for (int j = 0; !collision && j < 4; j++) {
            if (shape[i][j]) {
                int x = f->x + j;
                int y = f->y + i;
                
                if (x < 0 || x >= FIELD_WIDTH || y >= FIELD_HEIGHT 
                    || (y >= 0 && state->game_field[y][x] != 0)) {
                    collision = true;
                }
            }
        }
    }
    return collision;
}

void place_figure() {
    GameStateData* state = get_instance();
    Figure* f = &state->current_figure;
    const int (*shape)[4] = get_figure_shape(f->type, f->rotation);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j]) {
                int x = f->x + j;
                int y = f->y + i;
                if (y >= 0 && y < FIELD_HEIGHT && x >= 0 && x < FIELD_WIDTH) {
                    state->game_field[y][x] = 1;
                }
            }
        }
    }
    
    // Проверяем и удаляем заполненные строки
    clear_completed_lines();
    
    // Сгенерировать новую текущую фигуру из следующей
    state->current_figure = state->next_figure;
    state->current_figure.x = FIELD_WIDTH / 2 - 2;
    state->current_figure.y = 0;
    state->current_figure.rotation = 0;
    
    // Сгенерировать новую следующую фигуру
    state->next_figure.type = get_random_figure();
    state->next_figure.rotation = 0;
    
    // Проверить, возможно ли размещение новой фигуры
    if (check_collision()) {
        state->game_over = true;
    }
}

void update_game_state() {
    GameStateData* state = get_instance();
    
    if (state->game_over) {
        return;
    }
    
    // Проверка времени для автоматического падения
    long long current_time = time(NULL) * 1000; // в миллисекундах
    if (current_time - state->drop_time >= state->speed) {
        // Попробовать сдвинуть фигуру вниз
        int old_y = state->current_figure.y;
        state->current_figure.y++;
        
        if (check_collision()) {
            // Если столкновение, вернуть позицию и зафиксировать фигуру
            state->current_figure.y = old_y;
            place_figure();
        } else {
            state->drop_time = current_time;
        }
    }
}

GameStateData* get_game_state() {
    return get_instance();
}