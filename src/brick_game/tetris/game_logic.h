#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdbool.h>
#include "tetris.h"  // для использования GameInfo_t

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

// FSM состояния
typedef enum {
    FSM_Start,
    FSM_Spawn,
    FSM_Moving,
    FSM_Move,
    FSM_Attaching,
    FSM_GameOver
} FSMState_t;

// Структура фигуры
typedef struct {
    int x, y;           // Позиция фигуры на поле
    FigureType type;    // Тип фигуры
    int rotation;       // Поворот (0–3)
} Figure;

typedef struct {
    int game_field[FIELD_HEIGHT][FIELD_WIDTH];
    Figure current_figure;
    Figure next_figure;
    FSMState_t state;
    int score;
    int high_score;
    int level;
    long long drop_time;
    bool game_over;
    bool paused;
} GameStateData;

// Внутренние функции
bool check_collision(void);
void init_game(void);
void fsm_transition(void);
int get_random_figure(void);
const int (*get_figure_shape(FigureType type, int rotation))[4];
GameStateData* get_game_state(void);
void place_figure(void);
void clear_completed_lines(void);

// Фигуры
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
const int (*empty_fig())[4];

#endif