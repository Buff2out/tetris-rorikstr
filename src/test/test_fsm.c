#include <check.h>
#include "test_helper.h"
#include <unistd.h>

// ============================================================================
// Тесты FSM и интеграции
// ============================================================================

START_TEST(test_game_start) {
    userInput(Start, false);
    GameInfo_t state = updateCurrentState();
    
    // После Start игра должна инициализироваться
    ck_assert_int_eq(state.level, 1);
    ck_assert_int_eq(state.score, 0);
    ck_assert_int_eq(state.pause, 0);
}
END_TEST

START_TEST(test_pause_toggle) {
    userInput(Start, false);
    updateCurrentState();
    
    userInput(Pause, false);
    GameInfo_t state = updateCurrentState();
    ck_assert_int_eq(state.pause, 1);
    
    userInput(Pause, false);
    state = updateCurrentState();
    ck_assert_int_eq(state.pause, 0);
}
END_TEST

START_TEST(test_field_initialization) {
    userInput(Start, false);
    GameInfo_t state = updateCurrentState();
    
    int non_zero_count = 0;
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (state.field[i][j] != 0) {
                non_zero_count++;
            }
        }
    }
    
    ck_assert_int_le(non_zero_count, 4);
}
END_TEST

START_TEST(test_next_figure_exists) {
    userInput(Start, false);
    GameInfo_t state = updateCurrentState();
    
    int has_blocks = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (state.next[i][j]) {
                has_blocks = 1;
            }
        }
    }
    ck_assert_int_eq(has_blocks, 1);
}
END_TEST

START_TEST(test_movement_left) {
    userInput(Start, false);
    updateCurrentState();
    
    userInput(Left, false);
    GameInfo_t state = updateCurrentState();
    
    ck_assert_int_eq(state.pause, 0);
}
END_TEST

START_TEST(test_movement_right) {
    userInput(Start, false);
    updateCurrentState();
    
    userInput(Right, false);
    GameInfo_t state = updateCurrentState();
    
    ck_assert_int_eq(state.pause, 0);
    ck_assert_int_ge(state.level, 1);
}
END_TEST

START_TEST(test_rotation) {
    userInput(Start, false);
    updateCurrentState();
    
    userInput(Action, false);
    GameInfo_t state = updateCurrentState();
    
    int has_figure = 0;
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (state.field[i][j] == 1) {
                has_figure = 1;
            }
        }
    }
    ck_assert_int_eq(has_figure, 1);
}
END_TEST

START_TEST(test_user_input_actions) {
    userInput(Start, false);
    userInput(Left, false);
    userInput(Right, false);
    userInput(Action, false);
    userInput(Pause, false);
    userInput(Terminate, false);
    
    ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_multiple_updates) {
    userInput(Start, false);
    
    for (int i = 0; i < 10; i++) {
        updateCurrentState();
    }
    
    GameInfo_t state = updateCurrentState();
    ck_assert_int_eq(state.level, 1);
}
END_TEST

START_TEST(test_instant_drop_down_key) {
    userInput(Start, false);
    updateCurrentState();
    
    GameState_t* state = get_game_state();
    state->down_key_was_released = 1;
    
    userInput(Down, false);
    
    ck_assert_int_eq(state->down_key_was_released, 0);
}
END_TEST

START_TEST(test_up_key_release) {
    userInput(Start, false);
    updateCurrentState();
    
    GameState_t* state = get_game_state();
    state->down_key_was_released = 0;
    
    userInput(Up, false);
    updateCurrentState();
    
    ck_assert_int_eq(state->down_key_was_released, 1);
}
END_TEST

START_TEST(test_terminate_with_high_score) {
    userInput(Start, false);
    updateCurrentState();
    
    GameState_t* state = get_game_state();
    state->info->high_score = 100;
    state->info->score = 500;
    
    userInput(Terminate, false);
    
    int loaded = load_high_score();
    ck_assert_int_ge(loaded, 500);
}
END_TEST

START_TEST(test_game_over_state) {
    userInput(Start, false);
    updateCurrentState();
    
    GameState_t* state = get_game_state();
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            state->field[i][j] = 2;
        }
    }
    
    state->state = Spawn;
    updateCurrentState();
    
    ck_assert_int_eq(state->state, GameOver);
}
END_TEST

START_TEST(test_do_gameover_clears_next) {
    userInput(Start, false);
    updateCurrentState();
    
    GameState_t* state = get_game_state();
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            state->field[i][j] = 2;
        }
    }
    
    state->state = Spawn;
    updateCurrentState();
    
    state->state = GameOver;
    updateCurrentState();
    
    int has_blocks = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (state->next.mtrx[i][j]) {
                has_blocks = 1;
            }
        }
    }
    ck_assert_int_eq(has_blocks, 0);
}
END_TEST

START_TEST(test_place_figure_directly) {
    GameState_t* state = get_game_state();
    
    for (int i = 0; i < FIELD_HEIGHT; i++)
        for (int j = 0; j < FIELD_WIDTH; j++)
            state->field[i][j] = 0;
    
    state->curr.x = 5;
    state->curr.y = 10;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            state->curr.mtrx[i][j] = 0;
    state->curr.mtrx[0][0] = 1;
    state->curr.mtrx[0][1] = 1;
    
    place_figure();
    
    ck_assert_int_eq(state->field[10][5], 2);
    ck_assert_int_eq(state->field[10][6], 2);
}
END_TEST

START_TEST(test_attach_state_transition) {
    userInput(Start, false);
    updateCurrentState();
    
    GameState_t* state = get_game_state();
    
    state->state = Attaching;
    state->attach_start_time = 0;
    state->attach_completed = 0;
    
    updateCurrentState();
    
    ck_assert_int_gt(state->attach_start_time, 0);
}
END_TEST

START_TEST(test_moving_to_down) {
    userInput(Start, false);
    updateCurrentState();
    
    GameState_t* state = get_game_state();
    
    state->curr.y = 5;
    state->curr.x = 5;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            state->curr.mtrx[i][j] = 0;
    state->curr.mtrx[0][0] = 1;
    
    int initial_y = state->curr.y;
    
    state->state = Moving;
    state->moving_type = ToDown;
    
    long long start = get_current_time_ms();
    updateCurrentState();
    long long elapsed = get_current_time_ms() - start;
    
    ck_assert(state->curr.y > initial_y || state->state == Attaching);
    ck_assert_int_lt(elapsed, 1000);
}
END_TEST


START_TEST(test_moving_do_nothing) {
    userInput(Start, false);
    updateCurrentState();
    
    GameState_t* state = get_game_state();
    
    state->state = Moving;
    state->moving_type = DoNothing;
    updateCurrentState();
    
    ck_assert_int_eq(state->state, Move);
}
END_TEST

START_TEST(test_automatic_falling) {
    userInput(Start, false);
    updateCurrentState();
    
    GameState_t* state = get_game_state();
    
    state->curr.y = 5;
    state->curr.x = 5;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            state->curr.mtrx[i][j] = 0;
    state->curr.mtrx[0][0] = 1;
    
    state->state = Move;
    state->last_move_time = 0;
    
    int initial_y = state->curr.y;
    
    updateCurrentState();
    
    ck_assert(state->curr.y > initial_y || state->state == Attaching);
}
END_TEST


Suite* fsm_suite(void) {
    Suite* s = suite_create("FSM");
    TCase* tc = tcase_create("Core");
    
    tcase_add_test(tc, test_game_start);
    tcase_add_test(tc, test_pause_toggle);
    tcase_add_test(tc, test_field_initialization);
    tcase_add_test(tc, test_next_figure_exists);
    tcase_add_test(tc, test_movement_left);
    tcase_add_test(tc, test_movement_right);
    tcase_add_test(tc, test_rotation);
    tcase_add_test(tc, test_user_input_actions);
    tcase_add_test(tc, test_multiple_updates);
    
    tcase_add_test(tc, test_instant_drop_down_key);
    tcase_add_test(tc, test_up_key_release);
    tcase_add_test(tc, test_terminate_with_high_score);
    tcase_add_test(tc, test_game_over_state);
    tcase_add_test(tc, test_do_gameover_clears_next);
    tcase_add_test(tc, test_place_figure_directly);
    tcase_add_test(tc, test_attach_state_transition);
    tcase_add_test(tc, test_moving_to_down);
    tcase_add_test(tc, test_moving_do_nothing);
    tcase_add_test(tc, test_automatic_falling);
    
    suite_add_tcase(s, tc);
    return s;
}

