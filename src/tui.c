#include "../inc/tui.h"

#include <termios.h>
#include <stdlib.h>

#include "../inc/utils.h"

//Need to type [Enter] when use
void initialize_term_xy(int *x, int *y) {
    printf("\x1B[255;255H\x1B[6n");
    scanf("\x1B[%d;%dR", x, y);
    clrscr();
    home();
    // printf("Width: %d, Height: %d\n", term_width, term_height);
    // *x = term_width;
    // *y = term_height;
    // system(PAUSE);
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


// "┌─────┬────────────────────┬────────┬───┬──────┬────────┬────────────────┐\n"\
// "│PN   │SURNAME             │THEME   │DOF│SALARY│JC      │DN              │\n"\
// "├─────┴────────────────────┴────────┴───┴──────┴────────┴────────────────┤\n"\
// "│1     Mudrik                                                            │\n"\
// "│2     Usmanskiy                                                         │\n"\
// "│3     Purgin                                                            │\n"\
// "│4                                                                       │\n"\
// "│5                                                                       │\n"\
// "│6                                                                       │\n"\
// "│7                                                                       │\n"\
// "│8                                                                       │\n"\
// "│9                                                                       │\n"\
// "│10                                                                      │\n"\
// "├────────────────────────────────────────────────────────────────────────┤\n"\
// "│MORE ABOUT FIELD                                                        │\n"\
// "└────────────────────────────────────────────────────────────────────────┘\n"\
// " TIPS: [x] exit; [f12] more;                                              \n"

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


void draw_menu_form(int x, int y) {
    clrscr();
    home();

    //int x = (width - 34)/2, y = (height - 7)/2;

    cursor_to_xy(x, y);

    printf("┌MENU");
    for (int i = 6; i < 34; i++) {
        printf("─");
    }
    printf("┐\n");

    for (int i = 1; i < 6; i++) {
        cursor_to_xy(x, y + i);
        printf("│");
        for (int j = 0; j < 34 - 2; j++) {
            printf(" ");
        }
        printf("│\n");
    }

    cursor_to_xy(x, y + 6)

    printf("└");
    for (int i = 2; i < 34; i++) {
        printf("─");
    }
    printf("┘\n");
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

static struct termios stored_settings;

void set_keypress(void)
{
    struct termios new_settings;

    tcgetattr(0,&stored_settings);

    new_settings = stored_settings;

    /* Disable canonical mode, and set buffer size to 1 byte */
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;

    tcsetattr(0,TCSANOW,&new_settings);
    return;
}

void reset_keypress(void)
{
    tcsetattr(0,TCSANOW,&stored_settings);
    return;
}




void print_menu(struct menu_t *menu) {
    for (int i = 0; i < menu->menu_size; i++) {
        cursor_to_xy(menu->x, menu->y + i);
        if(i == menu->chosen)
            set_display_atrib(REVERSE);
        printf("%-*s", menu_line_size, menu->menu_text[i]);
        if(i == menu->chosen)
            resetcolor();
    }
}


void menu_process(struct menu_t *menu) {
    
    char act;
    //menu->chosen = -1;
    
    do {
        if (act == 106 && menu->chosen < menu->menu_size) { 
            //J
            menu->chosen++;
        } else if (act == 107 && menu->chosen >= 0) {
            //K
            menu->chosen--;
        } else if (act == 10) {
            //ENTER
            menu->menu_callback(menu);
        } else if (act == 27) {
            //ESC
            return;
        } else if (act >= 49 && act <= 58) {
            menu->chosen = act - 49;
            menu->menu_callback(menu);
        } else if (act == 48) {
            menu->chosen = 10;
            menu->menu_callback(menu);
        } 

        draw_menu_form(menu->x - 1, menu->y - 1);
        print_menu(menu);
        act = getchar();

    } while (1);
}


struct menu_t create_menu(char **menu_text, int menu_size, int (*menu_callback)(struct menu_t *), int x, int y) {
    struct menu_t menu = {
        .menu_text = menu_text, 
        .menu_size = menu_size,
        .menu_callback = menu_callback,
        .subs = (struct menu_t *)malloc(sizeof(struct menu_t)*menu_size),
        .chosen = -1,
        .x = x,
        .y = y
    };
    return menu;
}


void delete_menu(struct menu_t *menu) {
    free(menu->subs);
}

void add_menu_sub(struct menu_t *main_menu, struct menu_t *sub_menu, int position) {
    main_menu->subs[position] = *sub_menu;
}

