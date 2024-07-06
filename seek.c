
#include "seek.h"
int is_directory(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) == 0) {
        return S_ISDIR(path_stat.st_mode);
    }
    return 0;
}

void seek(const char *target, const char *target_directory, int search_files, int search_directories, int execute_mode) {
    DIR *dir = opendir(target_directory);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct full path
        char full_path[MAX_PATH_LENGTH];
        snprintf(full_path, sizeof(full_path), "%s/%s", target_directory, entry->d_name);

        if ((search_files && !is_directory(full_path)) ||
            (search_directories && is_directory(full_path))) {
            if (strcmp(entry->d_name, target) == 0) {
                printf("./%s\n", entry->d_name);
                if (execute_mode) {
                    if (is_directory(full_path)) {
                        chdir(full_path);
                        printf("This is a new folder!\n");
                    } else {
                        FILE *file = fopen(full_path, "r");
                        if (file) {
                            char line[MAX_COMMAND_LENGTH];
                            while (fgets(line, sizeof(line), file)) {
                                printf("%s", line);
                            }
                            fclose(file);
                        } else {
                            printf("Missing permissions for task!\n");
                        }
                    }
                }
            }
        }

        if (is_directory(full_path)) {
            seek(target, full_path, search_files, search_directories, execute_mode);
        }
    }

    closedir(dir);
}