//
// Created by Charles on 8/6/2026.
//

#include "game.h"

void Playfield_Init(Game *game) {
    // Initialization logic for the playfield
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            game->playfield[i][j] = EMPTY_TETROMINO;
        }
    }
}

void Playfield_Render(const Game *game) {
    // Rendering logic for the playfield
    for (int i = 0; i < GRID_HEIGHT; i++ ) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            const int y = i * CELL_SIZE + 10;
            const int x = j * CELL_SIZE + 10;
            DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, TetrominoColors[game->playfield[i][j]]);
        }
    }

    // Draw grid lines
    for (int i = 0; i < GRID_HEIGHT; i++ ) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            const int y = i * CELL_SIZE + 10;
            const int x = j * CELL_SIZE + 10;
            DrawRectangleLines(x, y, CELL_SIZE, CELL_SIZE, CUSTOM_COLOR_GAME_GRID_LINE);
        }
    }

    //Draw Ghost Piece
    for (int i = 0; i < TETROMINO_SIZE; i++) {
        for (int j = 0; j < TETROMINO_SIZE; j++) {
            const int y = ((i + game->ghost_piece->pos.y) * CELL_SIZE) + 10;
            const int x = ((j + game->ghost_piece->pos.x) * CELL_SIZE) + 10;

            if (game->current_piece->grid[i][j] != EMPTY_TETROMINO) {
                DrawRectangleLines(x, y, CELL_SIZE, CELL_SIZE,TetrominoColors[game->current_piece->grid[i][j]]);
            }
        }
    }

    // Draw current piece
    for (int i = 0; i < TETROMINO_SIZE; i++) {
        for (int j = 0; j < TETROMINO_SIZE; j++) {
            const int y = ((i + game->current_piece->pos.y) * CELL_SIZE) + 10;
            const int x = ((j + game->current_piece->pos.x) * CELL_SIZE) + 10;

            if (game->current_piece->grid[i][j] != EMPTY_TETROMINO) {
                DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, TetrominoColors[game->current_piece->grid[i][j]]);
                DrawRectangleLines(x, y, CELL_SIZE, CELL_SIZE, CUSTOM_COLOR_GAME_GRID_LINE);
            }
        }
    }
}

bool Playfield_Overlap_Check(const Game *game, const Tetromino_t *tetromino) {
   bool overlap = false;
    for (int i = 0; i < TETROMINO_SIZE; i++) {
        for (int j = 0; j < TETROMINO_SIZE; j++) {
            if (tetromino->grid[i][j] == tetromino->shape) {
                const Vector2i adjusted_pos = (Vector2i) {
                    .x = tetromino->pos.x + j,
                    .y = tetromino->pos.y + i
                };
                if (game->playfield[adjusted_pos.y][adjusted_pos.x] != EMPTY_TETROMINO) {
                    overlap = true;
                    break;
                }
            }
        }
    }
    return overlap;
}

void Playfield_Copy_Current_To_Playfield(Game *game) {
    for (int i = 0; i < TETROMINO_SIZE; i++) {
        for (int j = 0; j < TETROMINO_SIZE; j++) {
            if (game->current_piece->grid[i][j] == game->current_piece->shape) {
                game->playfield[game->current_piece->pos.y + i][game->current_piece->pos.x + j] = game->current_piece->shape;
            }
        }
    }
}