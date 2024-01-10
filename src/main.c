#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <string.h>

#include "../inc/LinkedList.h"
#include "../inc/utils.h"
#include "../inc/tui.h"
#include "../inc/assertimp.h"

// #define DEBUG

static int height, width;

void terminate_programm(int, LinkedList *);
void table_process(int, int, LinkedList **);
void help_process(int width, int height);
void read_dat_list_process(int width, int height, LinkedList **head);
void read_txt_list_process(int width, int height, LinkedList **head);
void read_con_list_process(int width, int height, LinkedList **head);
void write_dat_list_process(int width, int height, LinkedList **head);
void write_txt_list_process(int width, int height, LinkedList **head);
int atterntion_process(int width, int height, char attention[], size_t att_size);
void statistic_process(int width, int height, LinkedList **head);




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


void callback_main(struct menu_t *menu, LinkedList **head) {
    switch (menu->chosen)
    {
    case 0: // INPUT DATA
        menu_process(&(menu->subs[0]), head);
        break;

    case 1: // OUTPUT DATA
        menu_process(&(menu->subs[1]), head);
        break;

    case 2: // TABLE MODE
        if (!(*head)) {
            home();
            error("list empty\nPress [Enter]");
            getchar();
            break;
        }
        table_process(width, height, head);
        break;

    case 3: // FREE MEMORY
        DeleteList(*head);
        *head = NULL;
        break;

    case 4: // EXIT
        terminate_programm(0, *head);
        break;

    default:
        break;
    }
}

void callback_input(struct menu_t *menu, LinkedList **head) {
    switch (menu->chosen)
    {
    case 0: // CONSOLE
        if (*head != NULL) {
            home();
            error("list not empty\nPress [Enter]");
            getchar();
            break;
        }
        read_con_list_process(width, height, head);
        break;

    case 1: // .DAT FILE
        if (*head != NULL) {
            home();
            error("list not empty\nPress [Enter]");
            getchar();
            break;
        }
        read_dat_list_process(width, height, head);
        
        break;

    case 2: // .TXT FILE
        if (*head != NULL) {
            home();
            error("list not empty\nPress [Enter]");
            getchar();
            break;
        }
        read_txt_list_process(width, height, head);
        break;

    default:
        break;
    } 
}

void callback_output(struct menu_t *menu, LinkedList **head) {
    switch (menu->chosen)
    {
    case 0: // .DAT FILE
        if (!(*head)) {
            home();
            error("List is empty\nPress [Enter]");
            getchar();
            break;
        }
        write_dat_list_process(width, height, head);
        break;

    case 1: // .TXT FILE 
        if (!(*head)) {
            home();
            error("List is empty\nPress [Enter]");
            getchar();
            break;
        }
        write_txt_list_process(width, height, head);
        break;

    case 2:
        foo();
        break;

    default:
        break;
    }  
}

struct menu_t main_menu, input_menu, output_menu;


/*
 *  ######################################
 *  #                MAIN                #
 *  ######################################
*/

int main(int argc, char const *argv[])
{
    LinkedList *head = NULL;

    set_keypress();
    initialize_term_xy(&height, &width);
    clrscr();
    home();


    reset_keypress(); 
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
    main_menu = create_menu(main_menu_text, 
                                          main_menu_size, 
                                          callback_main, 
                                          (width - 34)/2 + 1, 
                                          (height - 7)/2 + 1);

    input_menu = create_menu(input_menu_text, 
                                           input_menu_size, 
                                           callback_input, 
                                           (width - 34)/2 + 1, 
                                           (height - 7)/2 + 1);

    output_menu = create_menu(output_menu_text, 
                                            output_menu_size, 
                                            callback_output, 
                                            (width - 34)/2 + 1, 
                                            (height - 7)/2 + 1);

    add_menu_sub(&main_menu, &input_menu, 0);
    add_menu_sub(&main_menu, &output_menu, 1);

    //Основной цикл
    clrscr();
    draw_menu_form(width, height);
    menu_process(&main_menu, &head);


    //Завершение программы
    terminate_programm(0, head);

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
        case KEY_J: //J
            sel_field++;
            if (sel_field > 7)
                sel_field = 7;
            break;
        
        case KEY_K://K
            sel_field--;
            if (sel_field < 1)
                sel_field = 1;
            break;
        
        case KEY_ENTER:
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

void table_process(int width, int height, LinkedList **head) {
    set_keypress();
    invisible_cursor();


    int selected = 0;
    char act;
    int page = 0;
    LinkedList *list, *sz = *head;
    int list_size = 0;
    for (list_size = 0; sz != NULL; list_size++) sz = GetNext(sz);
    int pages = (list_size / (height - 7));
    int key = 0;

    while (act != KEY_ESC) {
        draw_table_form(width, height);
        list = print_linked_list_data(*head, width, height, selected, page);
        cursor_to_xy(width-14, height-2);
        printf("SEL:%-2d", selected);
        cursor_to_xy(2, height-2);
        act = getchar();
        switch (act) {
        case 104:
            help_process(width, height);
            break;
        
        case KEY_J: //J
            selected++;
            if (selected >= height - 7 && page < pages) {
                selected = 0;
                page++;
            } else if (selected >= height - 7 && page >= pages) {
                selected = height - 8;
                page = pages;
            }
            break;

        case KEY_K: //K
            selected--;
            if (selected < 0 && page > 0) {
                selected = height - 7;
                page--;
            } else if (selected < 0 && page <= 0) {
                selected = 0;
                page = 0;
            }
            break;

        case KEY_C: //C
            correct_process(list);
            break;
        
        case KEY_S: //S
            act = getchar();
            if (act == 'g') {
                *head = SortListBySurnameG(*head);
            } else if (act == 'l') {
                *head = SortListBySurnameL(*head);
            }
            break;

        case KEY_SLASH: // /
            reset_keypress();
            scanf("%d", &key);
            flush();
            key = FindWorkerByPersonalNumber(*head, key);
            selected = (key%(height - 7));
            page = key/(height-7);
            set_keypress();
            break;

        case KEY_X:
            if (atterntion_process(width, height, "Do you want delete worker?", 1) == 1) {
                *head = DeleteListElement(*head, GetPersonalNumber(GetData(list)));
            }
            break;

        case KEY_F:
            statistic_process(width, height, head);
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
    clrscr();
    home();
    reset_keypress();
    visible_cursor();

    if (head)
        DeleteList(head);

    // fclose(NULL); //FIXME: impliment deleting menus
    delete_menu(&output_menu);
    delete_menu(&input_menu);
    delete_menu(&main_menu); 

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
        case KEY_ESC:
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
    home();
    int x = (width - 66)/2 + 1;
    int y = 5;

    char act;

    while (1)
    {
        draw_atterntion_form(width, height);
        cursor_to_xy(x, y);
        printf("%64s", attention);
        act = getchar();
        switch (act)
        {
        case KEY_ENTER:
            return 1;

        case KEY_ESC:
            return 0;
        }
    }

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
        case KEY_ENTER:
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
        
        case KEY_ESC:
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
        case KEY_ENTER:
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
        
        case KEY_ESC:
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
    act = getchar();
    switch (act)
    {
    case KEY_ENTER:
        cursor_to_xy(x + 1, y + 1);
        visible_cursor();
        while(scanf("%d", &listsize) != 1) {
            home();
            error("Incorrect input. Try agian\nPress [Enter]");
            flush();
            getchar();
            cursor_to_xy(x + 1, y + 1);
        }
        flush();
        invisible_cursor();
        break;

    case KEY_ESC:
        return;
    }
    

    x = (width - 48)/2;

    for (int i = 0; i < listsize; i++) {
        draw_input_form(width, height, 0);
        visible_cursor();
        reset_keypress();
        cursor_to_xy(x + 18, y + 1);
        while(scanf("%ld", &personnelNumber) != 1) {
            home();
            error("Incorrect input. Try agian\nPress [Enter]");
            flush();
            getchar();
            cursor_to_xy(x + 18, y + 1);
        }
        flush();
                

        cursor_to_xy(x + 10, y + 2);
        while(scanf("%s", surname)!= 1) {
            home();
            error("Incorrect input. Try agian\nPress [Enter]");
            flush();
            getchar();
            cursor_to_xy(x + 10, y + 2);
        }
        flush();

        cursor_to_xy(x + 20, y + 3);
        while(scanf("%ld", &departmentNumber)!= 1) {
            home();
            error("Incorrect input. Try agian\nPress [Enter]");
            flush();
            getchar();
            cursor_to_xy(x + 20, y + 3);
        }
        flush();

        cursor_to_xy(x + 9, y + 4);
        while(scanf("%lf", &salary)!= 1) {
            home();
            error("Incorrect input. Try agian\nPress [Enter]");
            flush();
            getchar();
            cursor_to_xy(x + 9, y + 4);
        }
        flush();

        cursor_to_xy(x + 8, y + 5);
        while(scanf("%d", &themeNumber)!= 1) {
            home();
            error("Incorrect input. Try agian\nPress [Enter]");
            flush();
            getchar();
            cursor_to_xy(x + 8, y + 5);
        }
        flush();

        cursor_to_xy(x + 32, y + 6);
        while(scanf("%d", &durationOfWorkOnTheTopic)!= 1) {
            home();
            error("Incorrect input. Try agian\nPress [Enter]");
            flush();
            getchar();
            cursor_to_xy(x + 32, y + 6);
        }
        flush();

        cursor_to_xy(x + 11, y + 7);
        while(scanf("%ld", &jobCode) != 1) {
            home();
            error("Incorrect input. Try agian\nPress [Enter]");
            flush();
            getchar();
            cursor_to_xy(x + 1, y + 7);
        }
        flush();
        set_keypress();
        invisible_cursor();

        ResearchWorker *tmp = CreateResearchWorker(departmentNumber, 
                                                   personnelNumber, 
                                                   jobCode, 
                                                   surname,  
                                                   themeNumber, 
                                                   durationOfWorkOnTheTopic, 
                                                   salary);
        *head = AddListElement(*head, tmp);
    }
}

void write_dat_list_process(int width, int height, LinkedList **head) {
    set_keypress();
    invisible_cursor();
    clrscr();
    home();
    char act;
    char filename[36];

    int x = (width - 34)/2 + 1;
    int y = 5;

    while (1)
    {
        draw_dat_file_read_form(width, height);
        act = getchar();
        switch (act)
        {
        case KEY_ENTER:
            cursor_to_xy(x, y);
            visible_cursor();
            reset_keypress();
            scanf("%s", filename);
            flush();
            strcat(filename, ".dat");
            FILE *file = fopen(filename, "wb");
            if (!file) {
                home();
                error("Can't open file");
                head = NULL;
                getchar();
                return;
            }
            int ret = WriteListToFile(file, *head);

            if (ret != 0) {
                home();
                error("Can't write list to file");
                getchar();
            }
            fclose(file);
            reset_keypress();
            invisible_cursor();
            break;
        
        case KEY_ESC:
            reset_keypress();
            visible_cursor();
            return;
            break;
        
        default:
            break;
        }
    }
    


}

void write_txt_list_process(int width, int height, LinkedList **head) {
    set_keypress();
    invisible_cursor();
    clrscr();
    home();
    char act;
    char filename[36];

    int x = (width - 34)/2 + 1;
    int y = 5;

    while (1)
    {
        draw_txt_file_read_form(width, height);
        act = getchar();
        switch (act)
        {
        case KEY_ENTER:
            cursor_to_xy(x, y);
            visible_cursor();
            reset_keypress();
            scanf("%s", filename);
            flush();
            strcat(filename, ".txt");
            FILE *file = fopen(filename, "w");
            if (!file) {
                home();
                error("Can't open file");
                head = NULL;
                getchar();
                return;
            }
            int ret = WriteListToFile(file, *head);

            if (ret != 0) {
                home();
                error("Can't write list to file");
                getchar();
            }
            fclose(file);
            reset_keypress();
            invisible_cursor();
            break;
        
        case KEY_ESC:
            reset_keypress();
            visible_cursor();
            return;
            break;
        
        default:
            break;
        }
    }
}

struct stat {
    unsigned long theme;
    unsigned long staff;
    double fund;
};

#define STAT_INIT {0, 0, 0.0}

void statistic_process(int width, int height, LinkedList **head) {
    set_keypress();
    invisible_cursor();
    home();
    char act;

    int page = 0;
    int x = (width - 48)/2 + 1;
    int y = 5;

    int list_size = 0;
    int total = 0;

    for (LinkedList *k = *head; k != NULL; k = GetNext(k))
        list_size++;

    struct stat  *statistics = (struct stat *)malloc(list_size * sizeof(struct stat));

    //Зануляем массив тем
    for (int i = 0; i < list_size; i++) {
        statistics[i].theme = 0;
        statistics[i].staff = 0;
        statistics[i].fund = 0.0; 
    }

    for (LinkedList *i = *head; i != NULL; i = GetNext(i)){
        for (int j = 0; j < list_size; j++) {
            if (GetThemeNumber(GetData(i)) == statistics[j].theme) {
                statistics[j].staff++;
                statistics[j].fund += GetSalary(GetData(i));
                break;
            } else if (statistics[j].theme == 0) {
                statistics[j].theme = GetThemeNumber(GetData(i));
                statistics[j].staff = 1;
                statistics[j].fund = GetSalary(GetData(i));
                break;
            }
        }
    }

    for (int i = 0; (i < list_size) && (statistics[i].theme != 0); i++)total++;

    int pages = total/8;

    while (1)
    {
        draw_statistics_form(width, height);
        if (page != pages) {
            for (int i = 0 ; i < 8; i++) {
                cursor_to_xy(x, y + i);
                printf("%-08d ", statistics[i + (8 * page)].theme);
                printf("%-10d ", statistics[i + (8 * page)].staff);
                printf("%10.2lf", statistics[i + (8 * page)].fund);
            }
        } else if (page == pages) {
            for (int i = 0 ; i < total%8; i++) {
                cursor_to_xy(x, y + i);
                printf("%-08d ", statistics[i + (8 * page)].theme);
                printf("%-10d ", statistics[i + (8 * page)].staff);
                printf("%10.2lf", statistics[i + (8 * page)].fund);
            }
        }
        
        cursor_to_xy(x + 6, y + 8);
        printf("%03d", total);
        cursor_to_xy(x + 15, y + 8);
        printf("%03d", page);
        act = getchar();
        switch (act)
        {
        case KEY_ESC:
            free(statistics);  
            statistics = NULL; 
            return;

        case KEY_K:
            if (page > 0)
                page--;
            break;
        
        case KEY_J:
            if (page < pages)
                page++;
        }
    }
    
}