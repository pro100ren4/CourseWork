#include "../inc/tui.h"

#include "../inc/utils.h"

/*
 * Need to type [Enter] when use
*/
void initialize_term_xy(int *x, int *y) {
    printf("\x1B[255;255H\x1B[6n");
    scanf("\x1B[%d;%dR", &term_height, &term_width);
    clrscr();
    home();
    printf("Width: %d, Height: %d\n", term_width, term_height);
    *x = term_width;
    *y = term_height;
    system(PAUSE);
}