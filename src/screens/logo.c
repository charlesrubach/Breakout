#include "screens/logo.h"
#include <stdio.h>
#include <stdlib.h>

const char *LOGO_PATH = "resources/logo.png"; // Path to the logo image

void LogoInit(Game *game) {
    // Load logo texture
    game->logo = (Logo *)malloc(sizeof(Logo));
    if (game->logo == NULL) {
        fprintf(stderr, "Failed to allocate memory for Logo struct\n");
        return; // Handle memory allocation failure
    }
    game->logo->texture = LoadTexture(LOGO_PATH);
    game->logo->width = game->logo->texture.width;
    game->logo->height = game->logo->texture.height;
    game->logo->timeCounter = GetTime(); // Initialize time counter
    game->logo->position.x = (float)(game->screenWidth - game->logo->width) / 2;
    game->logo->position.y = (float)game->logo->height * -1; // Start above the screen for downward movement
}

void LogoRender(Game *game) {
    DrawTexture(game->logo->texture, game->logo->position.x, game->logo->position.y, WHITE);
}

void LogoUnload(Game *game) {
    UnloadTexture(game->logo->texture);
    free(game->logo);
}

void LogoUpdate(Game *game) {
    double currentTime = GetTime();
    if (currentTime - game->logo->timeCounter >= LOGO_DISPLAY_TIME) { // Show logo for specified time
        game->state = SHOW_TITLE; // Transition to title screen
    } else {
        // Move the logo downwards
        if(game->logo->position.y  < (float)(game->screenHeight - game->logo->height) / 2 ) {
            game->logo->position.y += 2.0f; // Adjust speed as needed
        }
    }
}