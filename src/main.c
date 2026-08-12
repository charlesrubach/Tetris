#include <time.h>
#include <stdio.h>

#include "raylib.h"
#include "arena.h"
#include "game.h"
#include "config.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;

    InitWindow(screenWidth, screenHeight, "raylib Tetris by Charles Rubach");
    SetTargetFPS(TARGE_FPS);               // Set our game to run at 60 frames-per-second

    SetRandomSeed((unsigned int) time(NULL)); // set random seed using the time
    // Arena init
    Arena arena = arena_init(ARENA_CAPACITY);
    if (arena.buffer == NULL) {
        fprintf(stderr, "Arena failed to initialize.\n");
        return 1;
    }

    Game *game = arena_alloc_type(&arena, Game);
    if (game == NULL) {
        fprintf(stderr, "Failed to allocate space for the Game object\n");
        return 1;
    }
    GameInit(game, &arena);


    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        GameLoop(game);
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    arena_free(&arena);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

