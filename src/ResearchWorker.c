#include "../inc/ResearchWorker.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/tui.h"
#include "../inc/utils.h"

typedef struct ResearchWorker
{
    unsigned long departmentNumber, personnelNumber, jobCode;
    char surname[20];
    unsigned int themeNumber, durationOfWorkOnTheTopic;
    double salary;
} ResearchWorker;

const int ResearchWorkerSize = sizeof(ResearchWorker);

//GETER
unsigned long GetDepartmentNumber(ResearchWorker const * const researchWorker) {
    return researchWorker->departmentNumber;
}

unsigned long GetPersonalNumber(ResearchWorker const * const researchWorker) {
    return researchWorker->personnelNumber;
}

unsigned long GetJobCode(ResearchWorker const * const researchWorker) {
    return researchWorker->jobCode;
}

// Allocate 20 bytes of memory. Needed to be deallocated 
char* GetSurname(ResearchWorker const * const researchWorker)
{
    char *surname = (char *)malloc(20);
    strncpy(surname, researchWorker->surname, 19);
    return surname;
}

unsigned int GetThemeNumber(ResearchWorker const * const researchWorker) {
    return researchWorker->themeNumber;
}

unsigned int GetDurationOfWorkOnTheTopic(ResearchWorker const * const researchWorker) {
    return researchWorker->durationOfWorkOnTheTopic;
}

double GetSalary(ResearchWorker const * const researchWorker) {
    return researchWorker->salary;
}

//SETER
void SetDepartmentNumber(ResearchWorker* const researchWorker, 
                         unsigned long departmentNumber)
{
    researchWorker->departmentNumber = departmentNumber;
}

void SetPersonnelNumber(ResearchWorker* const researchWorker, 
                        unsigned long personnelNumber)
{
    researchWorker->personnelNumber = personnelNumber;
}

void SetJobCode(ResearchWorker* const researchWorker, unsigned long jobCode)
{
    researchWorker->jobCode = jobCode;
}

void SetSurname(ResearchWorker* const researchWorker, char surname[])
{
    strncpy(researchWorker->surname, surname, 19);
}

void SetThemeNumber(ResearchWorker* const researchWorker, unsigned int themeNumber)
{
    researchWorker->themeNumber = themeNumber;
}

void SetDurationOfWorkOnTheTopic(ResearchWorker* const researchWorker, 
                                 unsigned int durationOfWorkOnTheTopic)
{
    researchWorker->durationOfWorkOnTheTopic = durationOfWorkOnTheTopic;
}

void SetSalary(ResearchWorker* const researchWorker, double salary)
{
    researchWorker->salary = salary;
}

ResearchWorker* CreateResearchWorker( unsigned long departmentNumber, 
                                      unsigned long personnelNumber, 
                                      unsigned long jobCode, 
                                      char surname[], 
                                      unsigned int themeNumber,
                                      unsigned int durationOfWorkOnTheTopi, 
                                      double salary)
{
    ResearchWorker* const researchWorker = (ResearchWorker*)malloc(sizeof(ResearchWorker));
    SetDepartmentNumber(researchWorker, departmentNumber);
    SetPersonnelNumber(researchWorker, personnelNumber);
    SetJobCode(researchWorker, jobCode);
    SetSurname(researchWorker, surname);
    SetThemeNumber(researchWorker, themeNumber);
    SetDurationOfWorkOnTheTopic(researchWorker, durationOfWorkOnTheTopi);
    SetSalary(researchWorker, salary);
    return researchWorker;
}

ResearchWorker* CreateResearchWorkerFromConsole()
{
    home();
    clrscr();
    reset_keypress();
    visible_cursor();

    unsigned long departmentNumber, personnelNumber, jobCode;
    char surname[20];
    unsigned int themeNumber, durationOfWorkOnTheTopic;
    double salary;

    printf("enter department number: ");
    while(scanf("%ld", &departmentNumber)!=1)
    {
        flush();
        printf("[error] incorrect input. try again");
    }
    flush();

    printf("enter personnel number: ");
    while(scanf("%ld", &personnelNumber)!=1)
    {
        flush();
        printf("[error] incorrect input. try again");
    }
    flush();

    printf("enter job code: ");
    while(scanf("%ld", &jobCode)!=1)
    {
        flush();
        printf("[error] incorrect input. try again");
    }
    flush();

    printf("enter surname: ");
    while(scanf("%19s", &surname)!=1)
    {
        flush();
        printf("[error] incorrect input. try again");
    }
    flush();

    printf("enter theme number: ");
    while(scanf("%d", &themeNumber)!=1)
    {
        flush();
        printf("[error] incorrect input. try again");
    }
    flush();

    printf("enter duration of work on the topic: ");
    while(scanf("%d", &durationOfWorkOnTheTopic)!=1)
    {
        flush();
        printf("[error] incorrect input. try again");
    }
    flush();

    printf("enter salary: ");
    while(scanf("%lf", &salary)!=1)
    {
        flush();
        printf("[error] incorrect input. try again");
    }
    flush();

    return CreateResearchWorker(departmentNumber, 
                                personnelNumber, 
                                jobCode, 
                                surname, 
                                themeNumber, 
                                durationOfWorkOnTheTopic, 
                                salary);
}

void DeleteResearchWorker(ResearchWorker *researchWorker) {
    free(researchWorker);
}
