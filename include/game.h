#ifndef GAME_H
#define GAME_H

#include "level.h"
#if defined(__cplusplus)
extern "C" {
#endif

typedef enum GameState { SHOW_LOGO, SHOW_TITLE, SHOW_GAMEPLAY, SHOW_ENDING } GameState;

typedef struct Title Title;
typedef struct Paddle Paddle;
typedef struct Logo Logo;
typedef struct Ball Ball;
typedef struct Level Level;

typedef struct Game {
    GameState state;
    int screenWidth;
    int screenHeight;
    int targetFPS;
    Logo *logo;
    Title *title;
    Paddle *paddle; // Pointer to the Paddle struct
    Ball *ball; // Pointer to the Ball array 
    Level *level;
} Game;

typedef struct Game Game;

void GameInit(Game *game);
bool GameLoop(Game *game);
void GameUpdate(Game *game);
void GameRender(Game *game);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif // GAME_H__
