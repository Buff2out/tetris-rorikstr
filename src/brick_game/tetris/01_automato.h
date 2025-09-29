#ifndef AUTOMATO_H
#define AUTOMATO_H

#include "00_tetris.h"
#include <stdbool.h>

typedef enum {
    Init,
    Spawn,
    Moving,
    Move,
    Attaching,
    GameOver
} Automato_t;

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

typedef struct {
    int x, y;           // Позиция фигуры на поле
    int mtrx[4][4];     // сама матрица
    FigureType type;    // Тип фигуры
    int rotation;       // Поворот (0–3)
} Figure;

typedef struct {
    Figure curr;
    Figure next;
    Automato_t state;
    int field[FIELD_HEIGHT][FIELD_WIDTH];
    int score;
    int high_score;
    int level;
    int speed;
    long long last_time;
} GameState_t;

GameState_t* get_game_state(void);

// Функции состояний
void do_start(void);
void do_spawn(void);
void do_move(void);
void do_moving(void);
void do_attaching(void);
void do_gameover(void);

// Вспомогательные
void place_figure_on_field();
int check_collision();
void clear_lines();
int is_game_over();

// Функции фигур
const int (*get_figure_shape(FigureType type, int rotation))[4];

// Остальные фигуры...
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