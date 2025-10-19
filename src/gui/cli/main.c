#include "../../brick_game/tetris/00_tetris.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void display_game(GameInfo_t game_state);

int main() {
  srand(time(NULL));

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, FALSE);
  curs_set(0);

  mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH - 4, "Press F to Start");
  refresh();

  int ch = 0;
  int started = 0;
  while (!started) {
    ch = getch();
    if (ch == 'f' || ch == 'F') {
      userInput(Start, false);
      started = 1;
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

    if (ch == 'q') {
      userInput(Terminate, false);
      running = false;
    } else if (ch == 'r' || ch == ' ') {
      current_action = Action;
      action_valid = true;
    } else if (ch == KEY_LEFT) {
      current_action = Left;
      action_valid = true;
    } else if (ch == KEY_RIGHT) {
      current_action = Right;
      action_valid = true;
    } else if (ch == KEY_DOWN) {
      current_action = Down;
      action_valid = true;
    } else if (ch == KEY_UP) {
      current_action = Up;
      action_valid = true;
    } else if (ch == 's' || ch == 'S') {
      current_action = Start;
      action_valid = true;
    } else if (ch == 'p' || ch == 'P') {
      current_action = Pause;
      action_valid = true;
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
