#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>

#define ESC "\033"

/*!
 * =======UNIX=======
 * LINUX Do not use $REPLY enviroment variable in code
 * Use system(PAUSE); to pause your program. Before use 
 * system(PAUSE) must be printf with '\n'
*/
#if defined unix

#include <unistd.h>
#define wait(seconds) sleep(seconds);

//FIXME: Разбраться почему обязателен printf с '\n'
#define PAUSE "read"

/*=======WIN========*/
#elif defined _WIN32

#include <windows.h>
#define wait(seconds) Sleep(1000*seconds);

//TODO: Тест на WIN
#define PAUSE "pause"

#endif

//Format text
#define BRIGHT 		1
#define DIM			2
#define ITALIC  	3
#define UNDERLINED	4
#define BLINK		5 //FIXME: Not working
#define FAST_BLINK	6 //FIXME: Not working
#define REVERSE     7
#define HIDDEN      8

//Foreground Colours (text)
#define F_BLACK 	30
#define F_RED		31
#define F_GREEN		32
#define F_YELLOW	33
#define F_BLUE		34
#define F_MAGENTA 	35
#define F_CYAN		36
#define F_WHITE		37

//Background Colours
#define B_BLACK 	40
#define B_RED		41
#define RESET 		0
#define B_GREEN		42
#define B_YELLOW	43
#define B_BLUE		44
#define B_MAGENTA 	45
#define B_CYAN		46
#define B_WHITE		47

/*!
 * =====Terminal controll=====
 * Используйте while (1) если не хотите, чтоыб ари каждом использовании функции
 * cursor_to_xy() экран очищался
*/ 
#define home() 			printf(ESC "[H") //Move cursor to the indicated row, column (origin at 1,1)
#define clrscr()		printf(ESC "[2J") //lear the screen, move to (1,1)
#define cursor_to_xy(x,y)		printf(ESC "[%d;%dH", y, x);
#define visible_cursor() printf(ESC "[?25h");
#define invisible_cursor() printf(ESC "[?25l");
/** 
 *	Set Display Attribute Mode	<ESC>[{attr1};...;{attrn}m
*/
#define resetcolor() printf(ESC "[0m")
#define set_display_atrib(color) 	printf(ESC "[%dm",color)

/*!
 * USAGE:
 * Only read, do not write anything into this
*/
static int term_height;
static int term_width;


void initialize_term_xy(int *x, int *y);
// {
//     printf("\x1B[255;255H\x1B[6n");
//     scanf("\x1B[%d;%dR", &term_width, &term_height);
//     printf("Width: %d; Height: %d\n", term_width, term_height);//DE:ETE in Release
// }


/*=====TESTS=====*/

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

#endif /*_UTILS_H_*/
