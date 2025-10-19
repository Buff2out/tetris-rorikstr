#include <check.h>
#include "test_helper.h"

START_TEST(test_clear_one_line) {
    test_setup();
    fill_line(FIELD_HEIGHT - 1);
    
    clear_lines();
    
    ck_assert_int_eq(get_game_state()->info->score, 100);
}
END_TEST

START_TEST(test_clear_two_lines) {
    test_setup();
    fill_line(FIELD_HEIGHT - 1);
    fill_line(FIELD_HEIGHT - 2);
    
    clear_lines();
    
    ck_assert_int_eq(get_game_state()->info->score, 300);
}
END_TEST

START_TEST(test_clear_three_lines) {
    test_setup();
    fill_line(FIELD_HEIGHT - 1);
    fill_line(FIELD_HEIGHT - 2);
    fill_line(FIELD_HEIGHT - 3);
    
    clear_lines();
    
    ck_assert_int_eq(get_game_state()->info->score, 700);
}
END_TEST

START_TEST(test_clear_four_lines) {
    test_setup();
    fill_line(FIELD_HEIGHT - 1);
    fill_line(FIELD_HEIGHT - 2);
    fill_line(FIELD_HEIGHT - 3);
    fill_line(FIELD_HEIGHT - 4);
    
    clear_lines();
    
    ck_assert_int_eq(get_game_state()->info->score, 1500);
}
END_TEST

START_TEST(test_incomplete_line) {
    test_setup();
    GameState_t* state = get_game_state();
    
    // Не полная линия
    for (int j = 0; j < FIELD_WIDTH - 1; j++) {
        state->field[FIELD_HEIGHT - 1][j] = 2;
    }
    
    clear_lines();
    
    ck_assert_int_eq(state->info->score, 0);
}
END_TEST

Suite* lines_suite(void) {
    Suite* s = suite_create("ClearLines");
    TCase* tc = tcase_create("Core");
    
    tcase_add_test(tc, test_clear_one_line);
    tcase_add_test(tc, test_clear_two_lines);
    tcase_add_test(tc, test_clear_three_lines);
    tcase_add_test(tc, test_clear_four_lines);
    tcase_add_test(tc, test_incomplete_line);
    
    suite_add_tcase(s, tc);
    return s;
}
