#include "../inc/tui.h"

#include <termios.h>
#include <stdlib.h>

#include "../inc/LinkedList.h"
#include "../inc/ResearchWorker.h"
#include "../inc/utils.h"

//Before use call set_keypress()
void initialize_term_xy(int *x, int *y) {
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif
    printf("\x1B[255;255H\x1B[6n");
    scanf("\x1B[%d;%dR", x, y);
    clrscr();
    home();
}

void flush() {
    int c;
    while ((c = getchar()) != EOF && c != '\n');
}


void draw_correct_form(int width, int height, int selected) {
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
        "│[ENTER]Enter [ESC]Exit [k/j]up/down           │", 
        "└──────────────────────────────────────────────┘"  
    };
    for (int i = 0; i < 10; i++) {
        if (selected > 0 && selected < 8 && i == selected) {
            set_display_atrib(REVERSE);
        }
        cursor_to_xy(x,y + i);
        printf("%s", CORRECT_FORM[i]);
        if (selected > 0 && selected < 8 && i == selected) {
            resetcolor();
        }
    }
}

void draw_data_to_correct(int width, int height, LinkedList *list) {
    invisible_cursor();
    set_keypress();

    int x = (width - 48)/2;
    int y = 4;
    cursor_to_xy(x+17, y+1);
    printf("%lu", GetPersonalNumber(GetData(list)));

    cursor_to_xy(x+9, y+2);
    printf("%s", GetSurname(GetData(list)));

    cursor_to_xy(x+19, y+3);
    printf("%lu", GetDepartmentNumber(GetData(list)));

    cursor_to_xy(x+8, y+4);
    printf("%.3f", GetSalary(GetData(list)));

    cursor_to_xy(x+7, y+5);
    printf("%d", GetThemeNumber(GetData(list)));

    cursor_to_xy(x+31, y+6);
    printf("%d", GetDurationOfWorkOnTheTopic(GetData(list)));

    cursor_to_xy(x+10, y+7);
    printf("%lu", GetJobCode(GetData(list)));

    reset_keypress();
    visible_cursor();
}

/*
 ┌─────┬────────────────────┬────────┬──────────┬────────┬────┬───────────┐1
 │PN   │SURNAME             │DN      │SALARY    │THEME   │DOF │JC         │2
 ├─────┴────────────────────┴────────┴──────────┴────────┴────┴───────────┤3
 │12345 ABCDEFGHIJKLMNOPQRST 12345678 1234567.89 12345678 1234 12345678901│3
 │12345 ABCDEFGHIJKLMNOPQRST 12345678 1234567.89 12345678 1234 12345678901│4
 │12345 ABCDEFGHIJKLMNOPQRST 12345678 1234567.89 12345678 1234 12345678901│6
 │12345 ABCDEFGHIJKLMNOPQRST 12345678 1234567.89 12345678 1234 12345678901│7
 │12345 ABCDEFGHIJKLMNOPQRST 12345678 1234567.89 12345678 1234 12345678901│5
 │12345 ABCDEFGHIJKLMNOPQRST 12345678 1234567.89 12345678 1234 12345678901│8
 │12345 ABCDEFGHIJKLMNOPQRST 12345678 1234567.89 12345678 1234 12345678901│9
 │12345 ABCDEFGHIJKLMNOPQRST 12345678 1234567.89 12345678 1234 12345678901│0
 │12345 ABCDEFGHIJKLMNOPQRST 12345678 1234567.89 12345678 1234 12345678901│1
 │12345 ABCDEFGHIJKLMNOPQRST 12345678 1234567.89 12345678 1234 12345678901│2
 ├────────────────────────────────────────────────────────────────────────┤4
 │MORE ABOUT FIELD                                                        │5
 └────────────────────────────────────────────────────────────────────────┘6
  KEYS: [h]help; [x]exit; [k]up; [j]down; [c]correct; [s]sort              7 
*/
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
    printf("│PN   "); //5
    for (int i = 0; i < wide; i++)
        printf(" ");

    printf("│SURNAME             "); //20
    for (int i = 0; i < wide + (width - 74)%7; i++)
        printf(" ");
    
    printf("│DN      "); //8
    for (int i = 0; i < wide; i++) 
        printf(" ");

    printf("│SALARY    "); //10
    for (int i = 0; i < wide; i++) 
        printf(" ");

    printf("│THEME   "); // 8
    for (int i = 0; i < wide; i++) 
        printf(" ");

    printf("│DOW "); //4
    for (int i = 0; i < wide; i++) 
        printf(" ");

    printf("│JC         "); //11
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

    printf("%-*s", width, " [h]help [ESC]exit [k/j]up/down [x]del [c]correct [s]sort [/]find [f]stat");

}


void draw_menu_form(int x, int y) {
    clrscr();
    home();
    invisible_cursor();
    set_keypress();

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
    cursor_to_xy(x, y + 7)
    printf("[k/j]up/down [Enter]confirm\n");
    cursor_to_xy(x, y + 8)
    printf("[ESC]back\n");
    visible_cursor();
    reset_keypress();
}


void draw_help_form(int width, int height) {
    printf("┌HELP");
    for (int i = 6; i < width; i++) {
        printf("─");
    }
    printf("┐\n");

    printf("│%-*s│\n", width -2, " [Table Mode topics");
    printf("│%-*s│\n", width -2, "PN - Personal Number");
    printf("│%-*s│\n", width -2, "SURNAME - Surname");
    printf("│%-*s│\n", width -2, "DN - Department number");
    printf("│%-*s│\n", width -2, "SALARY - Salary");
    printf("│%-*s│\n", width -2, "THEME - Number of theme");
    printf("│%-*s│\n", width -2, "DOW - Duration of work on th theme");
    printf("│%-*s│\n", width -2, "JC - Job code");

    for (int i = 10; i < height; i++) {
        printf("│");
        for (int j = 2; j < width; j++) {
            printf(" ");
        }
        printf("│\n");
    }
    printf("└");
    for(int i = 2; i < width; i++ ) {
        printf("─");
    }
    printf("┘");
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


void menu_process(struct menu_t *menu, LinkedList **head) {
    
    char act;
    menu->chosen = 0;
    
    do {
        if (act == 106 && menu->chosen < menu->menu_size - 1) { 
            //J
            menu->chosen++;
        } else if (act == 107 && menu->chosen > 0) {
            //K
            menu->chosen--;
        } else if (act == 10) {
            //ENTER
            menu->menu_callback(menu, head);
        } else if (act == 27) {
            //ESC
            return;
        } else if (act >= 49 && act <= 58) {
            menu->chosen = act - 49;
        } else if (act == 48) {
            menu->chosen = 10;
        } 

        draw_menu_form(menu->x - 1, menu->y - 1);
        print_menu(menu);
        act = getchar();

    } while (1);
}


struct menu_t create_menu(char **menu_text, int menu_size, void (*menu_callback)(struct menu_t *, LinkedList **), int x, int y) {
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

static int page = 0;

LinkedList* print_linked_list_data(LinkedList *head, int width, int height, int selected, int page) {
    int wide = (width - 74)/7;
    int rows = height - 7;
    LinkedList *res, *i = head, *sz = head;
    int size = 0;
    for (size = 0; sz != NULL; size++)sz = GetNext(sz);

    for(int k = 0; k < page*rows; k++) i = GetNext(i); 

    selected = (selected >= rows ? selected%rows:selected);
    cursor_to_xy(4, 2);
    int j = 0;
    for(; i != NULL && j < rows; i = GetNext(i), j++) {
        cursor_to_xy(2, 4 + j);
        if (j == selected) {
            set_display_atrib(REVERSE);
            res = i; 
        } 
        printf("%*lu ", 5+wide, GetPersonalNumber(GetData(i)));
        printf("%*s ", (20+wide+(width - 74)%7), GetSurname(GetData(i)));
        printf("%*lu ", 8+wide, GetDepartmentNumber(GetData(i)));
        printf("%*.2f ", 9+wide, GetSalary(GetData(i)));
        printf("%*d ", 8+wide, GetThemeNumber(GetData(i)));
        printf("%*d ", 4+wide, GetDurationOfWorkOnTheTopic(GetData(i)));
        printf("%*lu", 11+wide, GetJobCode(GetData(i)));
        if (j == selected)
            resetcolor(); 
    } 
    cursor_to_xy(width - 8, height - 2);
    printf("PAGE:%-3d", page+1);
    return res;
}

void draw_input_form(int width, int height, int selected) {
    int x = (width - 48)/2;
    int y = 4;
    char *CORRECT_FORM[] = {
        "┌─Enter─Research─Worker────────────────────────┐",  
        "│Personal number                               │", 
        "│Surname                                       │", 
        "│Department number                             │", 
        "│Salary                                        │", 
        "│Theme                                         │", 
        "│Duration of work on the theme                 │", 
        "│Job code                                      │",  
        "└──────────────────────────────────────────────┘"  
    };
    for (int i = 0; i < 9; i++) {
        if (selected > 0 && selected < 8 && i == selected) {
            set_display_atrib(REVERSE);
        }
        cursor_to_xy(x,y + i);
        printf("%s", CORRECT_FORM[i]);
        if (selected > 0 && selected < 8 && i == selected) {
            resetcolor();
        }
    }
}

void draw_dat_file_read_form(int width, int height) {
    char *FileNameForm[] = {
        "┌Enter─Dat─File─name─────────────┐",
        "│                                │",
        "└[ENTER]Type─filenme─[ESC]Exit───┘",
        " Name must be <= 32ch!!           "
    };
    int x = (width - 34)/2;
    int y = 4;
    for(int i = 0; i < 4; i++) {
        cursor_to_xy(x, y + i);
        printf("%s", FileNameForm[i]);
    }
}


void draw_txt_file_read_form(int width, int height) {
    char *FileNameForm[] = {
        "┌Enter─Txt─File─name─────────────┐",
        "│                                │",
        "└[ENTER]Type─filenme─[ESC]Exit───┘",
        " Name must be <= 32ch!!           "
    };
    int x = (width - 34)/2;
    int y = 4;
    for(int i = 0; i < 4; i++) {
        cursor_to_xy(x, y + i);
        printf("%s", FileNameForm[i]);
    }
}

void draw_enter_listsize_form(int width, int height) {
    char *FileNameForm[] = {
        "┌Enter─List─Size─────────────────┐",
        "│                                │",
        "└[ENTER]Enter─size─[ESC]Exit─────┘"
    };
    int x = (width - 34)/2;
    int y = 4;
    for(int i = 0; i < 3; i++) {
        cursor_to_xy(x, y + i);
        printf("%s", FileNameForm[i]);
    }
}

void draw_atterntion_form(int width, int height) {
    char *AtterntionForm[] = {
        "┌Attention───────────────────────────────────────────────────────┐",
        "│                                                                │",
        "└[ENTER]OK─[ESC]CANCEL───────────────────────────────────────────┘"
    };
    int x = (width - 66)/2;
    int y = 4;
    for(int i = 0; i < 3; i++) {
        cursor_to_xy(x, y + i);
        printf("%s", AtterntionForm[i]);
    }
}

void draw_statistics_form(int width, int height) {
    char *StatisticsForm[] = {
        "┌Theme───|Workers───|Salary────────────────────┐",
        "│                                              │",
        "│                                              │",
        "│                                              │",
        "│                                              │",
        "│                                              │",
        "│                                              │",
        "│                                              │",
        "│                                              │",
        "└TOTAL:   ─PAGE:   ─[k/j]next/prev─────────────┘"
    };
    int x = (width - 48)/2;
    int y = 4;
    for(int i = 0; i < 10; i++) {
        cursor_to_xy(x, y + i);
        printf("%s", StatisticsForm[i]);
    }
}

