cmake_minimum_required(VERSION 3.10)
project(RogueGame C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(Curses REQUIRED)

add_executable(RogueGame main.c)

target_link_libraries(RogueGame
        PRIVATE
        SDL2::SDL2
        ${CURSES_LIBRARIES}
)

target_include_directories(RogueGame
        PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${CURSES_INCLUDE_DIR}
)
