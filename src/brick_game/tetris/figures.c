#include "tetris.h"

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