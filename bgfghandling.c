
#include "bgfghandling.h"

void execute_command( char *command) {
    // Check if the command should be run in the background
    int background = 0;
    if (strlen(command) > 0 && command[strlen(command) - 1] == '&') {
        background = 1;
        command[strlen(command) - 1] = '\0'; // Remove the '&' character
    }

    int pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) { // Child process
        char *args[MAX_INPUT_LENGTH];
        int argc = 0;

        char *token = strtok(command, " \t\n");
        while (token != NULL) {
            args[argc++] = token;
            token = strtok(NULL, " \t\n");
        }

        args[argc] = NULL; // Null-terminate the argument array

        // Execute the command
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else { // Parent process
        if (background) {
            // Print the child process ID
            printf("[%d]\n", pid);
            // Store the process information in the background_processes array
            background_processes[bg_process_count].pid = pid;
            strncpy(background_processes[bg_process_count].command, command, MAX_COMMAND_LENGTH);
            bg_process_count = (bg_process_count + 1) % MAX_BACKGROUND_PROCESSES;
        } else if (!background) {
            struct timeval start_time, end_time;
            gettimeofday(&start_time, NULL);

            int status;
            waitpid(pid, &status, 0);

            gettimeofday(&end_time, NULL);
            double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                                  (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

            if (elapsed_time > 2) {
                printf("%s : %.0fs\n", command, elapsed_time);
            }
        }
    }
}

void wait_for_background_processes() {
    for (int i = 0; i < bg_process_count; i++) {
        int status;
        pid_t result = waitpid(background_processes[i].pid, &status, WNOHANG);

        if (result == 0) {
            // Background process still running
            continue;
        } else if (result == -1) {
            // Error occurred
            perror("waitpid");
            continue;
        }

        // Process has finished
        if (WIFEXITED(status)) {
            printf("[%d] %s  exited normally (%d)\n",
                   background_processes[i].pid,
                   background_processes[i].command,
                   WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("[%d] %s exited abnormally (Signal %d)\n",
                   background_processes[i].pid,
                   background_processes[i].command,
                   WTERMSIG(status));
        }

        // Remove the finished process from the array
        bg_process_count--;
        for (int j = i; j < bg_process_count; j++) {
            background_processes[j] = background_processes[j + 1];
        }
        i--; // Check the new process at the same index again
    }
}

