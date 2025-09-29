// src/gui/cli/display.c
#include <ncurses.h>
#include "../../brick_game/tetris/00_tetris.h"
#include "../../logging.h"

// display.c
void display_game(GameInfo_t game_state) {
    LOG_FUNCTION_START("display_game", "");
    
    clear();

    // Отображение игрового поля (всегда, даже во время паузы)
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            if (game_state.field[i][j] == 2) {
                mvaddch(i + 1, j * 2 + 1, '#');  // Закрепленные блоки
            } else if (game_state.field[i][j] == 1) {
                mvaddch(i + 1, j * 2 + 1, '$');  // Активная фигура
            } else {
                mvaddch(i + 1, j * 2 + 1, '.');  // Пустые ячейки
            }
        }
    }

    // Отображение следующей фигуры
    mvaddstr(1, FIELD_WIDTH * 2 + 5, "Next figure:");
    
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (game_state.next[i][j]) {
                mvaddch(i + 3, (FIELD_WIDTH * 2 + 5) + j * 2, '@');
            } else {
                mvaddch(i + 3, (FIELD_WIDTH * 2 + 5) + j * 2, ' ');
            }
        }
    }

    mvprintw(FIELD_HEIGHT + 2, 1, "Score: %d", game_state.score);
    mvprintw(FIELD_HEIGHT + 3, 1, "High Score: %d", game_state.high_score);
    mvprintw(FIELD_HEIGHT + 4, 1, "Level: %d", game_state.level);
    mvprintw(FIELD_HEIGHT + 5, 1, "Speed: %d", game_state.speed);
    
    // Показываем надпись "PAUSED" если игра на паузе
    if (game_state.pause) {
        mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH * 2 + 1, "PAUSED");
    }

    refresh();
    
    LOG_FUNCTION_END("display_game", "score=%d, level=%d, pause=%d", 
                     game_state.score, game_state.level, game_state.pause);
}