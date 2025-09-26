// src/brick_game/tetris/tetris.h
#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
#include <stdint.h>

// Константы
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

// Типы фигур
typedef enum {
    I = 0,
    J,
    L,
    O,
    S,
    T,
    Z,
    FIGURE_COUNT
} FigureType;

// Структура фигуры
typedef struct {
    int x, y;           // Позиция фигуры на поле
    FigureType type;    // Тип фигуры
    int rotation;       // Поворот (0–3)
} Figure;

// Структура состояния игры
typedef struct {
    int field[FIELD_HEIGHT][FIELD_WIDTH];  // Игровое поле
    Figure current_figure;                 // Текущая фигура
    bool figure_active;                    // Есть активная фигура?
} GameStateData;

// Ввод пользователя
typedef enum {
    Undefined = -1,
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Rotate,
    Action,
    Figure1,
    Figure2,
    Figure3,
    Figure4,
    Figure5,
    Figure6,
    Figure7
} UserAction_t;

// Основные функции библиотеки
void user_input(UserAction_t action);
static bool check_collision();
GameStateData* get_game_state(void);

const int (*get_figure_shape(FigureType type, int rotation))[4];

const int (*i_fig_up())[4];
const int (*i_fig_right())[4];
const int (*i_fig_down())[4];
const int (*i_fig_left())[4];

const int (*o_fig())[4];

const int (*t_fig_up())[4];
const int (*t_fig_right())[4];
const int (*t_fig_down())[4];
const int (*t_fig_left())[4];

const int (*l_fig_up())[4];
const int (*l_fig_right())[4];
const int (*l_fig_down())[4];
const int (*l_fig_left())[4];

const int (*j_fig_up())[4];
const int (*j_fig_right())[4];
const int (*j_fig_down())[4];
const int (*j_fig_left())[4];

const int (*s_fig_up())[4];
const int (*s_fig_right())[4];
const int (*s_fig_down())[4];
const int (*s_fig_left())[4];

const int (*z_fig_up())[4];
const int (*z_fig_right())[4];
const int (*z_fig_down())[4];
const int (*z_fig_left())[4];

#endif