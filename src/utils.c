#include "../inc/utils.h"

void initialize_term_xy(void) {
    printf("\x1B[255;255H\x1B[6n");
    scanf("\x1B[%d;%dR", &term_width, &term_height);
    printf("Width: %d; Height: %d\n", term_width, term_height);//DE:ETE in Release
}

void test_begin(char *testName) {
    t_count = 0;
    terr_count= 0;

    // sprintf(buff, "***************TEST BEGIN****************");
    // printf("%-*s\n", 41, buff);
    test_printf("***************TEST BEGIN****************");

    // sprintf(buff, "TEST: %s", testName);
    // printf("%-*s\n", 41, buff);

    test_printf("TEST: %s", testName);
}


void test_end(void) {
    test_printf("****************TEST END*****************");
    if (terr_count) {
        test_printf_bad("RESULTS: BAD");
        test_printf_bad("Tests: %d", t_count);
        test_printf_bad("Tests 'Ok': %d", t_count - terr_count);
        test_printf_bad("Tests 'Bad': %d", terr_count);
    } else {
        test_printf_ok("RESULTS: OK");
        test_printf_ok("Tests: %d", t_count);
        test_printf_ok("Tests 'Ok': %d", t_count - terr_count);
        test_printf_ok("Tests 'Bad': %d", terr_count);
    }

}

void assertion(char *exp_name, char *real_name, int exp_val, int real_val) {
    t_count++;
    if (real_val == exp_val) {
        test_printf_ok("%s is %s OK", real_name, exp_name);
    } else {
        terr_count++;
        test_printf_bad("%s isn't %s is %d BAD", real_name, exp_name, real_val);
    }
}


void expectation(int cond, char *msg) {
    t_count++;
    if (cond) {
        test_printf_ok("%-36s[OK]", msg);
    } else {
        terr_count++;
        test_printf_bad("%-35s[BAD]", msg);
    }
}
