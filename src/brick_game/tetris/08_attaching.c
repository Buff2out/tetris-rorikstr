#include "01_automato.h"

void do_attaching(void) {
    GameState_t* state = get_game_state();
    // Закрепляем фигуру на поле
    place_figure_on_field();

    // Удаляем линии
    clear_lines();

    // Проверяем GameOver
    if (is_game_over()) {
        state->state = GameOver;
        return;
    }

    // Переход в Spawn
    state->state = Spawn;
}