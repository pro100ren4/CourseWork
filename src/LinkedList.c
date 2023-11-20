#include "../inc/LinkedList.h"

#include <stdlib.h>

#include "../inc/ResearchWorker.h"
#include "../inc/utils.h"
#include "../inc/assertimp.h"

typedef struct LinkedList {
    LinkedList *next;
    LinkedList *prev;
    ResearchWorker *data;
} LinkedList;

LinkedList *AddListElement(LinkedList *head, ResearchWorker *newResearchWorker, unsigned long workerPersonalNumber) {
#ifdef DEBUG
    message("Called AddListElement");
#endif
    LinkedList *tmp = head;
    LinkedList *newNode;
    newNode->data = newResearchWorker;

    while(GetPersonnelNumber(tmp->data) != workerPersonalNumber) tmp = tmp->next;

    newNode->next = tmp->next;
    newNode->prev = tmp;
    tmp->next = newNode;

#ifdef DEBUG
    message("AddListElement completed");
#endif

    return head;
}

LinkedList *DeleteListElement(LinkedList *head, unsigned long workerPersonalNumber) {
#ifdef DEBUG
    message("Called DeleteListElement");
#endif
    LinkedList *tmp = head;
    LinkedList *delNode;

    while(GetPersonnelNumber(tmp->data) != workerPersonalNumber) tmp = tmp->next;
    delNode = tmp->next;
    tmp->next = tmp->next->next;
    free(delNode);

#ifdef DEBUG
    message("DeleteListElement completed");
#endif
}

LinkedList *CorrectListElement(LinkedList *head, unsigned long workerPersonalNumber) {
    
}

LinkedList *CreateList(unsigned int length) {
#ifdef DEBUG
    message("Called CreateList");
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
    message("CreateList completed");
#endif

    return head;
}

void DeleteList(LinkedList *head) {
#ifdef DEBUG
    message("Called DeleteList");
#endif
    while (head->next != NULL) {
        LinkedList *curr = head;
        head = head->next;
        free(curr);
    }
#ifdef DEBUG
    message("DeleteList completed7");
#endif
}

LinkedList *ReadListFromFile(FILE *file);
int WriteListToFile(FILE *file, LinkedList *head);

void PrintList(LinkedList *head);