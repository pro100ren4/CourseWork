#ifndef _LINKEDLIST_LIST_H_
#define _LINKEDLIST_LIST_H_

#define DEBUG

#include <stdio.h>

#include "ResearchWorker.h"

typedef struct LinkedList LinkedList;

// FIXME: Do normal function prototypes
LinkedList *AddListElement(LinkedList *head, ResearchWorker *newResearchWorker, unsigned long workerPersonalNumber);
LinkedList *DeleteListElement(LinkedList *head, unsigned long workerPersonalNumber);
LinkedList *CorrectListElement(LinkedList *head, unsigned long workerPersonalNumber);

LinkedList *CreateList(unsigned int length);
void DeleteList(LinkedList *head);

LinkedList *ReadListFromFile(FILE *file);
int WriteListToFile(FILE *file, LinkedList *head);

void PrintList(LinkedList *head);

#endif //_LINKEDLIST_LIST_H_