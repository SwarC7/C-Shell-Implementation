#include "headers.h"
#include "bgfghandling.c"
#include "pastevents.c"
#include "printdetails.c"
#include "printdirectorycontent.c"
#include "printprocinfo.c"
#include "seek.c"
#include "trimspaces.c"

struct Command history[MAX_HISTORY_SIZE];
int history_count = 0;;
char prev_directory[MAX_PATH_LENGTH];
struct BackgroundProcess background_processes[MAX_BACKGROUND_PROCESSES];
int bg_process_count = 0;


int main() {
   char input[MAX_INPUT_LENGTH];
    char *delimiters = " \t\n;";
    getcwd(prev_directory, MAX_PATH_LENGTH);
    load_history_from_file("history.txt");  // Load history from file

    while (1) {
        print_prompt();

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        

        input[strcspn(input, "\n")] = '\0';
        
        
            char *commands[MAX_INPUT_LENGTH]; // Store separate commands
            int num_commands = 0;

            // Split input by semicolon to get individual commands
            char *token = strtok(input, ";");
            while (token != NULL) {
                 trim_whitespace(token);
               if (strlen(token) > 0) {
            commands[num_commands++] = token;
             }
              token = strtok(NULL, ";");
            }

            // Execute each command sequentially
            for (int i = 0; i < num_commands; i++) {
               
                
                char *current_command = commands[i];
                
                add_to_history(current_command);
              


             if (strncmp(current_command, "warp",4) == 0) {
            add_to_history(current_command);
            char *args[MAX_INPUT_LENGTH];
            int argc = 0;

            char *token = strtok(current_command, delimiters);
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
                else if (strncmp(current_command, "peek",4) == 0) {
                    
                     int show_hidden = 0;
                     int show_details = 0;

                     char *args[MAX_INPUT_LENGTH];
                     int argc = 0;

                     char *token = strtok(input, delimiters);
                    while (token != NULL) {
                    args[argc++] = token;
                    token = strtok(NULL, delimiters);
                    }

         // Check if the first argument is "peek"
                     if (argc == 1) {
        // No additional arguments, default to the current directory
                     print_directory_contents(getcwd(NULL, 0), show_hidden, show_details);
    } 
                     else if (argc == 2 && strcmp(args[1], "..") == 0) {
        // "peek .." command, list contents of the parent directory
                      char parent_dir[MAX_PATH_LENGTH];
                      snprintf(parent_dir, sizeof(parent_dir), "%s/..", getcwd(NULL, 0));
                      print_directory_contents(parent_dir, show_hidden, show_details);
    } 
                     else {
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
                else if (strcmp(current_command, "pastevents") == 0) {
                     print_history();
                }
                else if (strcmp(current_command, "pastevents purge") == 0) {
                    purge_history();
                }
                else if (strncmp(current_command, "pastevents execute", 18) == 0) {
                    int index;
            sscanf(current_command, "%*s %*s %d", &index);
            execute_from_history(index);
                }
                else if (strncmp(current_command, "proclore", 8) == 0) {
                    char *args[MAX_INPUT_LENGTH];
        int argc = 0;

        char *token = strtok(current_command, delimiters);
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
       else if (strncmp(current_command, "seek", 4) == 0) {
                char *args[MAX_INPUT_LENGTH];
                int argc = 0;

                char *token = strtok(current_command, delimiters);
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
                execute_command(current_command);
              

                }
            

         wait_for_background_processes();
        
    }

    

 
}
}

