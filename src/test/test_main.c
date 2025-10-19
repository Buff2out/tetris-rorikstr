#include <check.h>

// Объявления Suite из других файлов
Suite* collision_suite(void);
Suite* lines_suite(void);
Suite* figures_suite(void);
Suite* score_suite(void);
Suite* fsm_suite(void);  // <- Эта строка уже есть?

int main(void) {
    SRunner* sr = srunner_create(collision_suite());
    srunner_add_suite(sr, lines_suite());
    srunner_add_suite(sr, figures_suite());
    srunner_add_suite(sr, score_suite());
    srunner_add_suite(sr, fsm_suite());  // <- Эта строка добавлена?
    
    srunner_run_all(sr, CK_VERBOSE);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (failed == 0) ? 0 : 1;
}
