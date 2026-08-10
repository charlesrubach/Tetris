#ifndef TETRIS_PLAYFIELD_H
#define TETRIS_PLAYFIELD_H

typedef struct Tetromino Tetromino_t;

#define GRID_WIDTH  10
#define GRID_HEIGHT 20
#define CELL_SIZE   39

typedef struct Game Game;

void Playfield_Init(Game *game);
void Playfield_Render(const Game *game);
bool Playfield_Overlap_Check(const Game *game, const Tetromino_t *tetromino);
void Playfield_Copy_Current_To_Playfield(Game *game);

#endif //TETRIS_PLAYFIELD_H