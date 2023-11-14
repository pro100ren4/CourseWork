#include "../inc/LinkedList.h"

#include <stdlib.h>

#include "../inc/ResearchWorker.h"

typedef struct LinkedList {
    LinkedList *next;
    LinkedList *prev;
    ResearchWorker *data;
} LinkedList;

// FIXME: Do normal function prototypes
LinkedList *AddListElement(LinkedList *head, ResearchWorker *newResearchWorker, unsigned long workerPersonalNumber);
LinkedList *DeleteListElement(LinkedList *head, unsigned long workerPersonalNumber);
LinkedList *CorrectListElement(LinkedList *head, unsigned long workerPersonalNumber);

LinkedList *CreateList(unsigned int length) {
#ifdef DEBUG
    printf("[%s:%d] Called CreateList\n", __FUNCTION__, __LINE__);
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

    return head;
}

void DeleteList(LinkedList *head) {
#ifdef DEBUG
    printf("[%s:%d] Called DeleteList\n", __FUNCTION__, __LINE__);
#endif
    while (head->next != NULL) {
        LinkedList *curr = head;
        head = head->next;
        free(curr);
    }
}

LinkedList *ReadListFromFile(FILE *file);
int WriteListToFile(FILE *file, LinkedList *head);

void PrintList(LinkedList *head);