#ifndef _TUI_H_
#define _TUI_H_

#define BORDER "┌─────┬────────────────────┬────────┬───┬──────┬────────┬────────────────┐\n"\
"│PN   │SURNAME             │THEME   │DOF│SALARY│JC      │DN              │\n"\
"├─────┴────────────────────┴────────┴───┴──────┴────────┴────────────────┤\n"\
"│1     Mudrik                                                            │\n"\
"│2     Usmanskiy                                                         │\n"\
"│3     Purgin                                                            │\n"\
"│4                                                                       │\n"\
"│5                                                                       │\n"\
"│6                                                                       │\n"\
"│7                                                                       │\n"\
"│8                                                                       │\n"\
"│9                                                                       │\n"\
"│10                                                                      │\n"\
"├────────────────────────────────────────────────────────────────────────┤\n"\
"│MORE ABOUT FIELD                                                        │\n"\
"└────────────────────────────────────────────────────────────────────────┘\n"\
" TIPS: [x] exit; [f12] more;                                              \n"

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
// }s

#endif //_TUI_H_