#ifndef _ASSERTIMP_H_
#define _ASSERTIMP_H_

#include "utils.h"

#define message(format) do {                                            \
    set_display_atrib(B_BLUE);                                          \
    printf("[%s:%d] %s\n", __FUNCTION__, __LINE__, format);             \
    resetcolor();                                                       \
} while (0);

#define warning(format) do {                                            \
    set_display_atrib(B_YELLOW);                                        \
    printf("[%s:%d] %s\n", __FUNCTION__, __LINE__, format);             \
    resetcolor();                                                       \
} while (0);

#define error(format) do {                                              \
    set_display_atrib(B_RED);                                           \
    printf("[%s:%d] %s\n", __FUNCTION__, __LINE__, format);             \
    resetcolor();                                                       \
} while (0);


static int t_count = 0;
static int terr_count = 0;

static char buff[41];

#define test_printf(format, ...) do {       \
    sprintf(buff, format, ##__VA_ARGS__);   \
    printf("%-*s\n", 41, buff);             \
} while (0)

#define test_printf_ok(format, ...) do {    \
    sprintf(buff, format, ##__VA_ARGS__);   \
    set_display_atrib(B_GREEN);             \
    set_display_atrib(BRIGHT);              \
    printf("%-*s\n", 41, buff);             \
    resetcolor();                           \
} while (0)

#define test_printf_bad(format, ...) do {   \
    sprintf(buff, format, ##__VA_ARGS__);   \
    set_display_atrib(B_RED);               \
    set_display_atrib(BRIGHT);              \
    printf("%-*s\n", 41, buff);             \
    resetcolor();                           \
} while (0)

void test_begin(char *testName);
// {
//     t_count = 0;
//     terr_count= 0;

//     // sprintf(buff, "***************TEST BEGIN****************");
//     // printf("%-*s\n", 41, buff);
//     test_printf("***************TEST BEGIN****************");

//     // sprintf(buff, "TEST: %s", testName);
//     // printf("%-*s\n", 41, buff);

//     test_printf("TEST: %s", testName);
// }

void test_end(void);
// {
//     test_printf("****************TEST END*****************");
//     if (terr_count) {
//         test_printf_bad("RESULTS: BAD");
//         test_printf_bad("Tests: %d", t_count);
//         test_printf_bad("Tests 'Ok': %d", t_count - terr_count);
//         test_printf_bad("Tests 'Bad': %d", terr_count);
//     } else {
//         test_printf_ok("RESULTS: OK");
//         test_printf_ok("Tests: %d", t_count);
//         test_printf_ok("Tests 'Ok': %d", t_count - terr_count);
//         test_printf_ok("Tests 'Bad': %d", terr_count);
//     }

// }

void assertion(char *exp_name, char *real_name, int exp_val, int real_val);
// {
//     t_count++;
//     if (real_val == exp_val) {
//         test_printf_ok("%s is %s OK", real_name, exp_name);
//     } else {
//         terr_count++;
//         test_printf_bad("%s isn't %s is %d BAD", real_name, exp_name, real_val);
//     }
// }

#define test_asrt(exp, real) assertion(#exp, #real, exp, real)

void expectation(int cond, char *msg);
// {
//     t_count++;
//     if (cond) {
//         test_printf_ok("%-36s[OK]", msg);
//     } else {
//         terr_count++;
//         test_printf_bad("%-35s[BAD]", msg);
//     }
// }

#define test_expt(cond, msg) expectation(cond, msg)

#endif /*_ASSETIMP_H_*/
