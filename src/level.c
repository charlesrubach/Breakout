#include "level.h"
#include "cJSON.h"
#include "config.h"
#include "game.h"
#include "brick.h"
#include "raylib.h"
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <errno.h>
#endif

const char *json_file = "resources/breakout_levels.json";

static char *ReadLevelFile(const char *filename);
static int GetLevel(Game *game, const char *const breakout_levels);
static Color HexColorStringToColor(char *hex_str);

void LevelLoad(Game *game)
{
  // Load breakout_levels.json

  char *buffer = ReadLevelFile(json_file);

  if (buffer == NULL)
  {
    fprintf(stderr, "Unable to read the JSON file\n");
    return;
  }

  game->level->brick_width = SCREEN_WIDTH / BRICK_COLUMNS;
  game->level->brick_height = SCREEN_HEIGHT / 2 / BRICK_ROWS;

  GetLevel(game, buffer);

  free(buffer);
}

void LevelUpdate(Level *level) {

}

void LevelRender(Level *level) {
  for(int i = 0; i < level->brickCount; i++) {
    if(level->bricks[i].isActive) {
      Rectangle brick_rect = (Rectangle){ level->bricks[i].pos.x * level->brick_width,
                                          level->bricks[i].pos.y * level->brick_height, 100, 50};
      DrawRectangleRec(brick_rect, level->bricks[i].color);
      DrawRectangleLines(brick_rect.x, brick_rect.y, brick_rect.width, brick_rect.height, BLACK);
    }
  }
}

// Read in the file and return a pointer to the buffer
static char *ReadLevelFile(const char *filename)
{
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

  if (err != 0)
  {
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

  if (buffer == NULL)
  {
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

static int GetLevel(Game *game, const char *const breakout_levels)
{
  const cJSON *level = NULL;
  const cJSON *levels = NULL;
  const cJSON *bricks = NULL;
  const cJSON *brick = NULL;
  int levelCount = 0;
  int brickCount = 0;
  int index = 0;
  int status = 0;

  cJSON *root = cJSON_Parse(breakout_levels);
  if (root == NULL)
  {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL)
    {
      fprintf(stderr, "Error before: %s\n", error_ptr);
    }
    return status;
  }

  // Get "levels" array
  levels = cJSON_GetObjectItemCaseSensitive(root, "levels");
  levelCount = cJSON_GetArraySize(levels);

  // Find the current level
  bool levelFound = false;
  cJSON_ArrayForEach(levels, levels)
  {
    level = cJSON_GetObjectItemCaseSensitive(levels, "level");

    if (cJSON_IsString(level) && (level->valuestring != NULL))
    {
      if (atoi(level->valuestring) == game->level->levelNumber)
      {
        printf("Level found!\n");
        levelFound = true;
        break;
      }
    }
    index++;
  }

  if (!levelFound)
  {
    cJSON_Delete(root);
    return 0;
  }

  bricks = cJSON_GetArrayItem(levels, 1);
  // if (bricks == NULL || !cJSON_IsArray(bricks))
  if (bricks == NULL)
  {
    cJSON_Delete(root);
    return status;
  }

  game->level->brickCount = cJSON_GetArraySize(bricks);

  game->level->bricks = (Brick*)malloc(game->level->brickCount * sizeof(Brick));

  // Get all bricks
  Brick *current_brick = game->level->bricks;
  cJSON_ArrayForEach(bricks, bricks)
  {
    cJSON *row;
    cJSON *col;
    cJSON *color;

    row = cJSON_GetObjectItemCaseSensitive(bricks, "row");
    col = cJSON_GetObjectItemCaseSensitive(bricks, "col");
    color = cJSON_GetObjectItemCaseSensitive(bricks, "color");

    printf("row %d, col %d, color %s\n", row->valueint, col->valueint, color->valuestring);
    // current_brick = (Brick*)malloc(sizeof(Brick));
    *current_brick = (Brick) {
      .pos = (Vector2){ .x = (float)col->valueint, .y = (float)row->valueint },
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

void ClearLevel(Level *level) {
  if(level->bricks) {
    free(level->bricks);
  }
  level->brickCount = 0;
  level->columns = 0;
  level->rows = 0;
}

static Color HexColorStringToColor(char *hex_str) {
  Color color = (Color){ 0, 0, 0 , 0 };
  unsigned int r, g, b;

    if (hex_str && sscanf_s(hex_str, "#%02x%02x%02x", &r, &g, &b) == 3) {
        color = (Color){ (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };
    }

  return color;
}