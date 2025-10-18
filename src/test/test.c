#include <check.h>
#include "../brick_game/tetris/01_automato.h"

START_TEST(test_collision_bottom_boundary) {
    GameState_t* state = get_game_state();
    state->curr.y = FIELD_HEIGHT - 1;
    state->curr.x = 5;
    state->curr.mtrx[0][0] = 1;
    state->curr.y++; // Выходим за границу
    ck_assert_int_eq(check_collision(), 1);
}
END_TEST

START_TEST(test_collision_left_boundary) {
    GameState_t* state = get_game_state();
    state->curr.x = -1;
    state->curr.mtrx[0][0] = 1;
    ck_assert_int_eq(check_collision(), 1);
}
END_TEST

START_TEST(test_collision_with_placed_block) {
    GameState_t* state = get_game_state();
    state->field[10][5] = 2; // Размещённый блок
    state->curr.y = 10;
    state->curr.x = 5;
    state->curr.mtrx[0][0] = 1;
    ck_assert_int_eq(check_collision(), 1);
}
END_TEST

START_TEST(test_no_collision) {
    GameState_t* state = get_game_state();
    state->curr.y = 5;
    state->curr.x = 5;
    state->curr.mtrx[0][0] = 1;
    ck_assert_int_eq(check_collision(), 0);
}
END_TEST

START_TEST(test_game_over_detection) {
    GameState_t* state = get_game_state();
    state->field[0][5] = 2; // Блок в верхней строке
    ck_assert_int_eq(is_game_over(), 1);
}
END_TEST

START_TEST(test_clear_single_line) {
    GameState_t* state = get_game_state();
    state->info->score = 0;
    
    // Заполняем нижнюю линию
    for (int j = 0; j < FIELD_WIDTH; j++) {
        state->field[FIELD_HEIGHT - 1][j] = 2;
    }
    
    clear_lines();
    ck_assert_int_eq(state->info->score, 100);
}
END_TEST

Suite* tetris_suite(void) {
    Suite* s = suite_create("Tetris");
    TCase* tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, test_collision_bottom_boundary);
    tcase_add_test(tc_core, test_collision_left_boundary);
    tcase_add_test(tc_core, test_collision_with_placed_block);
    tcase_add_test(tc_core, test_no_collision);
    tcase_add_test(tc_core, test_game_over_detection);
    tcase_add_test(tc_core, test_clear_single_line);
    
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    Suite* s = tetris_suite();
    SRunner* sr = srunner_create(s);
    
    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? 0 : 1;
}
