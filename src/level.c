#include "level.h"
#include "brick.h"
#include "cJSON.h"
#include "config.h"
#include "game.h"
#include "raylib.h"

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <errno.h>
#endif

const char *json_file = "resources/breakout_levels.json";

// Private functions
static int GetLevel(Level *level);
static char *ReadLevelFile(const char *filename);
static Color HexColorStringToColor(char *hex_str);

void LevelLoad(Game *game) {
  // Load breakout_levels.json
  Level *level = game->level;

  level->buffer = ReadLevelFile(json_file);

  if (level->buffer == NULL) {
    fprintf(stderr, "Unable to read the JSON file\n");
    return;
  }

  level->brick_width = SCREEN_WIDTH / BRICK_COLUMNS;
  level->brick_height = SCREEN_HEIGHT / 4 / BRICK_ROWS;

  GetLevel(level);

  free(level->buffer);
}

void LevelUpdate(Game *game) { Level *level = game->level; }

void LevelRender(Game *game) {
  Level *level = game->level;

  for (int i = 0; i < level->brickCount; i++) {
    if (level->bricks[i].isActive) {
      DrawRectangleRec(level->bricks[i].rect, level->bricks[i].color);
      DrawRectangleLines(level->bricks[i].rect.x, level->bricks[i].rect.y, level->bricks[i].rect.width,
                         level->bricks[i].rect.height, BLACK);
    }
  }
}

// Read in the file and return a pointer to the buffer
static char *ReadLevelFile(const char *filename) {
  FILE *file_ptr = NULL;
  char *buffer;
  long numbytes;

  // Open the file and make sure it exists
#ifdef _WIN32
  errno_t err = fopen_s(&file_ptr, filename, "r");
#else
  file_ptr = fopen(filename, "r");
  int err = (file_ptr == NULL) ? errno : 0;
#endif

  if (err != 0) {
    // If an error occurred, file_ptr is guaranteed to be NULL
    char err_msg[80];

#ifdef _WIN32
    strerror_s(err_msg, sizeof(err_msg), err);
#else
    strerror_r(err, err_msg, sizeof(err_msg));
#endif

    fprintf(stderr, "Error opening file: %s (Error code: %d)\n", err_msg, err);
    return NULL;
  }

  // Get the number of bytes
  fseek(file_ptr, 0L, SEEK_END);
  numbytes = ftell(file_ptr);

  // Reset the file position indicator to the beginning of the file
  fseek(file_ptr, 0L, SEEK_SET);

  // Grab sufficient memory for the buffer to hld the text
  buffer = (char *)calloc(numbytes, sizeof(char));

  if (buffer == NULL) {
    return NULL;
  }

  // Copy all the text into the buffer
  fread(buffer, sizeof(char), numbytes, file_ptr);

  // Confirm we have read the file by outputing it to the console
  // printf("The file contains this text\n\n%s", buffer);

  // Always close the file pointer when finished
  fclose(file_ptr);

  return buffer;
}

static int GetLevel(Level *level) {
  const cJSON *cjson_level = NULL;
  const cJSON *cjson_levels = NULL;
  const cJSON *cjson_bricks = NULL;
  const cJSON *cjson_brick = NULL;
  int levelCount = 0;
  int brickCount = 0;
  int index = 0;
  int status = 0;

  cJSON *root = cJSON_Parse(level->buffer);
  if (root == NULL) {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
      fprintf(stderr, "Error before: %s\n", error_ptr);
    }
    return status;
  }

  // Get "levels" array
  cjson_levels = cJSON_GetObjectItemCaseSensitive(root, "levels");
  levelCount = cJSON_GetArraySize(cjson_levels);

  // Find the current level
  bool levelFound = false;
  cJSON_ArrayForEach(cjson_levels, cjson_levels) {
    cjson_level = cJSON_GetObjectItemCaseSensitive(cjson_levels, "level");

    if (cJSON_IsString(cjson_level) && (cjson_level->valuestring != NULL)) {
      if (atoi(cjson_level->valuestring) == level->levelNumber) {
        printf("Level found!\n");
        levelFound = true;
        break;
      }
    }
    index++;
  }

  if (!levelFound) {
    cJSON_Delete(root);
    return 0;
  }

  cjson_bricks = cJSON_GetArrayItem(cjson_levels, 1);
  // if (bricks == NULL || !cJSON_IsArray(bricks))
  if (cjson_bricks == NULL) {
    cJSON_Delete(root);
    return status;
  }

  level->brickCount = cJSON_GetArraySize(cjson_bricks);

  level->bricks = (Brick *)malloc(level->brickCount * sizeof(Brick));

  // Get all bricks
  Brick *current_brick = level->bricks;
  cJSON_ArrayForEach(cjson_bricks, cjson_bricks) {
    cJSON *row;
    cJSON *col;
    cJSON *color;

    row = cJSON_GetObjectItemCaseSensitive(cjson_bricks, "row");
    col = cJSON_GetObjectItemCaseSensitive(cjson_bricks, "col");
    color = cJSON_GetObjectItemCaseSensitive(cjson_bricks, "color");

    printf("row %d, col %d, color %s\n", row->valueint, col->valueint,
           color->valuestring);
    // current_brick = (Brick*)malloc(sizeof(Brick));
    *current_brick = (Brick){
        // .pos = (Vector2){.x = (float)col->valueint, .y =
        // (float)row->valueint},
        .rect = (Rectangle){.x = (float)(col->valueint * level->brick_width),
                            .y = (float)(row->valueint * level->brick_height),
                            (float)level->brick_width,
                            (float)level->brick_height},
        .color = HexColorStringToColor(color->valuestring),
        .health = 1,
        .points = 100,
        .isActive = true,
    };

    current_brick++;
  }

  cJSON_Delete(root);

  return status;
}

void ClearLevel(Game *game) {
  Level *level = game->level;

  if (level->bricks) {
    free(level->bricks);
  }
  level->brickCount = 0;
  level->columns = 0;
  level->rows = 0;
}

static Color HexColorStringToColor(char *hex_str) {
  Color color = (Color){0, 0, 0, 0};
  unsigned int r, g, b;

  if (hex_str && sscanf_s(hex_str, "#%02x%02x%02x", &r, &g, &b) == 3) {
    color = (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, 255};
  }

  return color;
}