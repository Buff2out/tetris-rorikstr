#include "test_helper.h"

START_TEST(test_generate_figure) {
  generate_next_figure();
  GameState_t *state = get_game_state();

  ck_assert(state->next.sprite >= I && state->next.sprite < FIGURE_COUNT);
  ck_assert_int_eq(state->next.rotation, 0);
}
END_TEST

START_TEST(test_all_shapes_exist) {
  for (int sprite = I; sprite < FIGURE_COUNT; sprite++) {
    for (int rotation = 0; rotation < 4; rotation++) {
      const int(*shape)[4] = get_figure_shape(sprite, rotation);
      ck_assert_ptr_nonnull(shape);
    }
  }
}
END_TEST

START_TEST(test_i_figure_horizontal) {
  const int(*shape)[4] = get_figure_shape(I, 0);

  int count = 0;
  for (int j = 0; j < 4; j++) {
    if (shape[1][j])
      count++;
  }
  ck_assert_int_eq(count, 4);
}
END_TEST

START_TEST(test_o_figure_unchanged) {
  const int(*s1)[4] = get_figure_shape(O, 0);
  const int(*s2)[4] = get_figure_shape(O, 2);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(s1[i][j], s2[i][j]);
    }
  }
}
END_TEST

Suite *figures_suite(void) {
  Suite *s = suite_create("Figures");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_generate_figure);
  tcase_add_test(tc, test_all_shapes_exist);
  tcase_add_test(tc, test_i_figure_horizontal);
  tcase_add_test(tc, test_o_figure_unchanged);

  suite_add_tcase(s, tc);
  return s;
}
