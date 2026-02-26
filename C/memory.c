// ...existing code...
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

int main(void)
{
    char folder[PATH_MAX];
    char filename[NAME_MAX];
    char fullpath[PATH_MAX];

    printf("Enter folder path: ");
    if (!fgets(folder, sizeof(folder), stdin)) return 1;
    folder[strcspn(folder, "\n")] = '\0';  // remove newline

    printf("Enter filename: ");
    if (!fgets(filename, sizeof(filename), stdin)) return 1;
    filename[strcspn(filename, "\n")] = '\0'; // remove newline

    // Build full path, handle trailing slash
    if (folder[0] == '\0') {
        snprintf(fullpath, sizeof(fullpath), "%s", filename);
    } else if (folder[strlen(folder) - 1] == '/') {
        snprintf(fullpath, sizeof(fullpath), "%s%s", folder, filename);
    } else {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", folder, filename);
    }

    if (access(fullpath, F_OK) == 0) {
        printf("file located in the folder\n");
    } else {
        printf("file not found in the folder\n");
    }

    return 0;
}
// ...existing code...