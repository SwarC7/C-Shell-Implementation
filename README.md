# Custom C Shell Implementation
- This project implements a custom Unix-like shell in C, providing core shell functionalities including command execution, process management, file operations, and command history management. The shell aims to replicate basic features of standard Unix shells while adding some custom functionality.

  
# Key features
- # 1.Command Execution
     - Foreground Process Execution: Commands run in foreground with parent process waiting
     - Background Process Execution: Commands with '&' suffix run in background
     - Multiple Command Support: Handles multiple commands separated by semicolons
     - Process Time Tracking: Displays execution time for processes taking > 2 seconds
- # 2.Built-in Commands
     - # Warp-Directory navigation (similar to cd)
         - Support for absolute/relative paths
         - Special arguments: ~, -, ..
         - Usage: warp [directory]
         - # Options:
                - warp ~ : Navigate to home directory
                - warp - : Go to previous directory
                - warp .. : Move up one directory
                - warp [path] : Navigate to specified path (absolute/relative)
     - # Peek-Directory listing (similar to ls)
         - Flags: -a (show hidden), -l (detailed view)
         - Usage: peek [options] [directory]
         - # Options:
                - -a : Show hidden files
                - -l : Show detailed view (permissions, size, timestamps)
         - # Features:
             - Color-coded output (blue for directories, green for executables)
             - Sorted listing
             - Shows total block size when using -l
     - # Proclore-Process information display
         - Shows PID, status, group, memory, executable path
         - Usage: proclore [pid]
         - Note: Cannot access root process information
     - # Pastevents-Command history management
         - Store/display command history
         - # Usage:
               - pastevents : Display command history
               - pastevents purge : Clear history
               - pastevents execute <index> : Execute command from history
         - # Features:
            - Persistent storage across sessions
            - Prevents duplicate consecutive commands
            - Stores up to MAX_HISTORY_SIZE commands
     - # Background/Foreground Process Management
         - Background Execution:
             - Add & at end of command
             - Shows process ID when launched
             - Notifies on completion
         - Foreground Execution:
             - Regular command execution
             - Shows execution time for processes taking > 2 seconds
         - # Features:
             - Process status monitoring
             - Exit status reporting
             - Background process cleanup
         - # Example:
               - Backgrund: sleep 10 &
               - Foreground: sleep 5
     - # System Commands
        - Supports standard system commands through execvp
        - # Examples:
              - cat file.txt
              - grep pattern file
              - ps aux
              - Any other valid system command

           
      
- # 3.Process Management
     - Background process status monitoring
     - Process creation and termination handling
     - Process information retrieval
 
   # Core Components
   - # 1.Main Controller (main.c)
        - Command parsing and routing
        - Shell loop management
        - Signal handling
   - # 2.Process Handler (bgfghandling.c)
        - Process creation (fork/exec)
        - Background process tracking
        - Process status monitoring
   - # 3.Command Processors
        - Directory operations (printdirectorycontent.c)
        - Process information (printprocinfo.c)
        - History management (pastevents.c)
   - # 4.Utility Modules
       - String handling (trimspaces.c)
       - File detail printing (printdetails.c)

# Control Flow
  - # 1.Shell Initalisation
      - Load command history
      - Set up signal handlers

  - # 2.Command Processing Loop
      - Display prompt
      - Read user input
      - Parse commands (handle semicolon separation)
      - For each command:
                  - Check for built-in commands
                  - Process commnd flags/arguments
                  - Execute appropriate handler
     - Check background process status

 -  # 3.Command Execution
      - Fork new process
      - In child:
            - Set up environment
            - Execute command
      - In parent:
            - Track process (background/foreground)
            - Wait if foreground
            - Update status if background

# How to Run
- # 1.Compilation
    make (or) gcc -g main.c prompt.c
- # 2.Execution
    ./a.out

# Implementation Details

  - # 1.Process Management
     - Uses fork() for process creation
     - execvp() for command execution
     - waitpid() for process status monitoring
     - Background processes tracked in global array
  - # 2.File Operations
     - Directory operations using opendir/readdir
     - File status using stat()
     - Path manipulation for relative/absolute paths
  - # 3.Command History
     - Circular buffer implementation
     - Persistent storage in file
     - Duplicate command filtering
   
# Assumptions and Limitatons
 - Proclore limited to user processes (no root access)
 - Background/foreground handling limited to bash commands
 - Invalid commands are saved in history
 - Shell exits with Ctrl+C
     
  
  
