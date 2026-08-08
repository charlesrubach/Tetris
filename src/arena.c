//
// Created by Charles on 8/6/2026.
//

#include "../include/arena.h"

// Initialize the arena by pre-allocating a large block
Arena arena_init(const size_t capacity) {
    Arena arena = {0};
    arena.buffer = (uint8_t *)malloc(capacity);
    if (arena.buffer) {
        arena.capacity = capacity;
        arena.offset = 0;
    }
    return arena;
}

// Allocate memory form the arena with proper alignment
void *arena_alloc(Arena *arena, const size_t size, const size_t alignment) {
    // Determine the alignment adjustment
    const uintptr_t current_ptr = (uintptr_t)arena->buffer + arena->offset;
    const uintptr_t aligned_ptr = (current_ptr + (alignment - 1)) & ~(alignment - 1);
    const size_t alignment_padding = aligned_ptr - current_ptr;

    // Check if the arena has enough room left
    if (arena->offset + alignment_padding + size > arena->capacity) {
        fprintf(stderr, "Arena out of memory!\n");
        return NULL;
    }

    // Advance the offset and return the aligned pointer
    arena->offset += alignment_padding + size;
    return (void *)aligned_ptr;
}

// Reset the offset to zero to reuse all the memory instantly
void arena_reset(Arena *arena) {
    arena->offset = 0;
}

// Free the backing memory block entirely from the system
void arena_free(Arena *arena) {
    if (arena != NULL) {
        free(arena->buffer);
        arena->buffer = NULL;
        arena->capacity = 0;
        arena->offset = 0;
    }
}