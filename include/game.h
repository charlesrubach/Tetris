#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "raylib.h"
#include "playfield.h"
#include "tetromino.h"
#include "arena.h"
#include "input.h"
#include "ui.h"

#define EMPTY_TETROMINO                 TOTAL_TETROMINOES
#define INITIAL_DROP_INTERVAL           (0.5f)
#define DROP_INTERVAL_INITIAL_SPEEDUP   (1.0f)
#define MOVE_INTERVAL                   (INITIAL_DROP_INTERVAL / GRID_WIDTH)

// Custom colors
#define CUSTOM_COLOR_GAME_BACKGROUND    (Color){.r = 77, .g = 2, .b = 176, .a = 255}
#define CUSTOM_COLOR_GAME_PLAYFIELD     (Color){.r = 40, .g = 1, .b = 92, .a = 255}
#define CUSTOM_COLOR_GAME_GRID_LINE     (Color){.r = 24, .g = 1, .b = 54, .a = 255}

typedef struct Game {
    Arena *arena;
    Color background_color;
    Input input;
    int score;
    int level;
    Tetromino_t *current_piece;
    Tetromino_t *ghost_piece;
    Tetromino_t *next_piece;
    TetrominoShape playfield[GRID_HEIGHT][GRID_WIDTH];
    double drop_interval;
    double drop_interval_speed_up;
    double last_drop_time;
} Game;

void GameInit(Game *game, Arena *arena);
void GameReset(Game *game);
void GameLoop(Game *game);
void GameHandleInput(Game *game);
void GameUpdate(Game *game);
void GameRender(const Game *game);
void GameSpawnPiece(Game *game);
void GameCheckGameOver(Game *game);
void GameClearLine(Game *game);

#endif //TETRIS_GAME_H