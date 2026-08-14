#ifndef BLOCK_H
#define BLOCK_H


#ifdef __cplusplus
extern "C" {
#endif

#include "raylib.h"

typedef struct Block {
    Rectangle rect;
    Color color;
    int health; // Number of hits the block can take before being destroyed
    int points; // Points awarded for destroying the block
    bool isActive; // Indicates if the block is still active (not destroyed)
} Block;

#ifdef __cplusplus
}
#endif

#endif // BLOCK_H
