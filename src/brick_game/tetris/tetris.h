#ifndef TETRIS_H
#define TETRIS_H

#include <stdint.h>
#include <stdbool.h>

// Константы
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define NEXT_SIZE 4

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

// Состояния конечного автомата
typedef enum {
    START,
    SPAWN,
    MOVING,
    SHIFTING,
    ATTACHING,
    GAME_OVER
} GameState;

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
    Figure next_figure;                    // Следующая фигура
    int score;                             // Текущие очки
    int high_score;                        // Максимальные очки
    int level;                             // Уровень
    int lines_cleared;                     // Удалённые линии
    GameState state;                       // Текущее состояние КА
    bool paused;                           // Игра на паузе?
} GameStateData;

// Ввод пользователя
typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,      // не используется
    Down,
    Action   // вращение
} UserAction_t;

// Основные функции библиотеки
void userInput(UserAction_t action, bool hold);
GameStateData* getGameState(void);
void updateCurrentState(void);

#endif