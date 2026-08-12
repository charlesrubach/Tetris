#ifndef TETRIS_UI_H
#define TETRIS_UI_H

#include "config.h"

#define SCORE_POS_X         ((GRID_WIDTH * CELL_SIZE) + GRID_PADDING * 2)
#define SCORE_POS_Y         GRID_PADDING
#define SCORE_WIDTH         (SCREEN_WIDTH - (GRID_WIDTH * CELL_SIZE) - GRID_PADDING * 3)
#define SCORE_HEIGHT        200

#define NEXT_PIECE_X        SCORE_POS_X
#define NEXT_PIECE_Y        (SCORE_HEIGHT + (GRID_PADDING * 2))
#define NEXT_PIECE_WIDTH    SCORE_WIDTH
#define NEXT_PIECE_HEIGHT   400

#define UI_RECT_ROUNDNESS   (0.2f)
typedef struct Game Game;

void UIRender(const Game *game);

#endif //TETRIS_UI_H