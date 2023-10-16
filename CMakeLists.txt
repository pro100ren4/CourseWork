cmake_minimum_required(VERSION 3.27)

project(ResearchInstituteProg)

set(${PROJECT_NAME}_SOURCES
    src/main.c
    src/LinkedList.c
    src/ResearchWorker.c
)

set(${PROJECT_NAME}_INCLUDES
    inc/LinkedList.h
    inc/ResearchWorker.h
)

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_INCLUDES}
    ${${PROJECT_NAME}_SOURCES}
)