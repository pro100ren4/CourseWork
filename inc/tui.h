#ifndef _TUI_H_
#define _TUI_H_

#include "LinkedList.h"

#define menu_line_size 32

#define KEY_J 106
#define KEY_K 107
#define KEY_H 104
#define KEY_C 99
#define KEY_X 120
#define KEY_SLASH 47
#define KEY_F 102
#define KEY_S 115
#define KEY_ESC 27
#define KEY_ENTER 10

void initialize_term_xy(int *x, int *y);

void flush();

struct menu_t {
    char **menu_text;
    int menu_size;
    int chosen;
    int x, y;
    void (*menu_callback)(struct menu_t *, LinkedList **);
    struct menu_t *subs;
};

struct menu_t create_menu(char **menu_text, 
                          int menu_size, 
                          void (*menu_callback)(struct menu_t *, LinkedList **), 
                          int x, int y);

void delete_menu(struct menu_t *menu);

void add_menu_sub(struct menu_t *main_menu, 
                  struct menu_t *sub_menu, 
                  int position);

void print_menu(struct menu_t *menu);
// int check_menu_input(struct menu_t *menu);
// void foo(void);
void menu_process(struct menu_t *menu, LinkedList **head);
// int check_main_menu(struct menu_t *menu);


void draw_correct_form(int width, int height, int selected);
void draw_table_form(int width, int height);
void draw_menu_form(int width, int height);
void draw_help_form(int width, int height);

void set_keypress(void);
void reset_keypress(void);

LinkedList* print_linked_list_data(LinkedList *head, 
                                   int width, 
                                   int height, 
                                   int selected, 
                                   int page);
void draw_input_form(int width, int height, int selected);
ResearchWorker *enter_worker_from_console(void);
void draw_data_to_correct(int width, int height, LinkedList *list);
void draw_dat_file_read_form(int width, int height);
void draw_txt_file_read_form(int width, int height);
void draw_enter_listsize_form(int width, int height);


#endif //_TUI_H_