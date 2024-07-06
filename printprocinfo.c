
#include "printprocinfo.h"
void print_process_info(int pid) {
    char status_path[MAX_PATH_LENGTH];
    snprintf(status_path, sizeof(status_path), "/proc/%d/status", pid);

    FILE *status_file = fopen(status_path, "r");
    if (status_file == NULL) {
        perror("proclore");
        return;
    }

    char line[MAX_COMMAND_LENGTH];
    char process_status[MAX_COMMAND_LENGTH] = "";
    int process_group = 0;
    unsigned long vsz = 0;

    while (fgets(line, sizeof(line), status_file)) {
        if (strncmp(line, "State:", 6) == 0) {
            sscanf(line + 6, "%s", process_status);
        } else if (strncmp(line, "VmSize:", 7) == 0) {
            sscanf(line + 7, "%lu", &vsz);
        }
    }

    fclose(status_file);

    // Extract process group from /proc/[pid]/stat
    char stat_path[MAX_PATH_LENGTH];
    snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);

    FILE *stat_file = fopen(stat_path, "r");
    if (stat_file == NULL) {
        perror("proclore");
        return;
    }

    int stat_pid, stat_ppid, stat_pgrp, stat_session;
    char stat_comm[MAX_COMMAND_LENGTH];

    fscanf(stat_file, "%d %s %*c %d %d %d", &stat_pid, stat_comm, &stat_ppid, &stat_pgrp, &stat_session);
    process_group = stat_pgrp;

    fclose(stat_file);

    // Get executable path from /proc/[pid]/exe
    char exe_path[MAX_PATH_LENGTH];
    snprintf(exe_path, sizeof(exe_path), "/proc/%d/exe", pid);

    char executable_path[MAX_PATH_LENGTH];
    ssize_t len = readlink(exe_path, executable_path, sizeof(executable_path) - 1);
    if (len != -1) {
        executable_path[len] = '\0';
    } else {
        perror("proclore");
        return;
    }

    // Print the gathered process information
    printf("pid : %d\n", pid);
    printf("process status : %s\n", process_status);
    printf("Process Group : %d\n", process_group);
    printf("Virtual memory : %lu\n", vsz);
    printf("executable path : %s\n", executable_path);
}
