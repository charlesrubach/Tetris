//
// Created by Charles on 8/6/2026.
//

#include "game.h"

void PlayField_Init(Game *game) {
    // Initialization logic for the playfield
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            game->playfield[i][j] = EMPTY_TETROMINO;
        }
    }
}

void PlayField_Render(const Game *game) {
    // Rendering logic for the playfield
    for (int i = 0; i < GRID_HEIGHT; i++ ) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            const int y = i * CELL_SIZE + 10;
            const int x = j * CELL_SIZE + 10;
            DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, TetrominoColors[game->playfield[i][j]]);
        }
    }
    // Draw current piece
    for (int i = 0; i < TETROMINO_SIZE; i++) {
        for (int j = 0; j < TETROMINO_SIZE; j++) {
            const int y = ((i + game->current_piece->pos.y) * CELL_SIZE) + 10;
            const int x = ((j + game->current_piece->pos.x) * CELL_SIZE) + 10;

            if (game->current_piece->grid[i][j] != EMPTY_TETROMINO) {
                DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, TetrominoColors[game->current_piece->grid[i][j]]);
            }
        }
    }
    for (int i = 0; i < GRID_HEIGHT; i++ ) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            const int y = i * CELL_SIZE + 10;
            const int x = j * CELL_SIZE + 10;
            DrawRectangleLines(x, y, CELL_SIZE, CELL_SIZE, CUSTOM_COLOR_GAME_GRID_LINE);
        }
    }
}