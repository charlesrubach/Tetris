cmake_minimum_required(VERSION 4.0)
project(Tetris C)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
)

FetchContent_MakeAvailable(raylib)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(Tetris)

target_sources(Tetris PRIVATE
        src/main.c
        src/game.c
        src/playfield.c
        src/tetromino.c
        src/randomizer.c
        src/renderer.c
        src/input.c
        src/arena.c
)

target_include_directories(Tetris PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(Tetris PRIVATE raylib)
