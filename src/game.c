#include "game.h"

#include <string.h>
#include <stdio.h>

#include "ui.h"

void GameInit(Game *game, Arena *arena) {
    game->arena = arena;
    game->background_color = CUSTOM_COLOR_GAME_BACKGROUND;
    game->input = (Input){
        .last_move_time = GetTime(),
        .move_interval = MOVE_INTERVAL,
        .left_held = false,
        .right_held = false,
        .rotation = false
        };


    // Initialize the pieces
    game->current_piece = arena_alloc_type(game->arena, Tetromino_t);
    if (game->current_piece == NULL) {
        fprintf(stderr, "Failed to allocate space for the current piece\n");
    }
    game->ghost_piece = arena_alloc_type(game->arena, Tetromino_t);
    if (game->ghost_piece == NULL) {
        fprintf(stderr, "Failed to allocate space for the ghost piece\n");
    }
    game->next_piece = arena_alloc_type(game->arena, Tetromino_t);
    if (game->next_piece == NULL) {
        fprintf(stderr, "Failed to allocate space for the next piece\n");
    }

    GameReset(game);
}

void GameReset(Game *game) {
    Tetromino_Generate(game->current_piece);
    Tetromino_Generate(game->next_piece);
    game->next_piece->pos.x = 10;
    game->next_piece->pos.y = 7;
    game->score = 0;
    game->level = 0;
    game->drop_interval = INITIAL_DROP_INTERVAL;
    game->drop_interval_speed_up = 1.0f;
    game->last_drop_time = GetTime();
    PlayfieldInit(game);
}

void GameLoop(Game *game) {
    // Handle Input
    //----------------------------------------------------------------------------------
    GameHandleInput(game);

    // Update
    //----------------------------------------------------------------------------------
    GameUpdate(game);

    // Draw
    //----------------------------------------------------------------------------------
    GameRender(game);
}

void GameHandleInput(Game *game) {
    if (IsKeyPressed(KEY_UP) && !game->input.rotation) {
        Tetromino_Rotate(game->current_piece, CW);
        game->input.rotation = true;
        // Check to see if rotated out of bounds and revert if necessary
        if (Tetromino_Bounds_Check(game->current_piece) || PlayfieldOverlapCheck(game, game->current_piece)) {
            Tetromino_Rotate(game->current_piece, CCW);
            game->input.rotation = false;
        }
    }

    // Check if down key is pressed and then speed up the drop rate
    if (IsKeyDown(KEY_DOWN)) {
        game->drop_interval_speed_up = game->drop_interval / 4;
    }

    // Reset the drop rate if the down key is released
    if (IsKeyReleased(KEY_DOWN)) {
        game->drop_interval_speed_up = 1.0f;
    }

    // Check if the space key is pressed and instant drop the current piece
    if (IsKeyPressed(KEY_SPACE)) {
        for (int i = 0; i < GRID_HEIGHT; i++) {
            game->score += TetrominoDrop(game->current_piece);
            if (Tetromino_Bounds_Check(game->current_piece) || PlayfieldOverlapCheck(game, game->current_piece)) {
                game->current_piece->pos.y--;
                // New piece time
                PlayfieldCopyCurrentToPlayfield(game);
                game->next_piece->pos = (Vector2i) { .x = 2, .y = 0 };
                memcpy(game->current_piece, game->next_piece, sizeof(Tetromino_t));
                Tetromino_Generate(game->next_piece);
                game->next_piece->pos.x = NEXT_PIECE_X + (NEXT_PIECE_WIDTH / 2);
                game->next_piece->pos.y = NEXT_PIECE_Y + (NEXT_PIECE_HEIGHT / 2);
                break;
            }
        }
    }

    // Check if the up arrow is released and clear the rotation flag
    if (IsKeyReleased(KEY_UP)) {
        game->input.rotation = false;
    }

    // Check if the right arrow is pressed to move the piece to the right
    if (IsKeyPressed(KEY_RIGHT)) {
        game->input.right_held = true;
    }

    // Check if the left arrow is pressed to move the piece to the left
    if (IsKeyPressed(KEY_LEFT)) {
        game->input.left_held = true;
    }

    // Check if the right arrow is released to clear the right held flag
    if (IsKeyReleased(KEY_RIGHT)) {
        game->input.right_held = false;
    }

    // Check if the left arrow is released to clear the left held flag
    if (IsKeyReleased(KEY_LEFT)) {
        game->input.left_held = false;
    }
}

void GameUpdate(Game *game) {
    const double now = GetTime();

    // Place the ghost piece by copying the current piece and dropping it to
    // the lowest point in the playfield
    memcpy(game->ghost_piece, game->current_piece, sizeof(Tetromino_t));
    for (int i = 0; i < GRID_HEIGHT; i++) {
        game->ghost_piece->pos.y++;
        if (Tetromino_Bounds_Check(game->ghost_piece) || PlayfieldOverlapCheck(game, game->ghost_piece)) {
            game->ghost_piece->pos.y--;
            break;
        }
    }

    // Check if it is time to move the piece to the left or right
    if ( now - game->input.last_move_time >= game->input.move_interval) {
        game->input.last_move_time = now;
        if (game->input.left_held) {
            game->current_piece->pos.x--;
            if (Tetromino_Bounds_Check(game->current_piece) || PlayfieldOverlapCheck(game, game->current_piece)) {
                game->current_piece->pos.x++;
            }
        }
        if (game->input.right_held) {
            game->current_piece->pos.x++;
            if (Tetromino_Bounds_Check(game->current_piece) || PlayfieldOverlapCheck(game, game->current_piece)) {
                game->current_piece->pos.x--;
            }
        }
    }

    if ( now - game->last_drop_time >= game->drop_interval * game->drop_interval_speed_up ) {
        game->score += TetrominoDrop(game->current_piece);
        if (Tetromino_Bounds_Check(game->current_piece) || PlayfieldOverlapCheck(game, game->current_piece)) {
            game->current_piece->pos.y--;
            // New piece time
            PlayfieldCopyCurrentToPlayfield(game);
            memcpy(game->current_piece, game->next_piece, sizeof(Tetromino_t));
            Tetromino_Generate(game->next_piece);
            if (PlayfieldOverlapCheck(game, game->current_piece)) {
                GameReset(game);
            }
        }
        game->last_drop_time = now;
    }

    game->score += PlayfieldClearLines(game);
}

void GameRender(const Game *game) {
    BeginDrawing();

    ClearBackground(game->background_color);
    UIRender(game);
    PlayfieldRender(game);

    EndDrawing();
}