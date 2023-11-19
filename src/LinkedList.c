#include "../inc/LinkedList.h"

#include <stdlib.h>

#include "../inc/ResearchWorker.h"
#include "../inc/utils.h"

typedef struct LinkedList {
    LinkedList *next;
    LinkedList *prev;
    ResearchWorker *data;
} LinkedList;

LinkedList *AddListElement(LinkedList *head, ResearchWorker *newResearchWorker, unsigned long workerPersonalNumber) {
#ifdef DEBUG
    set_display_atrib(B_BLUE);
    printf("[%s:%d] Called AddListElement\n", __FUNCTION__, __LINE__);
    resetcolor();
#endif
    LinkedList *tmp = head;
    LinkedList *newNode;
    newNode->data = newResearchWorker;

    while(GetPersonnelNumber(tmp->data) != workerPersonalNumber) tmp = tmp->next;

    newNode->next = tmp->next;
    newNode->prev = tmp;
    tmp->next = newNode;

#ifdef DEBUG
    set_display_atrib(B_BLUE);
    printf("[%s:%d] AddListElement return %p\n", __FUNCTION__, __LINE__, head);
    resetcolor();
#endif

    return head;
}

LinkedList *DeleteListElement(LinkedList *head, unsigned long workerPersonalNumber) {
#ifdef DEBUG
    set_display_atrib(B_BLUE);
    printf("[%s:%d] Called DeleteListElement\n", __FUNCTION__, __LINE__);
    resetcolor();
#endif
    LinkedList *tmp = head;
    LinkedList *delNode;

    while(GetPersonnelNumber(tmp->data) != workerPersonalNumber) tmp = tmp->next;
    delNode = tmp->next;
    tmp->next = tmp->next->next;
    free(delNode);

#ifdef DEBUG
    set_display_atrib(B_BLUE);
    printf("[%s:%d] DeleteListElement complete work\n", __FUNCTION__, __LINE__);
    resetcolor();
#endif
}

LinkedList *CorrectListElement(LinkedList *head, unsigned long workerPersonalNumber) {
    
}

LinkedList *CreateList(unsigned int length) {
#ifdef DEBUG
    set_display_atrib(B_BLUE);
    printf("[%s:%d] Called CreateList\n", __FUNCTION__, __LINE__);
    resetcolor();
#endif
    LinkedList *head = NULL;
    LinkedList *curr = NULL;

    for (; length > 0; length--) {
        LinkedList *node = (LinkedList*)malloc(sizeof(LinkedList));
        node->data = CreateResearchWorkerFromConsole();
        node->next = NULL;
        node->prev = NULL;

        if (!head) {
            head = node;
            curr = node;
        } else {
            curr->next = node;
            node->prev = curr;
            curr = node;
        }
    }
#ifdef DEBUG
    set_display_atrib(B_BLUE);
    printf("[%s:%d] CreateList return %p\n", __FUNCTION__, __LINE__, head);
    resetcolor();
#endif

    return head;
}

void DeleteList(LinkedList *head) {
#ifdef DEBUG
    set_display_atrib(B_BLUE);
    printf("[%s:%d] Called DeleteList\n", __FUNCTION__, __LINE__);
    resetcolor();
#endif
    while (head->next != NULL) {
        LinkedList *curr = head;
        head = head->next;
        free(curr);
    }
#ifdef DEBUG
    set_display_atrib(B_BLUE);
    printf("[%s:%d] DeleteList complete work\n", __FUNCTION__, __LINE__);
    resetcolor();
#endif
}

LinkedList *ReadListFromFile(FILE *file);
int WriteListToFile(FILE *file, LinkedList *head);

void PrintList(LinkedList *head);