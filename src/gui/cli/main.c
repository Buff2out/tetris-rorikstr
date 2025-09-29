#include <ncurses.h>
#include <unistd.h>
#include "../../brick_game/tetris/00_tetris.h"

void display_game(GameInfo_t game_state);

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);
    curs_set(0);

    // Цикл ожидания нажатия F/f
    mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH - 4, "Press F to Start");
    refresh();

    int ch = 0;
    while (1) {
        ch = getch();
        if (ch == 'f' || ch == 'F') {
            userInput(Start, false);
            break;
        }
    }

    nodelay(stdscr, TRUE);
    timeout(10);

    UserAction_t current_action = {0};
    bool action_valid = false;
    bool running = true;
    
    while (running) {
        ch = getch();
        action_valid = false;

        switch (ch) {
            case 'q': 
                userInput(Terminate, false);
                running = false;
                break;
            case 'r': case ' ': 
                current_action = Action; 
                action_valid = true; 
                break;
            case KEY_LEFT: 
                current_action = Left; 
                action_valid = true; 
                break;
            case KEY_RIGHT: 
                current_action = Right; 
                action_valid = true; 
                break;
            case KEY_DOWN: 
                current_action = Down; 
                action_valid = true; 
                break;
            case KEY_UP: 
                current_action = Up; 
                action_valid = true; 
                break;
            case 's': case 'S': 
                current_action = Start; 
                action_valid = true; 
                break;
            case 'p': case 'P': 
                current_action = Pause; 
                action_valid = true; 
                break;
        }
        
        if (action_valid) {
            userInput(current_action, false);
        }

        if (running) {
            GameInfo_t game_state = updateCurrentState();
            display_game(game_state);
        }
    }

    endwin();
    return 0;
}