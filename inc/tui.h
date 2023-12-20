#ifndef _TUI_H_
#define _TUI_H_

#include "LinkedList.h"

#define menu_line_size 32

void initialize_term_xy(int *x, int *y);

struct menu_t {
    char **menu_text;
    int menu_size;
    int chosen;
    int x, y;
    int (*menu_callback)(struct menu_t *);
    struct menu_t *subs;
};

struct menu_t create_menu(char **menu_text, int menu_size, int (*menu_callback)(struct menu_t *), int x, int y);
void delete_menu(struct menu_t *menu);

void add_menu_sub(struct menu_t *main_menu, struct menu_t *sub_menu, int position);

void print_menu(struct menu_t *menu);
// int check_menu_input(struct menu_t *menu);
// void foo(void);
void menu_process(struct menu_t *menu);
// int check_main_menu(struct menu_t *menu);


void draw_correct_form(int width, int height);
void draw_table_form(int width, int height);
void draw_menu_form(int width, int height);
void draw_help_form(int width, int height);

void set_keypress(void);
void reset_keypress(void);

LinkedList* print_linked_list_data(LinkedList *head, int width, int height, int selected, int page);
#endif //_TUI_H_