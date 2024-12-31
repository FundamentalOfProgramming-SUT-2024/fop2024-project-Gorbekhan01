cmake_minimum_required(VERSION 3.10)
project(RogueGame)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(RogueGame main.c)

target_link_libraries(RogueGame ${CURSES_LIBRARIES})
