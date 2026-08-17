#include "raylib.h"
#include "game.h"
#include "screens/logo.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");
    SetTargetFPS(TARGET_FPS);               // Set our game to run at 60 frames-per-second

    Game *game = (Game *)malloc(sizeof(Game));
    if (game == NULL) {
        fprintf(stderr, "Failed to allocate memory for Game struct\n");
        return -1; // Handle memory allocation failure
    }
    GameInit(game);

    //--------------------------------------------------------------------------------------

    // Main game loop
    bool running = true;
    while (!WindowShouldClose() && running)    // Detect window close button or ESC key
    {
        running = GameLoop(game);
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    LogoUnload(game); // Unload logo resources
    free(game->paddle);
    free(game); // Free the allocated memory for Game struct
    CloseWindow();        // Close window and OpenGL context

    //--------------------------------------------------------------------------------------
    return 0;
}
