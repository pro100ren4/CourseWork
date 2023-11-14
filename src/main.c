#include <stdio.h>
#include "../inc/LinkedList.h"

#define DEBUG

int main(int argc, char const *argv[])
{
#ifdef DEBUG
    system("");//TODO: Call tests
#endif
    LinkedList *head = CreateList(5);
    DeleteList(head);
    return 0;
}