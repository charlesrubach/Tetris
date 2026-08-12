#ifndef TETRIS_PLAYFIELD_H
#define TETRIS_PLAYFIELD_H

typedef struct Tetromino Tetromino_t;

#define GRID_WIDTH              10
#define GRID_HEIGHT             20
#define CELL_SIZE               39
#define CLEAR_LINES_POINTS      100
#define GRID_PADDING            10

typedef struct Game Game;

void PlayfieldInit(Game *game);
void PlayfieldRender(const Game *game);
bool PlayfieldOverlapCheck(const Game *game, const Tetromino_t *tetromino);
void PlayfieldCopyCurrentToPlayfield(Game *game);
int PlayfieldClearLines(Game *game);

#endif //TETRIS_PLAYFIELD_H