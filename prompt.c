
#include "prompt.h"
void print_prompt() {
    // Do not hardcode the prmopt
    
    
     char username[MAX_PATH_LENGTH];
    char systemname[MAX_PATH_LENGTH];
    char cwd[MAX_PATH_LENGTH];

    // Get username
    getlogin_r(username, MAX_PATH_LENGTH);

    // Get system name
    gethostname(systemname, MAX_PATH_LENGTH);

    // Get current working directory
    getcwd(cwd, MAX_PATH_LENGTH);

    // Replace home directory path with ~
    char *home_dir = getenv("HOME");
    if (home_dir != NULL && strncmp(cwd, home_dir, strlen(home_dir)) == 0) {
        char relative_path[MAX_PATH_LENGTH];
        snprintf(relative_path, sizeof(relative_path), "~%s", cwd + strlen(home_dir));
        printf("<%s@%s:%s> ", username, systemname, relative_path);
    } else {
        printf("<%s@%s:%s> ", username, systemname, cwd);
    }   
}
