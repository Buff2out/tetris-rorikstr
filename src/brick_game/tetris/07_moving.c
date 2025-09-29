#include "01_automato.h"
#include "../../logging.h"

void do_moving(void) {
    GameState_t* state = get_game_state();
    LOG_FUNCTION_START("do_moving", "moving_type=%d", state->moving_type);

    switch (state->moving_type) {
        case LeftDown:
        case RightDown:
        case Rotate:
            // Обработка движения/поворота
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
                state->curr = old;  // откат
            }
            state->state = Move;
            break;

        case ToDown:
            // Мгновенное падение: двигаем вниз, пока не упрёмся
            while (!check_collision()) {
                state->curr.y++;
            }
            state->curr.y--;  // откат на 1 назад, чтобы убрать последний шаг, вызвавший коллизию
            state->state = Attaching;  // сразу в Attaching
            break;

        case DoNothing:
            state->state = Move;
            break;
    }
    
    LOG_FUNCTION_END("do_moving", "curr=(%d,%d), state=%d", 
                     state->curr.x, state->curr.y, state->state);
}