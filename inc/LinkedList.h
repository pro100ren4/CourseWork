#ifndef _LINKEDLIST_LIST_H_
#define _LINKEDLIST_LIST_H_

#define DEBUG

#include <stdio.h>

#include "ResearchWorker.h"

typedef struct LinkedList LinkedList;
extern const int LinkedListSize;

void SetNext(LinkedList *list, LinkedList *next);
void SetPrev(LinkedList *list, LinkedList *prev);
void SetData(LinkedList *list, ResearchWorker* data);

LinkedList *GetNext(LinkedList *list);
LinkedList *GetPrev(LinkedList *list);
ResearchWorker *GetData(LinkedList *list);

// FIXME: Do normal function prototypes
LinkedList *AddListElementByPersonalNumber(LinkedList *head, ResearchWorker *newResearchWorker, unsigned long workerPersonalNumber);
LinkedList *AddListElement(LinkedList *head, ResearchWorker *newResearchWorker);
LinkedList *DeleteListElement(LinkedList *head, unsigned long workerPersonalNumber);

LinkedList *CreateList(unsigned int length);
void DeleteList(LinkedList *head);

LinkedList *ReadListFromFile(FILE *file, LinkedList *head);
LinkedList *ReadListFromFilePath(char *path, char *mode, LinkedList *head);
int WriteListToFile(FILE *file, LinkedList *head);

LinkedList *SortListByPersonalSurname(LinkedList *head);

#endif //_LINKEDLIST_LIST_H_