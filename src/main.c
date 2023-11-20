#include <stdio.h>
#include <stdlib.h>

#include "../inc/LinkedList.h"
#include "../inc/utils.h"
#include "../inc/tui.h"

#define DEBUG

static int height, width;

int main(int argc, char const *argv[])
{
#ifdef DEBUG
    //system("./test_utils");//TODO: Call tests
#endif
    //invisible_cursor();
    initialize_term_xy(&width, &height);
    clrscr();
    home();
    if (height <= 17 && width <= 74) {
        printf("Plese make your terminal bigger. It's too small\n");
        return 1;
    }

    draw_table_form(width, height);
    while (1) {
        draw_correct_form(width, height);
    }
    // LinkedList *head = CreateList(5);
    // DeleteList(head);
    visible_cursor();
    return 0;
}