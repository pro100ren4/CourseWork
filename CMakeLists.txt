cmake_minimum_required(VERSION 3.27)

project(ResearchInstituteProg)

set(PROJECT_SOURCES
    src/main.c
    src/LinkedList.c
    src/ResearchWorker.c
)

set(PORJECT_INCLUDES
    inc/LinkedList.h
    inc/ResearchWorker.h
)

add_executable(${PROJECT_NAME}
    ${PORJECT_INCLUDES}
    ${PROJECT_SOURCES}
)