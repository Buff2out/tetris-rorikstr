#include <check.h>
#include "test_helper.h"

START_TEST(test_collision_bottom) {
    test_setup();
    GameState_t* state = get_game_state();
    
    state->curr.y = FIELD_HEIGHT;
    state->curr.x = 5;
    state->curr.mtrx[0][0] = 1;
    
    ck_assert_int_eq(check_collision(), 1);
}
END_TEST

START_TEST(test_collision_left) {
    test_setup();
    GameState_t* state = get_game_state();
    
    state->curr.x = -1;
    state->curr.y = 5;
    state->curr.mtrx[0][0] = 1;
    
    ck_assert_int_eq(check_collision(), 1);
}
END_TEST

START_TEST(test_collision_right) {
    test_setup();
    GameState_t* state = get_game_state();
    
    state->curr.x = FIELD_WIDTH;
    state->curr.y = 5;
    state->curr.mtrx[0][0] = 1;
    
    ck_assert_int_eq(check_collision(), 1);
}
END_TEST

START_TEST(test_collision_placed_block) {
    test_setup();
    GameState_t* state = get_game_state();
    
    state->field[10][5] = 2;
    state->curr.y = 10;
    state->curr.x = 5;
    state->curr.mtrx[0][0] = 1;
    
    ck_assert_int_eq(check_collision(), 1);
}
END_TEST

START_TEST(test_no_collision) {
    test_setup();
    GameState_t* state = get_game_state();
    
    state->curr.y = 5;
    state->curr.x = 5;
    state->curr.mtrx[0][0] = 1;
    
    ck_assert_int_eq(check_collision(), 0);
}
END_TEST

Suite* collision_suite(void) {
    Suite* s = suite_create("Collision");
    TCase* tc = tcase_create("Core");
    
    tcase_add_test(tc, test_collision_bottom);
    tcase_add_test(tc, test_collision_left);
    tcase_add_test(tc, test_collision_right);
    tcase_add_test(tc, test_collision_placed_block);
    tcase_add_test(tc, test_no_collision);
    
    suite_add_tcase(s, tc);
    return s;
}
