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

// Use in cycle
void draw_correct_form(int width, int height) {
    int x = (width - 48)/2;
    int y = 4;
    char *CORRECT_FORM[] = {
        "┌────────────────────CORRECT───────────────────┐",  
        "│Personal number                               │", 
        "│Surname                                       │", 
        "│Department number                             │", 
        "│Salary                                        │", 
        "│Theme                                         │", 
        "│Duration of work on the theme                 │", 
        "│Job code                                      │", 
        "│     Confim[Y]                  Cancel[N]     │", 
        "└──────────────────────────────────────────────┘"  
    };
    for (int i = 0; i < 10; i++) {
        cursor_to_xy(x,y + i);
        printf(CORRECT_FORM[i]);
    }
}

void draw_table_form(int width, int height) {
    clrscr();
    home();
    int wide = (width - 74)/7;
//  First line
    printf("┌─────");
    for (int i = 0; i < wide; i++)
        printf("─");

    printf("┬────────────────────");
    for (int i = 0; i < wide + (width - 74)%7; i++)
        printf("─");
    
    printf("┬────────");
    for (int i = 0; i < wide; i++) 
        printf("─");

    printf("┬──────────");
    for (int i = 0; i < wide; i++) 
        printf("─");

    printf("┬────────");
    for (int i = 0; i < wide; i++) 
        printf("─");

    printf("┬────");
    for (int i = 0; i < wide; i++) 
        printf("─");

    printf("┬───────────");
    for (int i = 0; i < wide; i++) 
        printf("─");

    printf("┐\n");  

//  Second line
    printf("│PN   ");
    for (int i = 0; i < wide; i++)
        printf(" ");

    printf("│SURNAME             ");
    for (int i = 0; i < wide + (width - 74)%7; i++)
        printf(" ");
    
    printf("│DN      ");
    for (int i = 0; i < wide; i++) 
        printf(" ");

    printf("│SALARY    ");
    for (int i = 0; i < wide; i++) 
        printf(" ");

    printf("│THEME   ");
    for (int i = 0; i < wide; i++) 
        printf(" ");

    printf("│DOF ");
    for (int i = 0; i < wide; i++) 
        printf(" ");

    printf("│JC         ");
    for (int i = 0; i < wide; i++) 
        printf(" ");

    printf("│\n"); 

//  Third line
    printf("├─────");
    for (int i = 0; i < wide; i++)
        printf("─");

    printf("┴────────────────────");
    for (int i = 0; i < wide + (width - 74)%7; i++)
        printf("─");
    
    printf("┴────────");
    for (int i = 0; i < wide; i++) 
        printf("─");

    printf("┴──────────");
    for (int i = 0; i < wide; i++) 
        printf("─");

    printf("┴────────");
    for (int i = 0; i < wide; i++) 
        printf("─");

    printf("┴────");
    for (int i = 0; i < wide; i++) 
        printf("─");

    printf("┴───────────");
    for (int i = 0; i < wide; i++) 
        printf("─");

    printf("┤\n");

    for (int i = 0; i < height - 7; i++) {
        printf("│");
        for (int j = 0; j < width - 2; j++) {
            printf(" ");
        }
        printf("│\n");
    }


//  Botom info line
    printf("├");
    for (int j = 0; j < width - 2; j++) {
        printf("─");
    }
    printf("┤\n");

    printf("│");
    for (int j = 0; j < width - 2; j++) {
        printf(" ");
    }
    printf("│\n");

    printf("└");
    for (int j = 0; j < width - 2; j++) {
        printf("─");
    }
    printf("┘\n");

    printf("%-*s", width, " KEYS: [h] help; [x] exit; [m] menu; [k] up; [j] down; [c] correct");

}

// 123456789012345678901234567890123456789012  42
// ┌──────────────────MENU──────────────────┐1
// │ [1] Read Data from File                │2
// │ [2] Write Data to File                 │3
// │ [3] Read Data from Console             │4
// │ [4]                                    │5
// │ [5]                                    │6
// │                                        │7
// │                                        │8
// │ [x] Close                              │9
// └────────────────────────────────────────┘0


void draw_menu_form(int width, int height) {
    int x = (width - 42)/2;
    int y = 4;
    char *CORRECT_FORM[] = {
        "┌──────────────────MENU──────────────────┐",  
        "│ [1] Read Data from File                │", 
        "│ [2] Write Data to File                 │", 
        "│ [3] Read Data from Console             │", 
        "│ [4]                                    │", 
        "│ [5]                                    │", 
        "│                                        │", 
        "│                                        │", 
        "│ [x] Close                              │", 
        "└────────────────────────────────────────┘"  
    };
    for (int i = 0; i < 10; i++) {
        cursor_to_xy(x,y + i);
        printf(CORRECT_FORM[i]);
    }
}

// 123456789012345678901234567890123456789012  42
// ┌──────────────────HELP──────────────────┐1
// │ [PN] - Personal Number                 │2
// │ [SURNAME] - Surname                    │3
// │ [DN] - Department number               │4
// │ [SALARY] - Salary                      │5
// │ [THEME] - Number of theme              │6
// │ [DOF] - Duration of work on th theme   │7
// │ [JC] - Job code                        │8
// │                           Close[x]     │9
// └────────────────────────────────────────┘0

void draw_help_form(int width, int height) {
    int x = (width - 42)/2;
    int y = 4;
    char *CORRECT_FORM[] = {
        "┌──────────────────HELP──────────────────┐",  
        "│ [PN] - Personal Number                 │", 
        "│ [SURNAME] - Surname                    │", 
        "│ [DN] - Department number               │", 
        "│ [SALARY] - Salary                      │", 
        "│ [THEME] - Number of theme              │", 
        "│ [DOF] - Duration of work on th theme   │", 
        "│ [JC] - Job code                        │", 
        "│                           Close[x]     │", 
        "└────────────────────────────────────────┘"  
    };
    for (int i = 0; i < 10; i++) {
        cursor_to_xy(x,y + i);
        printf(CORRECT_FORM[i]);
    }
}