#include "../inc/LinkedList.h"

#include <stdlib.h>
#include <string.h>

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
    while(GetPersonalNumber(tmp->data) != workerPersonalNumber) {
        if (GetPersonalNumber(GetData(tmp)) == workerPersonalNumber)
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
    if (GetPersonalNumber(GetData(head)) == workerPersonalNumber) {
        LinkedList *tmp = GetNext(head);
        SetPrev(tmp, NULL);
        free(head);
        return tmp;
    }

    LinkedList *tmp = head;
    LinkedList *delNode;
    int success = 0;

    while (GetPersonalNumber(tmp->data) != workerPersonalNumber && tmp != NULL) {
        tmp = tmp->next;
    }
    if (GetPersonalNumber(GetData(tmp)) == workerPersonalNumber)
        success = 1; 

    if (success) {
        delNode = tmp;
        tmp->next->prev = tmp->prev;  
        tmp->prev->next = tmp->next;
        free(delNode);
    }

#ifdef DEBUG
    message("DeleteListElement completed");
#endif

    return head;
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
    if (!head){
        home();
        message("List is empty");
        return;
    }
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
    LinkedList* curr = head;
    ResearchWorker *tmp;
    rewind(file);
    for(int i = 0;i < file_length; i++)
    {
        tmp = (ResearchWorker *)malloc(ResearchWorkerSize);
        LinkedList* node = (LinkedList*)malloc(LinkedListSize);        
        if (fread(tmp, ResearchWorkerSize, 1, file) != 1) {
            home();
            error("Can't read list from file");
            return NULL;
        }
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
    if (head == NULL) {
        home();
        error("The list is empty");
        return -1;
    }

    ResearchWorker *tmp = GetData(head);

    while (head != NULL) {
        tmp = GetData(head);
        if (fwrite(tmp, ResearchWorkerSize, 1, file)!= 1) {
            home();
            error("Can't write file");
            return -1;
        }
        head = GetNext(head);
    }
    return 0;
}

LinkedList *SortListBySurnameG(LinkedList *head) {
    LinkedList *i = head, *j = head;
    ResearchWorker *tmp;
    int list_size = 0;

    char *str1, *str2;

    for (LinkedList *k = head; k != NULL; k = GetNext(k))
        list_size++;
    
    for (i = head; i != NULL; i = GetNext(i)) {
        for (j = head; GetNext(j) != NULL; j = GetNext(j)) {
            str1 = GetSurname(GetData(j));
            str2 = GetSurname(GetData(GetNext(j)));
            if (strcmp(str1, str2) > 0) {
                tmp = GetData(GetNext(j));
                SetData(GetNext(j), GetData(j));
                SetData(j, tmp);
            }
            free(str1);
            free(str2);
        }
    }

    return head;
}

LinkedList *SortListBySurnameL(LinkedList *head) {
    LinkedList *i = head, *j = head;
    ResearchWorker *tmp;
    int list_size = 0;

    char *str1, *str2;

    for (LinkedList *k = head; k != NULL; k = GetNext(k))
        list_size++;
    
    for (i = head; i != NULL; i = GetNext(i)) {
        for (j = head; GetNext(j) != NULL; j = GetNext(j)) {
            str1 = GetSurname(GetData(j));
            str2 = GetSurname(GetData(GetNext(j)));
            if (strcmp(str1, str2) < 0) {
                tmp = GetData(GetNext(j));
                SetData(GetNext(j), GetData(j));
                SetData(j, tmp);
            }
            free(str1);
            free(str2);
        }
    }

    return head;
}

int FindWorkerByPersonalNumber(LinkedList *head, unsigned long key) {
    int success = 0;
    int selected = 0;
    LinkedList *tmp = head;
    while (GetNext(tmp) != NULL && GetPersonalNumber(GetData(tmp)) != key) {
        selected++;
        tmp = GetNext(tmp);
    }
    
    if (GetPersonalNumber(GetData(tmp)) == key) {
        success = selected;
    }
    return success;
}
