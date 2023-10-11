#ifndef _RESEARCHWORKER_H_* const
#define _RESEARCHWORKER_H_

typedef struct ResearchWorker ResearchWorker;


//GETER
unsigned long GetDepartmentNumber(ResearchWorker const * const researchWorker);
unsigned long GetPersonnelNumber(ResearchWorker const * const researchWorker);
unsigned long GetJobCode(ResearchWorker const * const researchWorker);

char* GetSurname(ResearchWorker const * const researchWorker);

unsigned int GetThemeNumber(ResearchWorker const * const researchWorker);
unsigned int GetDurationOfWorkOnTheTopic(ResearchWorker const * const researchWorker);

double GetSalary(ResearchWorker const * const researchWorker);

//SETER
void SetDepartmentNumber(ResearchWorker* const researchWorker, unsigned long departmentNumber);
void SetPersonnelNumber(ResearchWorker* const researchWorker, unsigned long personnelNumber);
void SetJobCode(ResearchWorker* const researchWorker, unsigned long jobCode); //, unsigned long jobCode

void SetSurname(ResearchWorker* const researchWorker, char surname[]);

void SetThemeNumber(ResearchWorker* const researchWorker, unsigned int themeNumber);
void SetDurationOfWorkOnTheTopic(ResearchWorker* const researchWorker, unsigned int durationOfWorkOnTheTopic);

void SetSalary(ResearchWorker* const researchWorker, double salary);

ResearchWorker* CreateResearchWorker( unsigned long departmentNumber, unsigned long personnelNumber, unsigned long jobCode, char surname[], unsigned int themeNumber, unsigned int durationOfWorkOnTheTopi, double salary);

ResearchWorker* CreateResearchWorkerFromConsole();

#endif //_RESEARCHWORKER_H_