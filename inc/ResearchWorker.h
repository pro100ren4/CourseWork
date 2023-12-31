#ifndef _RESEARCHWORKER_H_
#define _RESEARCHWORKER_H_

#define DEBUG

typedef struct ResearchWorker ResearchWorker;
extern const int ResearchWorkerSize;

//GETER
unsigned long GetDepartmentNumber(ResearchWorker const * const researchWorker);
unsigned long GetPersonalNumber(ResearchWorker const * const researchWorker);
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

void DeleteResearchWorker(ResearchWorker *researchWorker);


#endif //_RESEARCHWORKER_H_