#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"

#ifdef __cplusplus
extern "C" {
#endif

// Level definitions here
typedef struct Level {
    int levelNumber;
    int blockCount;
    int rows;
    int columns;
    Block **blocks; // Pointer to an array of Block pointers
} Level;

void LoadLevel(Level *level, int levelNumber);
void UpdateLevel(Level *level);
void RenderLevel(Level *level);

#ifdef __cplusplus
}
#endif

#endif // LEVEL_H
