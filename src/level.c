#define _POSIX_C_SOURCE 200112L
#include "level.h"
// #include "cJSON.h"
#include <stdio.h>
#include <string.h>

#ifdef __linux__
#include <errno.h>
#endif

const char *filename = "resources/breakout_levels.json";

static int GetLevel(const char * const breakout_levels);

void LoadLevel(Level *level, int levelNumber)
{
    // Load breakout_levels.json
    FILE *file_ptr = NULL;

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
        return;
    }

    // Read and print file contents
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file_ptr) != NULL)
    {
        printf("%s", buffer);
    }

    // Always close the file pointer when finished
    fclose(file_ptr);

    GetLevel(buffer);
}

static int GetLevel(const char * const breakout_levels) {

}