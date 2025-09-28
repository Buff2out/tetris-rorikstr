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

    timeout(100);

    int ch;
    UserAction_t current_action;
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

        updateCurrentState();
        display_game();
    }

    // Вызов userInput с Terminate для освобождения памяти
    userInput(Terminate, false);
    endwin();
    return 0;
}