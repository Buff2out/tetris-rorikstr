// src/brick_game/tetris/tetris.c
#include "tetris.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static GameStateData game_state = {0};
static bool initialized = false;

// I
const int (*i_fig_up())[4] {
    static const int shape[4][4] = {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*i_fig_right())[4] {
    static const int shape[4][4] = {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}
    };
    return (const int (*)[4])shape;
}

const int (*i_fig_down())[4] {
    static const int shape[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*i_fig_left())[4] {
    static const int shape[4][4] = {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}
    };
    return (const int (*)[4])shape;
}

// O
const int (*o_fig())[4] {
    static const int shape[4][4] = {
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

// T
const int (*t_fig_up())[4] {
    static const int shape[4][4] = {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*t_fig_right())[4] {
    static const int shape[4][4] = {
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*t_fig_down())[4] {
    static const int shape[4][4] = {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*t_fig_left())[4] {
    static const int shape[4][4] = {
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

// L
const int (*l_fig_up())[4] {
    static const int shape[4][4] = {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*l_fig_right())[4] {
    static const int shape[4][4] = {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*l_fig_down())[4] {
    static const int shape[4][4] = {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*l_fig_left())[4] {
    static const int shape[4][4] = {
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

// J
const int (*j_fig_up())[4] {
    static const int shape[4][4] = {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*j_fig_right())[4] {
    static const int shape[4][4] = {
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*j_fig_down())[4] {
    static const int shape[4][4] = {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*j_fig_left())[4] {
    static const int shape[4][4] = {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

// S
const int (*s_fig_up())[4] {
    static const int shape[4][4] = {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*s_fig_right())[4] {
    static const int shape[4][4] = {
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*s_fig_down())[4] {
    static const int shape[4][4] = {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*s_fig_left())[4] {
    static const int shape[4][4] = {
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

// Z
const int (*z_fig_up())[4] {
    static const int shape[4][4] = {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*z_fig_right())[4] {
    static const int shape[4][4] = {
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*z_fig_down())[4] {
    static const int shape[4][4] = {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*z_fig_left())[4] {
    static const int shape[4][4] = {
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    };
    return (const int (*)[4])shape;
}

const int (*get_figure_shape(FigureType type, int rotation))[4] {
    const int (*result)[4] = NULL;
    switch (type) {
        case I:
            switch (rotation % 4) {
                case 0: result =  i_fig_up(); break;
                case 1: result =  i_fig_right(); break;
                case 2: result =  i_fig_down(); break;
                case 3: result =  i_fig_left(); break;
            }
            break;
        case O:
            result =  o_fig();
            break;
        case T:
            switch (rotation % 4) {
                case 0: result =  t_fig_up(); break;
                case 1: result =  t_fig_right(); break;
                case 2: result =  t_fig_down(); break;
                case 3: result =  t_fig_left(); break;
            }
            break;
        case L:
            switch (rotation % 4) {
                case 0: result =  l_fig_up(); break;
                case 1: result =  l_fig_right(); break;
                case 2: result =  l_fig_down(); break;
                case 3: result =  l_fig_left(); break;
            }
            break;
        case J:
            switch (rotation % 4) {
                case 0: result =  j_fig_up(); break;
                case 1: result =  j_fig_right(); break;
                case 2: result =  j_fig_down(); break;
                case 3: result =  j_fig_left(); break;
            }
            break;
        case S:
            switch (rotation % 4) {
                case 0: result =  s_fig_up(); break;
                case 1: result =  s_fig_right(); break;
                case 2: result =  s_fig_down(); break;
                case 3: result =  s_fig_left(); break;
            }
            break;
        case Z:
            switch (rotation % 4) {
                case 0: result =  z_fig_up(); break;
                case 1: result =  z_fig_right(); break;
                case 2: result =  z_fig_down(); break;
                case 3: result =  z_fig_left(); break;
            }
            break;
        default: result = NULL;
    }
    return result;
}

void user_input(UserAction_t action) {
    if (!initialized) {
        memset(&game_state, 0, sizeof(game_state));
        initialized = true;
    }

    if (Figure1 <= action && action <= Figure7) {
        FigureType type = (FigureType)(action - Figure1);
        game_state.current_figure.type = type;
        game_state.current_figure.x = FIELD_WIDTH / 2 - 2;
        game_state.current_figure.y = 0;
        game_state.current_figure.rotation = 0;
        game_state.figure_active = true;
    }

    if (game_state.figure_active) {
        if (action == Left) game_state.current_figure.x--;
        if (action == Right) game_state.current_figure.x++;
        if (action == Down) game_state.current_figure.y++;
        if (action == Up) game_state.current_figure.y--;
        if (action == Rotate) {
            game_state.current_figure.rotation = (game_state.current_figure.rotation + 1) % 4;
        }
    }
}

GameStateData* get_game_state() {
    return &game_state;
}