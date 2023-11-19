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