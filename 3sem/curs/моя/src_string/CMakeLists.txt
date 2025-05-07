cmake_minimum_required(VERSION 3.10)
project(my_string)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

add_library(${PROJECT_NAME} STATIC my_string.c)
target_link_libraries(${PROJECT_NAME} check m pthread rt)

enable_testing()

if(BUILD_TESTING)
    add_executable(tests tests/tests.c)
    target_link_libraries(tests ${PROJECT_NAME})
endif()
