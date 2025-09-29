#ifndef AUTOMATO_H
#define AUTOMATO_H

#include "00_tetris.h"
#include <stdbool.h>
#include <stdlib.h>

typedef enum {
    Init,
    Spawn,
    Moving,
    Move,
    Attaching,
    GameOver
} Automato_t;

typedef enum {
    RightDown,
    LeftDown,
    Rotate,
    ToDown,
    DoNothing
} Moving_t;

typedef enum {
    I = 0,
    J,
    L,
    O,
    S,
    T,
    Z,
    FIGURE_COUNT
} Sprite_t;

typedef struct {
    int x, y;           // Позиция фигуры на поле
    int mtrx[4][4];     // сама матрица
    Sprite_t sprite;    // Тип фигуры
    int rotation;       // Поворот (0–3)
} Figure_t;

typedef struct {
    Figure_t curr;
    Figure_t next;
    Automato_t state;
    Moving_t moving_type;
    int field[FIELD_HEIGHT][FIELD_WIDTH];
    GameInfo_t* info;
    long long frame_count;  // Общий счётчик кадров
    long long last_move_frame;  // Кадр, когда фигура последний раз двигалась
} GameState_t;

GameState_t* get_game_state(void);

// Функции состояний
// init
void do_init(void);
int load_high_score();
void save_high_score(int score);

// spawn
void do_spawn(void);

// move
void do_move(void);

//moving
void do_moving(void);

// attaching
void do_attaching(void);
int check_collision();
void place_figure();
void clear_lines();

// gameover
void do_gameover(void);
int is_game_over();


// Функции фигур
const int (*get_figure_shape(Sprite_t sprite, int rotation))[4];

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