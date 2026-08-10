//
// Created by Charles on 8/6/2026.
//

#include <string.h>
#include <stdio.h>
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
    SKYBLUE, // I
    DARKBLUE, // J
    ORANGE, // L
    YELLOW, // O
    GREEN, // S
    PURPLE, // T
    RED, // Z
    CUSTOM_COLOR_GAME_PLAYFIELD
};

Tetromino_t *Tetromino_Generate(Tetromino_t *tetromino) {
    if (tetromino == NULL) {
        fprintf(stderr, "Tetromino not allocated.\n");
        return NULL;
    }

    const TetrominoShape shape = (TetrominoShape)GetRandomValue(0, TOTAL_TETROMINOES - 1);

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
    tetromino->pos = (Vector2i){0, 0};

    return tetromino;
}

void Tetromino_Rotate(Tetromino_t *tetromino, const TetrominoRotationDirection direction) {
    int rotated_grid[TETROMINO_SIZE][TETROMINO_SIZE] = {0};
    switch (direction) {
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

void Tetromino_Move(Tetromino_t *tetromino, const TetrominoDirection move_direction) {
    bool out_of_bounds = false;

    for (int i = 0; i < TETROMINO_SIZE; i++) {
        for (int j = 0; j < TETROMINO_SIZE; j++) {
            if (tetromino->grid[i][j] == tetromino->shape) {
                if (move_direction == RIGHT) {
                    if (tetromino->pos.x + j + 1 >= GRID_WIDTH) {
                        out_of_bounds = true;
                        break;
                    }
                }
                if (move_direction == LEFT) {
                    if (tetromino->pos.x - 1 + j < 0) {
                        out_of_bounds = true;
                        break;
                    }
                }
            }
        }
    }

    if (!out_of_bounds) {
        if (move_direction == RIGHT) {
            tetromino->pos.x++;
        } else {
            tetromino->pos.x--;
        }
    }
}

bool Tetromino_Bounds_Check(const Tetromino_t *tetromino) {
    bool out_of_bounds = false;

    for (int i = 0; i < TETROMINO_SIZE; i++) {
        for (int j = 0; j < TETROMINO_SIZE; j++) {
            if (tetromino->grid[i][j] == tetromino->shape) {
                // Translate grid position to playfield position
                const Vector2i square_pos = (Vector2i) { .x = j + tetromino->pos.x, .y = i + tetromino->pos.y};
                if (square_pos.x >= GRID_WIDTH || square_pos.x < 0 || square_pos.y >= GRID_HEIGHT || square_pos.y < 0) {
                    out_of_bounds = true;
                    break;
                }
            }
        }
    }

    return out_of_bounds;
}