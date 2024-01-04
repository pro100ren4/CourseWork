cmake_minimum_required(VERSION 3.16)

project(ResearchInstituteProg)
enable_testing()

set(${PROJECT_NAME}_SOURCES
    src/main.c
    src/LinkedList.c
    src/ResearchWorker.c
    src/tui.c
)

set(${PROJECT_NAME}_INCLUDES
    inc/LinkedList.h
    inc/ResearchWorker.h
    inc/utils.h
    inc/tui.h
)

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_INCLUDES}
    ${${PROJECT_NAME}_SOURCES}
)

# add_executable(test_utils
#     inc/utils.h
#     test/test_utils.c
# )

# add_test(utils "./bin/test_utils")
# add_test(utils "./bin/test_ResearchWorker")
# add_test(utils "./bin/test_LinkedList")