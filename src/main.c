#include <stdio.h>
#include <stdlib.h>
#include <termio.h>

#include "../inc/LinkedList.h"
#include "../inc/utils.h"
#include "../inc/tui.h"

#define DEBUG

static int height, width;
LinkedList *head;

void exit_programm(int);
void table_process(int, int, LinkedList *);
void help_process(int width, int height);

#define main_menu_size 5
static char *main_menu_text[menu_line_size] = {
    "[1] Input Data",
    "[2] Output Data",
    "[3] Table mode",
    "[4] Free memory",
    "[5] Exit"
};

#define input_menu_size 3
static char *input_menu_text[20] = {
    "[1] Console",
    "[2] .dat file",
    "[3] .txt file"
};

#define output_menu_size 2
static char *output_menu_text[20] = {
    "[1] .dat file",
    "[2] .txt file"
};

void foo(void) {
    cursor_to_xy(1, height);
    printf("Mock func");
    char a = getchar();
}


int callback_main(struct menu_t *menu) {
    switch (menu->chosen)
    {
    case 0:
        menu_process(&(menu->subs[0]));
        break;

    case 1:
        menu_process(&(menu->subs[1]));
        break;

    case 2:
        table_process(width, height, head);
        break;

    case 3:
        foo();
        break;

    case 4:
        exit_programm(0);
        break;

    default:
        break;
    }
}

int callback_input(struct menu_t *menu) {
    switch (menu->chosen)
    {
    case 0:
        foo();
        break;

    case 1:
        foo();
        break;

    case 2:
        foo();
        break;

    default:
        break;
    } 
}

int callback_output(struct menu_t *menu) {
    switch (menu->chosen)
    {
    case 0:
        foo();
        break;

    case 1:
        foo();
        break;

    case 2:
        foo();
        break;

    default:
        break;
    }  
}

int main(int argc, char const *argv[])
{
#ifdef DEBUG
    //system("./test_utils");//TODO: Call tests
#endif
    set_keypress();
    initialize_term_xy(&height, &width);
    clrscr();
    home();

    visible_cursor();

    reset_keypress();
    head = CreateList(5);
    clrscr();
    set_keypress();
    
    invisible_cursor();
    
    char act;
    if (height <= 17 && width <= 74) {
        printf("Plese make your terminal bigger. It's too small\n");
        visible_cursor();
        return 1;
    }

    struct menu_t main_menu = create_menu(main_menu_text, 
                                          main_menu_size, 
                                          callback_main, 
                                          (width - 34)/2 + 1, 
                                          (height - 7)/2 + 1);

    struct menu_t input_menu = create_menu(input_menu_text, 
                                           input_menu_size, 
                                           callback_input, 
                                           (width - 34)/2 + 1, 
                                           (height - 7)/2 + 1);

    struct menu_t output_menu = create_menu(output_menu_text, 
                                            output_menu_size, 
                                            callback_output, 
                                            (width - 34)/2 + 1, 
                                            (height - 7)/2 + 1);

    add_menu_sub(&main_menu, &input_menu, 0);
    add_menu_sub(&main_menu, &output_menu, 1);

    clrscr();
    draw_menu_form(width, height);
    menu_process(&main_menu);




    reset_keypress();
    visible_cursor();

    DeleteList(head);

    delete_menu(&output_menu);
    delete_menu(&input_menu);
    delete_menu(&main_menu);

    return 0;
}

void correct_process(LinkedList *list) {
    int sel_field = 0;
    char act;
    unsigned long departmentNumber = GetDepartmentNumber(GetData(list));
    unsigned long personnelNumber = GetPersonnelNumber(GetData(list));
    unsigned long jobCode =GetJobCode(GetData(list));
    char *surname = GetSurname(GetData(list));
    unsigned int themeNumber = GetThemeNumber(GetData(list)); 
    unsigned int  durationOfWorkOnTheTopic = GetDurationOfWorkOnTheTopic(GetData(list));
    double salary = GetSalary(GetData(list));
    while (act != 27) {
        draw_correct_form(width, height, sel_field); 
        visible_cursor();
        act = getchar();
        switch (act)
        {
        case 106:
            sel_field++;
            break;
        
        case 107:
            sel_field--;
            break;
        
        case 99:
            reset_keypress();
            if (sel_field == 1) {
                cursor_to_xy((width - 48)/2 + 16, 5);
                scanf("%d", &personnelNumber);
            } else if (sel_field == 2) {
                cursor_to_xy((width - 48)/2 + 8, 6);
                scanf("%s", surname);
            } else if (sel_field == 3) {
                cursor_to_xy((width - 48)/2 + 18, 7);
                scanf("%d", &departmentNumber);
            } else if (sel_field == 4) {
                cursor_to_xy((width - 48)/2 + 7, 8);
                scanf("%f", &salary);
            } else if (sel_field == 5) {
                cursor_to_xy((width - 48)/2 + 6, 9);
                scanf("%d", &themeNumber);
            } else if (sel_field == 6) {
                cursor_to_xy((width - 48)/2 + 30, 10);
                scanf("%d", &durationOfWorkOnTheTopic);
            } else if (sel_field == 7) {
                cursor_to_xy((width - 48)/2 + 9, 11);
                scanf("%d", &jobCode);
            }
            set_keypress();
            break;

        default:
            break;
        }   
    }
    invisible_cursor();
    SetPersonnelNumber(GetData(list), personnelNumber);
    SetSurname(GetData(list), surname);
    SetDepartmentNumber(GetData(list), departmentNumber);
    SetSalary(GetData(list), salary);
    SetThemeNumber(GetData(list), themeNumber);
    SetDurationOfWorkOnTheTopic(GetData(list), durationOfWorkOnTheTopic);
    SetJobCode(GetData(list), jobCode);
    free(surname);
}

void table_process(int width, int height, LinkedList* head) {
    int selected = 0;
    char act;
    int page = 0;
    LinkedList *list;
    while (act != 120) {
        draw_table_form(width, height);
        list = print_linked_list_data(head, width, height, selected, page);
        cursor_to_xy(2, height-2);
        act = getchar();
        switch (act) {
        case 104:
            help_process(width, height);
            break;
        
        case 106: //J
            if (selected > height - 7) {
                selected = 1;
                page++;
            } else {
                selected++;
            }
            break;

        case 107: //K
            if (selected < 0 && page > 0) {
                selected = height - 7;
                page--;
            } else {
                selected--;
            }
            break;

        case 99: //C
            correct_process(list);
            break;

        default:
            cursor_to_xy(2, height-2);
            printf("Wrong action");
            break;
        }
        cursor_to_xy(width-14, height-2);
        printf("SEL:%-2d", selected);
    }
}

void exit_programm(int exit_code) {
    reset_keypress();
    visible_cursor();

    DeleteList(head);

    fclose(NULL); //FIXME: impliment 
    // delete_menu(&output_menu);
    // delete_menu(&input_menu);
    // delete_menu(&main_menu); 
}

void help_process(int width, int height) {
    clrscr();
    home();
    char act;
    while (1) {
        draw_help_form(width, height);
        act = getchar();
        switch (act) {
        case 27:
            return;
            break;

        default:
            cursor_to_xy(2, height-1);
            printf("Wrong action");
            break;
        }
    }
}