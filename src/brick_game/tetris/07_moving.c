#include "01_automato.h"

void do_moving(void) {
    GameState_t* state = get_game_state();

    switch (state->moving_type) {
        case LeftDown:
        case RightDown:
        case (Rotate): {
            Figure_t old = state->curr;
            switch (state->moving_type) {
                case LeftDown:
                    state->curr.x--;
                    break;
                case RightDown:
                    state->curr.x++;
                    break;
                case Rotate:
                    state->curr.rotation = (state->curr.rotation + 1) % 4;
                    const int (*shape)[4] = get_figure_shape(state->curr.sprite, state->curr.rotation);
                    for (int i = 0; i < 4; ++i)
                        for (int j = 0; j < 4; ++j)
                            state->curr.mtrx[i][j] = shape[i][j];
                    break;
                default:
                    break;
            }
            if (check_collision()) {
                state->curr = old;
            }
            state->state = Move;
            break;
        }
        case ToDown:
            while (!check_collision()) {
                state->curr.y++;
            }
            state->curr.y--;
            state->state = Attaching;
            break;

        case DoNothing:
            state->state = Move;
            break;
    }
    state->state = Move;
}