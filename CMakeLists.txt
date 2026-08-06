cmake_minimum_required(VERSION 4.0)
project(Tetris C)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG master
)

FetchContent_MakeAvailable(raylib)

set(CMAKE_C_STANDARD 11)

add_executable(Tetris src/main.c
        src/game.c
        include/game.h
        src/grid.c
        include/grid.h
        src/tetromino.c
        include/tetromino.h
        src/randomizer.c
        include/randomizer.h
        src/renderer.c
        include/renderer.h
        src/input.c
        include/input.h
        include/config.h
        include/utilities.h
)

target_include_directories(Tetris PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)


target_link_libraries(Tetris PRIVATE raylib)