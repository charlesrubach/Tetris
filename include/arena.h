//
// Created by Charles on 8/6/2026.
//

#ifndef TETRIS_ARENA_H
#define TETRIS_ARENA_H

#include <stdint.h>
#include <stdlib.h>

typedef struct Arena {
   uint8_t *buffer;
   size_t capacity;
   size_t offset;
} Arena;

#define arena_alloc_type(arena_ptr, type) ((type *)arena_alloc((arena_ptr), sizeof(type), _Alignof(type)))

Arena arena_init(size_t capacity);
void *arena_alloc(Arena *arena, size_t size, size_t alignment);
void arena_reset(Arena *arena);
void arena_free(Arena *arena);


#endif //TETRIS_ARENA_H