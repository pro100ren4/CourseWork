#ifndef _LINKEDLIST_LIST_H_
#define _LINKEDLIST_LIST_H_

#include "ResearchWorker.h"
#include <stdio.h>

typedef struct LinkedList LinkedList;

LinkedList* CreateList();
void DeleteList(LinkedList* head);

// FIXME: Do normal function prototypes
LinkedList* AddListElement(LinkedList* head, ResearchWorker* newResearchWorker);
LinkedList* DeleteListElement(LinkedList* head, ResearchWorker* researchWorker);

LinkedList* CreateList(unsigned int length);
void DeleteList(LinkedList* head);

LinkedList* ReadListFromFile(FILE* file);
int WriteListToFile(FILE* file, LinkedList* head);

#endif //_LINKEDLIST_LIST_H_