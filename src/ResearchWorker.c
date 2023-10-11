#include "../inc/ResearchWorker.h"
#include <stdlib.h>

typedef struct ResearchWorker
{
    unsigned long departmentNumber, personnelNumber, jobCode;
    char surname[20];
    unsigned int themeNumber, durationOfWorkOnTheTopic;
    double salary;
} ResearchWorker;

//GETER
unsigned long GetDepartmentNumber(ResearchWorker const * const researchWorker){return researchWorker->departmentNumber;}
unsigned long GetPersonnelNumber(ResearchWorker const * const researchWorker){return researchWorker->personnelNumber;}
unsigned long GetJobCode(ResearchWorker const * const researchWorker){return researchWorker->jobCode;}

char* GetSurname(ResearchWorker const * const researchWorker){return researchWorker->surname;}

unsigned int GetThemeNumber(ResearchWorker const * const researchWorker){return researchWorker->themeNumber;}
unsigned int GetDurationOfWorkOnTheTopic(ResearchWorker const * const researchWorker){return researchWorker->durationOfWorkOnTheTopic;}

double GetSalary(ResearchWorker const * const researchWorker){return researchWorker->salary;}

//SETER
void SetDepartmentNumber(ResearchWorker* const researchWorker, unsigned long departmentNumber)
{
    researchWorker->departmentNumber = departmentNumber;
}
void SetPersonnelNumber(ResearchWorker* const researchWorker, unsigned long personnelNumber)
{
    researchWorker->personnelNumber = personnelNumber;
}
void SetJobCode(ResearchWorker* const researchWorker, unsigned long jobCode)
{
    researchWorker->jobCode = jobCode;
}

void SetSurname(ResearchWorker* const researchWorker, char surname[])
{
    //FIXME: Impliment function
}

void SetThemeNumber(ResearchWorker* const researchWorker, unsigned int themeNumber)
{
    researchWorker->themeNumber = themeNumber;
}
void SetDurationOfWorkOnTheTopic(ResearchWorker* const researchWorker, unsigned int durationOfWorkOnTheTopic)
{
    researchWorker->durationOfWorkOnTheTopic = durationOfWorkOnTheTopic;
}

void SetSalary(ResearchWorker* const researchWorker, double salary)
{
    researchWorker->salary = salary;
}

ResearchWorker* CreateResearchWorker( unsigned long departmentNumber, unsigned long personnelNumber, unsigned long jobCode, char surname[], unsigned int themeNumber, unsigned int durationOfWorkOnTheTopi, double salary)
{
    ResearchWorker* researchWorker = (ResearchWorker*)malloc(sizeof(ResearchWorker));
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
    unsigned long departmentNumber, personnelNumber, jobCode;
    char surname[20];
    unsigned int themeNumber, durationOfWorkOnTheTopic;
    double salary;

    
}
