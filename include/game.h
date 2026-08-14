#ifndef GAME_H
#define GAME_H

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum GameState { SHOW_LOGO, SHOW_TITLE, SHOW_GAMEPLAY, SHOW_ENDING } GameState;

typedef struct Logo Logo;
typedef struct Title Title;

typedef struct Game {
    GameState state;
    int screenWidth;
    int screenHeight;
    int targetFPS;
    Logo *logo;
    Title *title;
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
