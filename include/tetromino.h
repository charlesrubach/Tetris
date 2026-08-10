#ifndef TETRIS_TETROMINO_H
#define TETRIS_TETROMINO_H

#define TETROMINO_SIZE  4
#include "utilities.h"

typedef enum TetrominoShape {
    TETROMINO_I,
    TETROMINO_J,
    TETROMINO_L,
    TETROMINO_O,
    TETROMINO_S,
    TETROMINO_T,
    TETROMINO_Z,
    TOTAL_TETROMINOES
} TetrominoShape;

extern Color TetrominoColors[];

typedef enum TetrominoRotationState {
    DEGREE_0, DEGREE_90_CW, DEGREE_180, DEGREE_270_CCW, TOTAL_ROTATION_STATES
} TetrominoRotationState;

typedef enum TetrominoRotationDirection {
    CW, CCW
} TetrominoRotationDirection;

typedef enum TetrominoDirection {
    LEFT, RIGHT
} TetrominoDirection;


typedef struct Tetromino {
    TetrominoShape grid[TETROMINO_SIZE][TETROMINO_SIZE];
    TetrominoRotationState rotation_state;
    TetrominoShape shape;
    Color color;
    Vector2i pos;
} Tetromino_t;

Tetromino_t *Tetromino_Generate(Tetromino_t *tetromino);
void Tetromino_Rotate(Tetromino_t *tetromino, TetrominoRotationDirection direction);
void Tetromino_Move(Tetromino_t *tetromino, TetrominoDirection move_direction);
bool Tetromino_Bounds_Check(const Tetromino_t *tetromino);

#endif //TETRIS_TETROMINO_H
