

#include "prompt.h"
#include "bgfghandling.h"
#include "pastevents.h"
#include "printdetails.h"
#include "printdirectorycontent.h"
#include "printprocinfo.h"
#include "seek.h"
#include "trimspaces.h"

void save_history_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening history file");
        return;
    }

    for (int i = 0; i < history_count; i++) {
        fprintf(file, "%s\n", history[i].command);
    }

    fclose(file);
}

void load_history_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening history file");
        return;
    }

    char line[MAX_COMMAND_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        add_to_history(line);
    }

    fclose(file);
}


void add_to_history(const char *command) {
    if (history_count > 0 && strcmp(history[history_count - 1].command, command) == 0) {
        return; // Don't store duplicates
    }

    if (strstr(command, "pastevents") == NULL) {
        strcpy(history[history_count].command, command);
        history_count = (history_count + 1) % MAX_HISTORY_SIZE; // Circular buffer behavior
    }
    save_history_to_file("history.txt");
   
}


void print_history() {
    for (int i = 0; i <history_count; i++) {
        printf("%d %s\n",i+1, history[i].command);
    }
}

void purge_history(){
    FILE *file = fopen("history.txt", "w");
    if (file == NULL) {
        perror("Error opening file for purging");
        return;
    }

    // Simply opening the file in write mode truncates it to empty
    fclose(file);
    history_count=0;
}


void execute_from_history(int index) {
    if (index < 1 || index > history_count) {
        printf("Invalid index\n");
        return;
    }
   
   char*command= history[history_count - index].command;
   add_to_history(command);
   char *delimiters = " \t\n";
    getcwd(prev_directory, MAX_PATH_LENGTH);

   if (strncmp(command, "warp", 4) == 0) 
        {   
            char *args[MAX_INPUT_LENGTH];
            int argc = 0;

            char *token = strtok(command, delimiters);
            while (token != NULL) {
                args[argc++] = token;
                token = strtok(NULL, delimiters);
            }

            if (argc == 1) {
                chdir(getenv("HOME"));
            } else {
                for (int i = 1; i < argc; i++) {
                    char *path = args[i];

                    if (strcmp(path, "~") == 0) {
                        chdir(getenv("HOME"));
                    } else if (strcmp(path, "..") == 0) {
                        chdir("..");
                    } else if (strcmp(path, "-") == 0) {
                        // Swap current directory and previous directory
                        char temp[MAX_PATH_LENGTH];
                        strcpy(temp, prev_directory);
                        strcpy(prev_directory, getcwd(NULL, 0)); // Store current directory before changing
                        if (chdir(temp) != 0) {
                            perror("warp");
                        }
                    } else {
                        if (chdir(path) != 0) {
                            perror("warp");
                        }
                    }

                    char cwd[MAX_PATH_LENGTH];
                    getcwd(cwd, MAX_PATH_LENGTH);
                    printf("%s\n", cwd);
                }
            }
        }

        else if (strncmp(command, "peek", 4) == 0) {
       
        int show_hidden = 0;
        int show_details = 0;

        char *args[MAX_INPUT_LENGTH];
        int argc = 0;

        char *token = strtok(command, delimiters);
        while (token != NULL) {
            args[argc++] = token;
            token = strtok(NULL, delimiters);
        }

         // Check if the first argument is "peek"
    if (argc == 1) {
        // No additional arguments, default to the current directory
        print_directory_contents(getcwd(NULL, 0), show_hidden, show_details);
    } else if (argc == 2 && strcmp(args[1], "..") == 0) {
        // "peek .." command, list contents of the parent directory
        char parent_dir[MAX_PATH_LENGTH];
        snprintf(parent_dir, sizeof(parent_dir), "%s/..", getcwd(NULL, 0));
        print_directory_contents(parent_dir, show_hidden, show_details);
    } else {
        // Process flags and path
        int path_index = 0; // Index of the path argument
        for (int i = 1; i < argc; i++) {
            if (args[i][0] == '-') {
                // Process flags
                for (size_t j = 1; j < strlen(args[i]); j++) {
                    if (args[i][j] == 'a') {
                        show_hidden = 1;
                    } else if (args[i][j] == 'l') {
                        show_details = 1;
                    } 
                       
                    
                }
            } else {
                // Found the path argument
                path_index = i;
                break;
            }
        }

        // Get the path (default to current directory)
        char *path = path_index > 0 ? args[path_index] : getcwd(NULL, 0);

        // Call the print_directory_contents function with the specified options
        print_directory_contents(path, show_hidden, show_details);
    }

  
 }
 else if (strcmp(command, "pastevents") == 0) {
                     print_history();
                }
                else if (strcmp(command, "pastevents purge") == 0) {
                    purge_history();
                }
                else if (strncmp(command, "pastevents execute", 18) == 0) {
                    int index;
            sscanf(command, "%*s %*s %d", &index);
            execute_from_history(index);
                }
                else if (strncmp(command, "proclore", 8) == 0) {
                    char *args[MAX_INPUT_LENGTH];
        int argc = 0;

        char *token = strtok(command, delimiters);
        while (token != NULL) {
            args[argc++] = token;
            token = strtok(NULL, delimiters);
        }

        if (argc == 1) {
            // Print information about the shell process
            int shell_pid = getpid();
            print_process_info(shell_pid);
        } else if (argc == 2) {
            // Print information about the specified process
            int pid;
            if (sscanf(args[1], "%d", &pid) == 1) {
                print_process_info(pid);
            } else {
                printf("Invalid process ID\n");
            }
        } else {
            printf("Usage: proclore [pid]\n");
        }
                }
       else if (strncmp(command, "seek", 4) == 0) {
                char *args[MAX_INPUT_LENGTH];
                int argc = 0;

                char *token = strtok(command, delimiters);
                while (token != NULL) {
                    args[argc++] = token;
                    token = strtok(NULL, delimiters);
                }

               
               
                    int search_files = 0;
                    int search_directories = 0;
                    int execute_mode = 0;
                    int flags=0;

                    // Process flags
                    for (int j = 0; j < argc ; j++) {
                        if (strcmp(args[j], "-d") == 0) {
                            search_directories = 1;
                            flags++;
                        } else if (strcmp(args[j], "-f") == 0) {
                            search_files = 1;
                            flags++;
                        } else if (strcmp(args[j], "-e") == 0) {
                            execute_mode = 1;
                            flags++;
                        } 
                            
                            
                        
                    }
                     if(flags==0&&argc==2)
                  { search_files=1;
                    search_directories=1;
                    const char *target = args[1];
                    const char *target_directory =".";
                  

                    seek(target, target_directory, search_files, search_directories, execute_mode);
                  }
                  if(flags==0&&argc==3)
                  {  search_files=1;
                     search_directories=1;
                    const char *target = args[1];
                    const char *target_directory =args[2];

                    seek(target, target_directory, search_files, search_directories, execute_mode);
                  }
                  if(flags==1&&argc==3)
                  { const char *target = args[2];
                    const char *target_directory =".";
                    seek(target, target_directory, search_files, search_directories, execute_mode);
                  }
                  if(flags==1&&argc==4)
                  {
                    const char *target = args[2];
                    const char *target_directory =args[3];
                    seek(target, target_directory, search_files, search_directories, execute_mode);
                  }
                  if(flags==2&&argc==3)
                  {
                    printf("Invalid Flags");
                  }
                  if(flags==2&&argc==4)
                  {const char *target = args[3];
                    const char *target_directory =".";
                    if((strcmp(args[1],"-d")==0 && strcmp(args[2],"-f")==0) ||( strcmp(args[1],"-f")==0 && strcmp(args[2],"-d")==0))
                    {printf("Invalid Flags\n");
                    }
                    else{
                    seek(target, target_directory, search_files, search_directories, execute_mode);
                    printf("ok");
                    printf("%s %s",args[1],args[2]);
                    }
                  }
                  if(flags==2&&argc==5)
                  {const char *target = args[3];
                    const char *target_directory =args[4];
                     if((strcmp(args[1],"-d")==0 && strcmp(args[2],"-f")==0) ||( strcmp(args[1],"-f")==0 && strcmp(args[2],"-d")==0))
                    {printf("Invalid Flags\n");
                    
                    }
                    else{
                    seek(target, target_directory, search_files, search_directories, execute_mode);
                    }
                   

                  }
                  if(argc>5)
                  {
                    printf("invalid input");
                  }
                  
            
                
       }
        else {  //FOREGROUND AND BACKGROUND PROCESS HANDLING FOR BASH COMMANDS IMPLEMENTED IN c
                execute_command(command);
              

                }




   

   
}

