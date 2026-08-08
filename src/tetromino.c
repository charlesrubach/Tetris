//
// Created by Charles on 8/6/2026.
//

#include <string.h>
#include "game.h"

const int tetromino_shape[TOTAL_TETROMINOES][TETROMINO_SIZE][TETROMINO_SIZE] = {

    // Tetromino Shape I
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // Tetromino Shape J
    {
            {1, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    },
    // Tetromino Shape L
    {
            {0, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    },
    // Tetromino Shape O
    {
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    },
    // Tetromino Shape S
    {
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    },
    // Tetromino Shape T
    {
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    },
    // Tetromino Shape Z
    {
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
    }
};

Color TetrominoColors[TOTAL_TETROMINOES + 1] = {
    SKYBLUE,    // I
    DARKBLUE,   // J
    ORANGE,     // L
    YELLOW,     // O
    GREEN,      // S
    PURPLE,     // T
    RED,        // Z
    CUSTOM_COLOR_GAME_PLAYFIELD
};

Tetromino_t *Tetromino_Create(const Game *game, const TetrominoShape shape) {
    Tetromino_t *tetromino = arena_alloc_type(game->arena, Tetromino_t);
    if (tetromino == NULL) {
        fprintf(stderr, "Unable to allocate space for tetromino.\n");
        return NULL;
    }

    for (int i = 0; i < TETROMINO_SIZE; i++) {
        for (int j = 0; j < TETROMINO_SIZE; j++) {
            if (tetromino_shape[shape][i][j] == 1) {
                tetromino->grid[i][j] = shape;
            } else {
                tetromino->grid[i][j] = EMPTY_TETROMINO;
            }
        }
    }

    tetromino->rotation_state = DEGREE_0;
    tetromino->shape = shape;
    tetromino->color = TetrominoColors[shape];
    Tetromino_Rotate(tetromino, CW);
    tetromino->pos = (Vector2i) { (GRID_WIDTH - TETROMINO_SIZE - 1) / 2, 0 };

    return tetromino;
}

void Tetromino_Rotate(Tetromino_t *tetromino, const TetrominoDirection direction) {
    int rotated_grid[TETROMINO_SIZE][TETROMINO_SIZE] = { 0 };
    switch (direction){
        case CW:
            for (int i = 0; i < TETROMINO_SIZE; i++) {
                for (int j = 0; j < TETROMINO_SIZE; j++) {
                    rotated_grid[j][TETROMINO_SIZE - i - 1] = tetromino->grid[i][j];
                }
            }
            tetromino->rotation_state = (tetromino->rotation_state + 1) % TOTAL_ROTATION_STATES;
            break;
        case CCW:
            for (int i = 0; i < TETROMINO_SIZE; i++) {
                for (int j = 0; j < TETROMINO_SIZE; j++) {
                    rotated_grid[TETROMINO_SIZE - j - 1][i] = tetromino->grid[i][j];
                }
            }
            tetromino->rotation_state = (tetromino->rotation_state - 1 + TOTAL_ROTATION_STATES) % TOTAL_ROTATION_STATES;
            break;
        default:
            // This should never happen
            break;
    }

    memcpy(tetromino->grid, rotated_grid, sizeof(tetromino->grid));
}

void Tetromino_Move(Tetromino_t *tetromino) {

}