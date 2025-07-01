#include "path.h"

char* find_in_path(const char* filename) {
    char* path = getenv("PATH"); // Get PATH environment variable
    if (!path) return NULL;

    char* token = strtok(path, ":");
    while (token) {
        char file_path[PATH_MAX];
        snprintf(file_path, sizeof(file_path), "%s/%s", token, filename);
		// Check if file exists
        if (access(file_path, F_OK) == 0) {
            free(path);
            return strdup(file_path);
        }
        token = strtok(NULL, ":");
    }
    free(path);
    return NULL;
}
