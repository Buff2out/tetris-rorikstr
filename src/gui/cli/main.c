// src/gui/cli/main.c
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include "../../brick_game/tetris/tetris.h"

void display_game();

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    timeout(100);  // Таймаут для getch()

    int ch;
    UserAction_t action = Undefined;
    while (action != Terminate) {
        ch = getch();
        

        switch (ch) {
            case 'q': action = Terminate; break;
            case '1': action = Figure1; break;
            case '2': action = Figure2; break;
            case '3': action = Figure3; break;
            case '4': action = Figure4; break;
            case '5': action = Figure5; break;
            case '6': action = Figure6; break;
            case '7': action = Figure7; break;
            case KEY_LEFT: action = Left; break;
            case KEY_RIGHT: action = Right; break;
            case KEY_DOWN: action = Down; break;
            case KEY_UP: action = Up; break;
        }

        if (action != Undefined) {
            user_input(action);
        }

        display_game();
    }

    endwin();
    return 0;
}