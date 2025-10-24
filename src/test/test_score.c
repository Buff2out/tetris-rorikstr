#include "test_helper.h"

START_TEST(test_level_up) {
  test_setup();
  GameState_t *state = get_game_state();

  fill_line(FIELD_HEIGHT - 1);
  clear_lines();

  fill_line(FIELD_HEIGHT - 1);
  fill_line(FIELD_HEIGHT - 2);
  clear_lines();

  fill_line(FIELD_HEIGHT - 1);
  fill_line(FIELD_HEIGHT - 2);
  clear_lines();

  ck_assert_int_eq(state->info->level, 2);
}
END_TEST

START_TEST(test_max_level) {
  test_setup();
  GameState_t *state = get_game_state();

  state->info->score = 10000;
  fill_line(FIELD_HEIGHT - 1);
  clear_lines();

  ck_assert_int_le(state->info->level, 10);
}
END_TEST

START_TEST(test_high_score_save) {
  save_high_score(9999);
  ck_assert_int_eq(load_high_score(), 9999);
}
END_TEST

START_TEST(test_game_over_top) {
  test_setup();
  GameState_t *state = get_game_state();

  state->field[0][5] = 2;
  ck_assert_int_eq(is_game_over(), 1);
}
END_TEST

Suite *score_suite(void) {
  Suite *s = suite_create("Score");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_level_up);
  tcase_add_test(tc, test_max_level);
  tcase_add_test(tc, test_high_score_save);
  tcase_add_test(tc, test_game_over_top);

  suite_add_tcase(s, tc);
  return s;
}
