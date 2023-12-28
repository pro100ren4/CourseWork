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

const int LinkedListSize = sizeof(LinkedList);

void SetNext(LinkedList *list, LinkedList *next) {
    list->next = next;
}

void SetPrev(LinkedList *list, LinkedList *prev) {
    list->prev = prev;
}

void SetData(LinkedList *list, ResearchWorker* data) {
    list->data = data;
}


LinkedList *GetNext(LinkedList *list) {
    return list->next;
}

LinkedList *GetPrev(LinkedList *list) {
    return list->prev;
}

ResearchWorker *GetData(LinkedList *list) {
    return list->data;
}

LinkedList *AddListElementByPersonalNumber(LinkedList *head, 
                                           ResearchWorker *newResearchWorker, 
                                           unsigned long workerPersonalNumber) {
    LinkedList *tmp = head;
    LinkedList *newNode = (LinkedList *)malloc(LinkedListSize);
    newNode->data = newResearchWorker;
    int success = 0;
    while(GetPersonnelNumber(tmp->data) != workerPersonalNumber) {
        if (GetPersonnelNumber(GetData(tmp)) == workerPersonalNumber)
            success = 1;
        tmp = tmp->next;
    }

    newNode->next = tmp->next;
    newNode->prev = tmp;
    tmp->next = newNode;

    return (success?head:NULL);
}

LinkedList *AddListElement(LinkedList *head, ResearchWorker *newResearchWorker) {
#ifdef DEBUG
    home();
    message("Called AddListElement");
#endif
    LinkedList *tmp = head;
    LinkedList *newNode = (LinkedList *)malloc(LinkedListSize);
    newNode->data = newResearchWorker;
    if (!head) {
        home();
        warning("List empty!");
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->data = newResearchWorker;
        return newNode;
    }

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
    home();
    message("Called DeleteListElement");
#endif
    LinkedList *tmp = head;
    LinkedList *delNode;

    while(GetPersonnelNumber(tmp->data) != workerPersonalNumber) 
        tmp = tmp->next;

    delNode = tmp;
    tmp->next->prev = tmp->prev;  
    tmp->prev->next = tmp->next;
    free(delNode);

#ifdef DEBUG
    message("DeleteListElement completed");
#endif
}

LinkedList *CreateList(unsigned int length) {
#ifdef DEBUG
    home();
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
    home();
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

LinkedList *ReadListFromFile(FILE *file, LinkedList *head) {
#ifdef DEBUG
    home();
    message("ReadListFromFile was called");
#endif

    if(!file) {
        home();
        error("Can't read file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_length = ftell(file)/ResearchWorkerSize;
    LinkedList* curr = NULL;
    ResearchWorker *tmp = (ResearchWorker *)malloc(ResearchWorkerSize);
    rewind(file);
    for(int i = 0;i < file_length; i++)
    {
        LinkedList* node = (LinkedList*)malloc(LinkedListSize);
        fread(&tmp, ResearchWorkerSize, 1, file);
        node->data = tmp;
        node->next = NULL;
        node->prev = NULL;

        if(head == NULL)
        {
            head = node;
            curr = node;
        }
        else
        {
            curr->next = node;
            node->prev = curr;
            curr = node;
        }
    }
#ifdef DEBUG
    message("ReadListFromFile completed");
#endif
    return head;
}

LinkedList *ReadListFromFilePath(char *path, char *mode, LinkedList *head) {
    FILE *file = fopen(path, mode);
    if (!file) { 
        error("Can't open file");
    }
    
    head = ReadListFromFile(file, head);
    fclose(file);
    return head;
}

int WriteListToFile(FILE *file, LinkedList *head) {
    if(head == NULL)
    {
        error("warn<write_file>: The list is empty");
        return 0;
    }
    while(head != NULL)
    {
        if(fwrite(&(head->data), ResearchWorkerSize, 1, file)!= 1)
        {
            error("error<write_file>: Can't write file");
            return -1;
        }
        head = head->next;
    }
    return 0;
}
