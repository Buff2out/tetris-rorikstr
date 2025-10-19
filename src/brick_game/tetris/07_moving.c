#include "01_automato.h"

void handle_move_direction(Moving_t direction) {
  GameState_t *state = get_game_state();
  switch (direction) {
  case LeftDown:
    state->curr.x--;
    break;
  case RightDown:
    state->curr.x++;
    break;
  default:
    break;
  }
}

void handle_rotate(void) {
  GameState_t *state = get_game_state();
  state->curr.rotation = (state->curr.rotation + 1) % 4;
  const int(*shape)[4] =
      get_figure_shape(state->curr.sprite, state->curr.rotation);
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      state->curr.mtrx[i][j] = shape[i][j];
}

void handle_horizontal_rotate_move(void) {
  GameState_t *state = get_game_state();
  Figure_t old = state->curr;

  switch (state->moving_type) {
  case LeftDown:
  case RightDown:
    handle_move_direction(state->moving_type);
    break;
  case Rotate:
    handle_rotate();
    break;
  default:
    break;
  }

  if (check_collision()) {
    state->curr = old;
  }
  state->state = Move;
}

void handle_to_down_move(void) {
  GameState_t *state = get_game_state();
  while (!check_collision()) {
    state->curr.y++;
  }
  state->curr.y--;
  state->state = Attaching;
}

void do_moving(void) {
  GameState_t *state = get_game_state();

  switch (state->moving_type) {
  case LeftDown:
  case RightDown:
  case Rotate:
    handle_horizontal_rotate_move();
    break;
  case ToDown:
    handle_to_down_move();
    break;
  case DoNothing:
    state->state = Move;
    break;
  }
}