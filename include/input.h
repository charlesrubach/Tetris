//
// Created by Charles on 8/6/2026.
//

#ifndef TETRIS_INPUT_H
#define TETRIS_INPUT_H
#include <stdbool.h>

typedef struct Input {
    double das;
    double arr;
    double last_move_time;
    double move_interval;
    bool left_held;
    bool right_held;
    bool rotation;
} Input;

#endif //TETRIS_INPUT_H