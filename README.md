# Custom C Shell Implementation
- This project implements a custom Unix-like shell in C, providing core shell functionalities including command execution, process management, file operations, and command history management. The shell aims to replicate basic features of standard Unix shells while adding some custom functionality.

# Key features
- # 1.Command Execution
     - Foreground Process Execution: Commands run in foreground with parent process waiting
     - Background Process Execution: Commands with '&' suffix run in background
     - Multiple Command Support: Handles multiple commands separated by semicolons
     - Process Time Tracking: Displays execution time for processes taking > 2 seconds
- # 2.Built-in Commands
     - Warp
