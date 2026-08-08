//
// Created by Charles on 8/6/2026.
//

#include "game.h"

void Game_Init(Game *game, Arena *arena) {
    game->arena = arena;
    game->background_color = CUSTOM_COLOR_GAME_BACKGROUND;
    game->score = 0;
    game->level = 0;
    PlayField_Init(game);
    game->current_piece = Tetromino_Create(game, TETROMINO_J);
    game->next_piece = Tetromino_Create(game, TETROMINO_S);
    game->drop_interval = INITIAL_DROP_INTERVAL;
    game->last_drop_time = GetTime();
}

void Game_Loop(Game *game) {
    // Handle Input
    //----------------------------------------------------------------------------------
    Game_Handle_Input(game);

    // Update
    //----------------------------------------------------------------------------------
    Game_Update(game);

    // Draw
    //----------------------------------------------------------------------------------
    Game_Render(game);
}

void Game_Handle_Input(Game *game) {

}

void Game_Update(Game *game) {
    const double now = GetTime();

    if ( now - game->last_drop_time >= game->drop_interval ) {
        game->current_piece->pos.y++;
        game->last_drop_time = now;
    }
}

void Game_Render(const Game *game) {
    BeginDrawing();

    ClearBackground(game->background_color);
    PlayField_Render(game);

    EndDrawing();
}