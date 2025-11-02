# Custom C Shell Implementation

## Project Overview
This project implements a fully-functional Unix-like shell written entirely in C, designed to demonstrate core systems programming concepts including process management, file operations, and command parsing. Developed as a showcase of low-level programming skills, this shell replicates key features of standard shells like bash while adding custom functionality.

**Key Value Proposition**:
- Demonstrates deep understanding of Linux/Unix internals
- Showcases clean C code architecture
- Implements complex systems programming concepts
- Features persistent command history and background process management

## Features & Technical Highlights

### Core Shell Functionality
- **Command Parsing Engine**: Handles complex input including:
  - Multiple commands separated by semicolons
  - Background processes (with `&` suffix)
  - Built-in vs system command routing
- **Process Management**:
  - Fork/exec implementation with proper signal handling
  - Foreground/background process tracking
  - Automatic reaping of zombie processes
  - Execution time reporting for long-running processes

### Custom Built-in Commands

#### `warp` - Enhanced Directory Navigation
```bash
warp ~       # Home directory (uses getenv("HOME"))
warp -       # Previous directory (maintains stack)
warp ..      # Parent directory (chdir implementation)
warp /path   # Absolute/relative path resolution
```
*Implementation Details*: Uses `chdir()` with path resolution and maintains previous directory state.

#### `peek` - Advanced File Listing
```bash
peek -a      # Shows hidden files (implements . file filtering)
peek -l      # Detailed view with permissions/size (uses stat())
peek -al     # Combines flags (proper flag parsing)
```
*Technical Notes*: Implements `opendir()/readdir()` with custom sorting and colored output.

#### `proclore` - Process Inspection
```bash
proclore      # Shows shell process info
proclore 1234 # Details for PID 1234
```
*Implementation*: Parses `/proc/[pid]/` filesystem to extract process details.

#### `pastevents` - Persistent Command History
```bash
pastevents           # Shows numbered history
pastevents purge     # Clears history (maintains file integrity)
pastevents execute 3 # Re-executes command #3
```
*Architecture*: Circular buffer implementation with file persistence (`history.txt`).

## Technical Deep Dive

### Code Structure
```text
├── main.c            # Core shell loop and dispatcher
├── bgfghandling.c    # Process creation/management
├── pastevents.c      # History implementation
├── printprocinfo.c   # Process inspection logic
├── printdirectorycontent.c # File listing
└── headers.h         # Common definitions
```

### Key Algorithms
1. **Command Processing Pipeline**:
   - Input tokenization (handles quoting/spaces)
   - Semicolon separation
   - Built-in vs external command routing

2. **Background Process Manager**:
   - Tracks PIDs in global array
   - Periodic status checks via `waitpid(WNOHANG)`
   - Notification system for completed processes

3. **History System**:
   - Circular buffer with O(1) insertion
   - File I/O for persistence
   - Duplicate command filtering

## Building & Running
```bash
# Compile with debug symbols
gcc -g main.c prompt.c -o custom_shell

# Run the shell
./custom_shell
```



### Key Technical Demonstrations
- **Systems Programming**: Direct interaction with Linux kernel APIs
- **Memory Management**: Proper allocation/freeing throughout
- **Error Handling**: Comprehensive error checking/reporting
- **Signal Handling**: SIGCHLD for background processes
- **File I/O**: History persistence implementation

### Design Decisions
1. **Modular Architecture**: Separated concerns into logical modules
2. **Error Resilience**: Graceful handling of invalid commands
3. **User Experience**: Color output, execution timing, etc.
4. **Performance**: Minimal overhead in main loop


## Author
[C Swaroop]
[cswaroop2004@gmail.com]
[https://github.com/SwarC7]
