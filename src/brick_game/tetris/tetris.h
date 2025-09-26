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
GameStateData* getGameState(void);

const int (*get_figure_shape(FigureType type, int rotation))[4];

#endif