//
// Created by Charles on 8/6/2026.
//

#ifndef TETRIS_PLAYFIELD_H
#define TETRIS_PLAYFIELD_H

#include "game.h"

#define GRID_WIDTH  10
#define GRID_HEIGHT 20
#define CELL_SIZE   39

typedef struct Game Game;

void PlayField_Init(Game *game);
// bool PlayField_Bounds_Check(Tetromino_t *tetromino);
void PlayField_Render(const Game *game);

#endif //TETRIS_PLAYFIELD_H