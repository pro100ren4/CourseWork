#include "../inc/utils.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    printf("TEST: terminal drawing funcs\n");


    printf("\nText format\n");

    set_display_atrib(BRIGHT);
    printf("BRIGHT\t");
    resetcolor();

    set_display_atrib(DIM);
    printf("DIM\t");
    resetcolor();

    set_display_atrib(ITALIC);
    printf("ITALIC\t");
    resetcolor();

    set_display_atrib(UNDERLINED);
    printf("UNDERLINED\n");
    resetcolor();

    set_display_atrib(BLINK);
    printf("BLINK\t");
    resetcolor();

    set_display_atrib(FAST_BLINK);
    printf("FBLINK\t");
    resetcolor();

    set_display_atrib(REVERSE);
    printf("REVERSE\t");
    resetcolor();

    set_display_atrib(HIDDEN);
    printf("HIDDEN\n");
    resetcolor();


    printf("\nFG color\n");

    set_display_atrib(F_BLACK);
    printf("F_BLACK\t");
    resetcolor();

    set_display_atrib(F_RED);
    printf("F_RED\t");
    resetcolor();

    set_display_atrib(F_GREEN);
    printf("F_GREEN\t");
    resetcolor();

    set_display_atrib(F_YELLOW);
    printf("F_YELLOW\n");
    resetcolor();

    set_display_atrib(F_BLUE);
    printf("F_BLUE\t");
    resetcolor();

    set_display_atrib(F_MAGENTA);
    printf("F_MGNT\t");
    resetcolor();

    set_display_atrib(F_CYAN);
    printf("F_CYAN\t");
    resetcolor();

    set_display_atrib(F_WHITE);
    printf("F_WHITE\n");
    resetcolor();


    printf("\nBG color\n");

    set_display_atrib(B_BLACK);
    printf("B_BLACK\t");
    resetcolor();

    set_display_atrib(B_RED);
    printf("B_RED\t");
    resetcolor();

    set_display_atrib(B_GREEN);
    printf("B_GREEN\t");
    resetcolor();

    set_display_atrib(B_YELLOW);
    printf("B_YELLOW\n");
    resetcolor();

    set_display_atrib(B_BLUE);
    printf("B_BLUE\t");
    resetcolor();

    set_display_atrib(B_MAGENTA);
    printf("B_MGNT\t");
    resetcolor();

    set_display_atrib(B_CYAN);
    printf("B_CYAN\t");
    resetcolor();

    set_display_atrib(B_WHITE);
    printf("B_WHITE\n");
    resetcolor();   


    cursor_to_xy(10,18);
    printf("cursor at x:10 y:18\n");

    cursor_to_xy(10,20);
    printf("PAUSE (Press [Enter])\n");
    system(PAUSE);

    clrscr();
    home();

    test_begin("MyTest"); 

    test_asrt(5, 5);
    test_asrt(5, 4);

    test_expt(5 == 5, "5 == 5");
    test_expt(5 == 4, "5 == 4");
    
    test_end();

    test_begin("MyTest2");
    test_end();


    printf("PAUSE (Press [Enter])\n");
    system(PAUSE);
    printf("This screen must be cleared after 5 sec...\n");
    printf("TEST END: Bye-bye\n");
    wait(5);
    clrscr();
    home();

    return 0;
}
