#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ARENA_SIZE 1024

typedef struct {
    uint8_t memory[ARENA_SIZE];
    size_t offset;
} Arena;

// Initialize the arena
void arena_init(Arena* a) {
    a->offset = 0;
}

// Implement this function
void* arena_alloc(Arena* a, size_t size) {
    // Check if there is enough space left
    if (a->offset + size > ARENA_SIZE) {
        return NULL;
    }

    // Calculate pointer to the current free memory
    void* ptr = &a->memory[a->offset];

    // Increment offset
    a->offset += size;

    // Return pointer
    return ptr;
}

int main() {
    Arena my_arena;
    arena_init(&my_arena);

    int* num = (int*)arena_alloc(&my_arena, sizeof(int));
    if (num) {
        *num = 42;
        printf("Allocated number: %d\n", *num);
    } else {
        printf("Allocation failed!\n");
    }

    // Try allocating more than the remaining space
    char* big_string = (char*)arena_alloc(&my_arena, 2048);
    if (!big_string) {
        printf("Successfully caught out-of-memory error!\n");
    }

    return 0;
}
