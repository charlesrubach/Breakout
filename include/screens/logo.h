#ifndef LOGO_H
#define LOGO_H

#include "raylib.h"
#include "game.h"

#if defined(__cplusplus)
extern "C" {
#endif

static const float LOGO_DISPLAY_TIME = 4.0f; // Display logo for 4 seconds

typedef struct Logo {
    int width;
    int height;
    Texture2D texture;
    double timeCounter;
    Vector2 position; // Position of the logo on the screen
} Logo;

void LogoInit(Game *game);
void LogoRender(Game *game);
void LogoUnload(Game *game);
void LogoUpdate(Game *game);
#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif // LOGO_H