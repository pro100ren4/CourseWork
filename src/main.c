#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <string.h>

#include "../inc/LinkedList.h"
#include "../inc/utils.h"
#include "../inc/tui.h"
#include "../inc/assertimp.h"

#define DEBUG

int height, width;
// static LinkedList *head;

void terminate_programm(int, LinkedList *);
void table_process(int, int, LinkedList *);
void help_process(int width, int height);
void read_dat_list_process(int width, int height, LinkedList **head);
void read_txt_list_process(int width, int height, LinkedList **head);
void read_con_list_process(int width, int height, LinkedList **head);
LinkedList *console_input_process();




/*
 *  ######################################
 *  #             MENU SET UP            #
 *  ######################################
*/

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
    home();
    printf("Mock func");
    char a = getchar();
}


int callback_main(struct menu_t *menu, LinkedList *head) {
    switch (menu->chosen)
    {
    case 0:
        menu_process(&(menu->subs[0]), head);
        break;

    case 1:
        menu_process(&(menu->subs[1]), head);
        break;

    case 2:
        if (!head) {
            home();
            error("list empty");
            getchar();
            break;
        }
        table_process(width, height, head);
        break;

    case 3:
        foo();
        break;

    case 4:
        terminate_programm(0, head);
        break;

    default:
        break;
    }
    return 0;
}

int callback_input(struct menu_t *menu, LinkedList *head) {
    switch (menu->chosen)
    {
    case 0:
        read_con_list_process(width, height, &head);
        break;

    case 1:
        read_dat_list_process(width, height, &head);
        
        break;

    case 2:
        read_txt_list_process(width, height, &head);
        break;

    default:
        break;
    } 

    return 0;
}

int callback_output(struct menu_t *menu, LinkedList *head) {
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

    return 0;
}




/*
 *  ######################################
 *  #                MAIN                #
 *  ######################################
*/

int main(int argc, char const *argv[])
{
#ifdef DEBUG
    //system("./test_utils");//TODO: Call tests
#endif
    LinkedList *head = NULL;

    set_keypress();
    initialize_term_xy(&height, &width);
    clrscr();
    home();


    reset_keypress();
    // head = CreateList(10);
    // 
    clrscr();
    set_keypress();
    
    invisible_cursor();
    
    char act;
    if (height <= 12 || width <= 74) {
        printf("Plese make your terminal bigger. It's too small\n");
        visible_cursor();
        return 1;
    }


    //FIXME: Проверить на корректность памяти
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

    //Основной цикл
    clrscr();
    draw_menu_form(width, height);
    menu_process(&main_menu, head);


    //Завершение программы
    reset_keypress();
    visible_cursor();

    DeleteList(head);

    delete_menu(&output_menu);
    delete_menu(&input_menu);
    delete_menu(&main_menu);

    return 0;
}




/*
 *  ######################################
 *  #           PROGRAM MODES            #
 *  ######################################
*/

void correct_process(LinkedList *list) {
    set_keypress();
    invisible_cursor();

    int sel_field = 1;
    char act;

    //Кешируем параметры list
    unsigned long departmentNumber = GetDepartmentNumber(GetData(list));
    unsigned long personnelNumber = GetPersonalNumber(GetData(list));
    unsigned long jobCode =GetJobCode(GetData(list));
    char *surname = GetSurname(GetData(list));
    unsigned int themeNumber = GetThemeNumber(GetData(list)); 
    unsigned int  durationOfWorkOnTheTopic = GetDurationOfWorkOnTheTopic(GetData(list));
    double salary = GetSalary(GetData(list));

    while (act != 27) {
        draw_correct_form(width, height, sel_field); 
        draw_data_to_correct(width, height, list);
        visible_cursor();
        act = getchar();
        switch (act)
        {
        case 106: //J
            sel_field++;
            if (sel_field > 7)
                sel_field = 7;
            break;
        
        case 107://K
            sel_field--;
            if (sel_field < 1)
                sel_field = 1;
            break;
        
        case 99:
            reset_keypress();
            if (sel_field == 1) {
                cursor_to_xy((width - 48)/2 + 17, 5);
                scanf("%ld", &personnelNumber);
            } else if (sel_field == 2) {
                cursor_to_xy((width - 48)/2 + 9, 6);
                scanf("%s", surname);
            } else if (sel_field == 3) {
                cursor_to_xy((width - 48)/2 + 19, 7);
                scanf("%ld", &departmentNumber);
            } else if (sel_field == 4) {
                cursor_to_xy((width - 48)/2 + 8, 8);
                scanf("%lf", &salary);
            } else if (sel_field == 5) {
                cursor_to_xy((width - 48)/2 + 7, 9);
                scanf("%d", &themeNumber);
            } else if (sel_field == 6) {
                cursor_to_xy((width - 48)/2 + 31, 10);
                scanf("%d", &durationOfWorkOnTheTopic);
            } else if (sel_field == 7) {
                cursor_to_xy((width - 48)/2 + 10, 11);
                scanf("%ld", &jobCode);
            }
            flush();
            set_keypress();
            break;

        default:
            break;
        }
        SetPersonnelNumber(GetData(list), personnelNumber);
        SetSurname(GetData(list), surname);
        SetDepartmentNumber(GetData(list), departmentNumber);
        SetSalary(GetData(list), salary);
        SetThemeNumber(GetData(list), themeNumber);
        SetDurationOfWorkOnTheTopic(GetData(list), durationOfWorkOnTheTopic);
        SetJobCode(GetData(list), jobCode);
    }
    invisible_cursor();
    free(surname);

    reset_keypress();
    visible_cursor();
}

void table_process(int width, int height, LinkedList* head) {
    set_keypress();
    invisible_cursor();


    int selected = 0;
    char act;
    int page = 0;
    LinkedList *list, *sz = head;
    int list_size = 0;
    for (list_size = 0; sz != NULL; list_size++) sz = GetNext(sz);
    int pages = (list_size / (height - 7));
    int key = 0;

    while (act != 120) {
        draw_table_form(width, height);
        list = print_linked_list_data(head, width, height, selected, page);
        cursor_to_xy(width-14, height-2);
        printf("SEL:%-2d", selected);
        cursor_to_xy(2, height-2);
        act = getchar();
        switch (act) {
        case 104:
            help_process(width, height);
            break;
        
        case 106: //J
            selected++;
            if (selected >= height - 7 && page < pages) {
                selected = 0;
                page++;
            } else if (selected >= height - 7 && page >= pages) {
                selected = height - 7;
                page = pages;
            }
            break;

        case 107: //K
            selected--;
            if (selected < 0 && page > 0) {
                selected = height - 7;
                page--;
            } else if (selected < 0 && page <= 0) {
                selected = 0;
                page = 0;
            }
            break;

        case 99: //C
            correct_process(list);
            break;
        
        case 115: //S
            head = SortListBySurname(head);
            break;

        case 47: // /
            reset_keypress();
            scanf("%d", &key);
            flush();
            key = FindWorkerByPersonalNumber(head, key);
            selected = (key%(height - 7));
            page = key/(height-7);
            set_keypress();
            break;

        default:
            cursor_to_xy(2, height-2);
            printf("Wrong action");
            break;
        }
        
    }

    visible_cursor();
    reset_keypress();
}

void terminate_programm(int exit_code, LinkedList *head) {
    reset_keypress();
    visible_cursor();

    DeleteList(head);

    fclose(NULL); //FIXME: impliment 
    // delete_menu(&output_menu);
    // delete_menu(&input_menu);
    // delete_menu(&main_menu); 
    exit(exit_code);
}

void help_process(int width, int height) {
    set_keypress();
    invisible_cursor();
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
    visible_cursor();
    reset_keypress();
}


//FIXME: Impliment
int atterntion_process(int width, int height, char attention[], size_t att_size) {
    set_keypress();
    clrscr();
    home();

    return 0;
}

void read_dat_list_process(int width, int height, LinkedList **head) {
    set_keypress();
    invisible_cursor();
    clrscr();
    home();
    char act;
    char filename[36];

    int x = (width - 34)/2 + 1;
    int y = 5;

    while (1) {
        draw_dat_file_read_form(width, height);
        act = getchar();
        switch (act)
        {
        case 10:
            cursor_to_xy(x, y);
            visible_cursor();
            reset_keypress();
            scanf("%s", filename);
            flush();
            strcat(filename, ".dat");
            FILE *file = fopen(filename, "rb");
            if (!file) {
                home();
                error("Can't open file");
                head = NULL;
                getchar();
                return;
            }
            *head = ReadListFromFile(file, *head);
            fclose(file);
            reset_keypress();
            visible_cursor();
            return;
            break;
        
        case 27:
            reset_keypress();
            visible_cursor();
            return;
            break;

        default:
            break;
        }
    }
}

void read_txt_list_process(int width, int height, LinkedList **head) {
    set_keypress();
    invisible_cursor();
    clrscr();
    home();
    char act;
    char filename[36];

    int x = (width - 34)/2 + 1;
    int y = 5;

    while (1) {
        draw_txt_file_read_form(width, height);
        act = getchar();
        switch (act)
        {
        case 10:
            cursor_to_xy(x, y);
            visible_cursor();
            reset_keypress();
            scanf("%s", filename);
            flush();
            strcat(filename, ".txt");
            FILE *file = fopen(filename, "r");
            if (!file) {
                home();
                error("Can't open file");
                head = NULL;
                getchar();
                return;
            }
            *head = ReadListFromFile(file, *head);
            fclose(file);
            reset_keypress();
            visible_cursor();
            return;
            break;
        
        case 27:
            reset_keypress();
            visible_cursor();
            return;
            break;

        default:
            break;
        }
    }
}

void read_con_list_process(int width, int height, LinkedList **head) {
    set_keypress();
    invisible_cursor();
    clrscr();
    home();
    char act;
    int listsize = 0;

    // Поля сотрудника нии
    unsigned long departmentNumber, personnelNumber, jobCode;
    char surname[20];
    unsigned int themeNumber, durationOfWorkOnTheTopic;
    double salary;

    int x = (width - 34)/2;
    int y = 4;

    draw_enter_listsize_form(width, height);
    cursor_to_xy(x + 1, y + 1);
    while(scanf("%d", &listsize) != 1) {
        home();
        error("Incorrect input. Try agian");
        flush();
        getchar();
        cursor_to_xy(x + 1, y + 1);
    }
    flush();

    x = (width - 48)/2;

    for (int i = 0; i < listsize; i++) {
        draw_input_form(width, height, 0);
        visible_cursor();
        reset_keypress();
        cursor_to_xy(x + 18, y + 1);
        while(scanf("%ld", &personnelNumber) != 1) {
            home();
            error("Incorrect input. Try agian");
            flush();
            getchar();
            cursor_to_xy(x + 18, y + 1);
        }
        flush();
                

        cursor_to_xy(x + 10, y + 2);
        while(scanf("%s", surname)!= 1) {
            home();
            error("Incorrect input. Try agian");
            flush();
            getchar();
            cursor_to_xy(x + 10, y + 2);
        }
        flush();

        cursor_to_xy(x + 20, y + 3);
        while(scanf("%ld", &departmentNumber)!= 1) {
            home();
            error("Incorrect input. Try agian");
            flush();
            getchar();
            cursor_to_xy(x + 20, y + 3);
        }
        flush();

        cursor_to_xy(x + 9, y + 4);
        while(scanf("%lf", &salary)!= 1) {
            home();
            error("Incorrect input. Try agian");
            flush();
            getchar();
            cursor_to_xy(x + 9, y + 4);
        }
        flush();

        cursor_to_xy(x + 8, y + 5);
        while(scanf("%d", &themeNumber)!= 1) {
            home();
            error("Incorrect input. Try agian");
            flush();
            getchar();
            cursor_to_xy(x + 8, y + 5);
        }
        flush();

        cursor_to_xy(x + 32, y + 6);
        while(scanf("%d", &durationOfWorkOnTheTopic)!= 1) {
            home();
            error("Incorrect input. Try agian");
            flush();
            getchar();
            cursor_to_xy(x + 32, y + 6);
        }
        flush();

        cursor_to_xy(x + 11, y + 7);
        while(scanf("%ld", &jobCode) != 1) {
            home();
            error("Incorrect input. Try agian");
            flush();
            getchar();
            cursor_to_xy(x + 1, y + 7);
        }
        flush();
        set_keypress();
        invisible_cursor();

        ResearchWorker *tmp = CreateResearchWorker(departmentNumber, personnelNumber, jobCode, surname,  themeNumber, durationOfWorkOnTheTopic, salary);
        *head = AddListElement(*head, tmp);
    }
}

void write_dat_list_process(int width, int height, LinkedList **head) {
    set_keypress();
    invisible_cursor();
    clrscr();
    home();
    char act;

    while (1)
    {
        draw_dat_file_read_form(width, height);
    }
    


}

void write_txt_list_process(int width, int height, LinkedList **head) {
    
}
