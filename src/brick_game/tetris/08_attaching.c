#include "01_automato.h"

void do_attaching(void) {
    GameState_t* state = get_game_state();
    // Закрепляем фигуру на поле
    place_figure();

    // Удаляем линии
    clear_lines();

    // Проверяем GameOver
    int is_gameov = 0;
    if (is_game_over()) {
        state->state = GameOver;
    } else {
        state->state = Spawn;
    }
}