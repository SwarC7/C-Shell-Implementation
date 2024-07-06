
#include "printdirectorycontent.h"


int compare_entries(const void *a, const void *b) {
   const char *name_a = (*(struct dirent **)a)->d_name;
    const char *name_b = (*(struct dirent **)b)->d_name;

    // Perform a case-insensitive comparison
    return strcasecmp(name_a, name_b);
}


void print_directory_contents(const char *path, int show_hidden, int show_details) {
    
    struct dirent *entry;
    struct dirent *entries[MAX_INPUT_LENGTH]; // Store entries for sorting
    int num_entries = 0;

    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("peek");
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        if (!show_hidden && entry->d_name[0] == '.') {
            continue;
        }

        entries[num_entries++] = entry;
    }

    // Sort entries in lexicographic order
    qsort(entries, num_entries, sizeof(struct dirent *), compare_entries);



long long total_blocks = 0; // Total block count

    struct stat fs_stat;
    if (stat(path, &fs_stat) == -1) {
        perror("peek");
        return;
    }
    long block_size = fs_stat.st_blksize; // Get block size
    for (int i = 0; i < num_entries; i++) {
        
          char entry_path[MAX_PATH_LENGTH];
        snprintf(entry_path, sizeof(entry_path), "%s/%s", path, entries[i]->d_name);

        struct stat file_stat;
        if (stat(entry_path, &file_stat) == -1) {
            perror("peek");
            continue;
        }
        total_blocks += (file_stat.st_blocks * (block_size/(512) )); // Calculate total blocks
        if (show_details) {
            // Print details if -l flag is given
            print_details(file_stat,entries[i]->d_name);
            
        } else {
            // Print file/directory names with appropriate color
            if (S_ISDIR(file_stat.st_mode)) {
                printf("\033[1;34m%s\033[0m", entries[i]->d_name); // Blue for directories
            } else if (file_stat.st_mode & S_IXUSR) {
                printf("\033[1;32m%s\033[0m", entries[i]->d_name); // Green for executables
            } else {
                printf("%s", entries[i]->d_name); // White for regular files
            }
            printf("\n");
        }
    }
    if (show_details) {
        printf("total %lld\n", total_blocks/16);
    }

    closedir(dp);
}

