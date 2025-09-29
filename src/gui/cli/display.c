// src/gui/cli/display.c
#include <ncurses.h>
#include "../../brick_game/tetris/00_tetris.h"

void display_game() {
    clear();

    GameInfo_t game_state = updateCurrentState();
    
    // Проверяем, является ли состояние GameOver
    if (game_state.next[0][0] == 0 && game_state.next[0][1] == 0 && game_state.next[0][2] == 0 && game_state.next[0][3] == 0) {
        mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH - 4, "GAME OVER");
        refresh();
        return;
    }

    // Проверяем pause
    if (game_state.pause) {
        mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH - 4, "PAUSED");
        refresh();
        return;
    }

    // Отображение игрового поля
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
    
    if (game_state.pause) {
        mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH - 4, "PAUSED");
    }

    refresh();
    printf("DEBUG: display_game completed\n");
}