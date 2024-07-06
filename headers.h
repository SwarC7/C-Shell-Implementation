#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/time.h>
#include <getopt.h>


// #include "prompt.h"
// #include "bgfghandling.h"
// #include "pastevents.h"
// #include "printdetails.h"
// #include "printdirectorycontent.h"
// #include "printprocinfo.h"
// #include "seek.h"
// #include "trimspaces.h"


#define MAX_INPUT_LENGTH 1024
#define MAX_PATH_LENGTH 1024
#define MAX_HISTORY_SIZE 15
#define MAX_COMMAND_LENGTH 1024
#define MAX_BACKGROUND_PROCESSES 10






struct BackgroundProcess {
    int pid;
    char command[MAX_COMMAND_LENGTH];
    int status; // To store exit status
};

extern struct BackgroundProcess background_processes[MAX_BACKGROUND_PROCESSES];
extern int bg_process_count;


struct Command {
    char command[MAX_COMMAND_LENGTH];
};

extern struct Command history[MAX_HISTORY_SIZE];
extern int history_count;
extern char prev_directory[MAX_PATH_LENGTH];

#endif
