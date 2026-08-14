#ifndef TITLE_H
#define TITLE_H 

#include "game.h"
#include "raylib.h"

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum TitleState { TITLE_START, TITLE_HIGHSCORES, TITLE_OPTIONS, TITLE_EXIT, TITLE_TOTAL_STATES} TitleState;

typedef struct TextPosition {
    Vector2 textSize;
    Vector2 position;
} TextPosition;

typedef struct Title {
    TitleState state; // Current state of the title screen
    Vector2 v1, v2, v3; // Vertices for the triangle cursor
    TextPosition breakout,start, highScores, options, exit; // Positions for menu items
} Title;

void TitleInit(Game *game);
void TitleRender(Game *game);      
void TitleUnload(Game *game);
void TitleUpdate(Game *game);


#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif // TITLE_H