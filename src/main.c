#include <stdio.h>
#include "../inc/ResearchWorker.h"

int main(int argc, char const *argv[])
{
    ResearchWorker* researchWorker = CreateResearchWorkerFromConsole();
    char* surname = GetSurname(researchWorker);
    surname[0] = 'B';
    return 0;
}