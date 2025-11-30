# Custom C Shell Implementation (C-Shell)

[![C Language](https://img.shields.io/badge/Language-C-00599C?logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Unix Shell](https://img.shields.io/badge/Platform-Unix/Linux-24273A?logo=linux)](https://en.wikipedia.org/wiki/Unix)
[![Systems Programming](https://img.shields.io/badge/Category-Systems_Programming-0077B6)](https://en.wikipedia.org/wiki/System_programming_language)


## Table of Contents
- [Project Overview](#project-overview)
- [Features & Technical Highlights](#features--technical-highlights)
  - [Core Shell Functionality](#core-shell-functionality)
  - [Custom Built-in Commands](#custom-built-in-commands)
    - [`warp` - Enhanced Directory Navigation](#warp---enhanced-directory-navigation)
    - [`peek` - Advanced File Listing](#peek---advanced-file-listing)
    - [`proclore` - Process Inspection Tool](#proclore---process-inspection-tool)
    - [`pastevents` - Persistent Command History Management](#pastevents---persistent-command-history-management)
    - [`seek` - File/Directories Search Engine](#seek---filedirectories-search-engine)
- [Technical Deep Dive](#technical-deep-dive)
  - [Architecture Overview](#architecture-overview)
  - [Core Algorithms & Data Structures](#core-algorithms--data-structures)
- [Setup Instructions](#setup-instructions)
  - [Prerequisites](#prerequisites)
  - [Installation & Compilation](#installation--compilation)
  - [Testing & Verification](#testing--verification)
- [Technical Demonstrations](#technical-demonstrations)
- [Use Cases & Applications](#use-cases--applications)
- [Author](#author)


## Project Overview

This is an advanced custom shell implementation written entirely in C, designed to demonstrate deep understanding of Unix/Linux internals and systems programming concepts. The shell replicates and extends functionality found in standard shells like bash, with custom features and optimized performance. This project showcases proficiency in low-level programming, process management, file operations, and command parsing.

**Key Value Propositions**:
- **Systems Programming Mastery**: Demonstrates advanced understanding of Unix/Linux internals, process management, and system APIs
- **Advanced C Programming**: Clean, modular architecture with proper memory management and error handling
- **Real-world Application**: Production-quality code with comprehensive feature set
- **Problem-Solving Skills**: Complex algorithmic implementations for command parsing, process tracking, and file searching
- **Performance Optimization**: Efficient algorithms with minimal overhead in main execution loop

## Features & Technical Highlights

### Core Shell Functionality
- **Advanced Command Parsing Engine**:
  - Handles multiple commands separated by semicolons
  - Background execution support (with `&` suffix)
  - Dynamic routing between built-in and system commands
- **Robust Process Management**:
  - Fork/exec implementation with proper signal handling
  - Foreground/background process tracking system
  - Automatic zombie process reaping
  - Execution time monitoring for long-running processes

### Custom Built-in Commands

#### `warp` - Enhanced Directory Navigation (Advanced `cd` equivalent)
```bash
warp ~       # Navigate to home directory using getenv("HOME")
warp -       # Switch to previous directory (maintains directory stack)
warp ..      # Navigate to parent directory 
warp /path   # Navigate to absolute/relative path
```
*Implementation Details*: Uses `chdir()` with comprehensive path resolution, maintains previous directory state for quick navigation.

#### `peek` - Advanced File Listing (Enhanced `ls` equivalent)
```bash
peek -a      # Display all files including hidden files (implementing . file filtering)
peek -l      # Detailed view with permissions, size, ownership (using stat())
peek -al     # Combined view (equivalent to ls -la)
peek [dir]   # List contents of specified directory
```
*Technical Notes*: Implements `opendir()/readdir()` with custom lexicographic sorting, colored output for different file types, and efficient memory usage.

#### `proclore` - Process Inspection Tool (Custom `ps` equivalent)
```bash
proclore      # Displays current shell process information
proclore 1234 # Shows detailed information for specific process PID 1234
```
*Implementation*: Direct parsing of `/proc/[pid]/` filesystem to extract real-time process details including memory usage, process state, and executable path.

#### `pastevents` - Persistent Command History Management
```bash
pastevents           # Displays numbered command history (circular buffer)
pastevents purge     # Clears command history (with persistent file management)
pastevents execute 3 # Re-executes command #3 from history
```
*Architecture*: Implements circular buffer with O(1) insertion, file persistence via `history.txt`, and automatic duplicate command filtering.

#### `seek` - File/Directories Search Engine
```bash
seek file_name                    # Search for file/directory recursively
seek -f file_name                 # Search for files only
seek -d dir_name                  # Search for directories only  
seek -e file_name                 # Execute found file upon discovery
seek -f file_name /path/to/search # Search in specific directory
```
*Technical Implementation*: Recursive directory traversal with efficient search algorithms, pattern matching, and execution capabilities.

## Technical Deep Dive

### Architecture Overview
The project follows a modular, service-oriented architecture where each feature is implemented in dedicated modules for maintainability and scalability.

```
├── main.c                    # Core shell loop, command dispatcher, main logic
├── bgfghandling.c/.h         # Process creation, management, foreground/background handling
├── pastevents.c/.h           # Command history management, persistence logic
├── printdetails.c/.h         # File permission and metadata formatting
├── printdirectorycontent.c/.h # Directory listing with sorting and filtering
├── printprocinfo.c/.h        # Process information extraction from /proc
├── prompt.c/.h               # Dynamic prompt generation with path resolution
├── seek.c/.h                 # File/directory search functionality
├── trimspaces.c/.h           # Utility functions for string processing
└── headers.h                 # Common definitions, constants, structures
```

### Core Algorithms & Data Structures

1. **Command Processing Pipeline**:
   - Tokenization engine that handles complex input with proper quote/space handling
   - Semicolon-based command separation for multiple command execution
   - Efficient routing mechanism to direct-built-in vs external command execution

2. **Background Process Management System**:
   - PID tracking using global array structure
   - Periodic status checking using `waitpid(WNOHANG)`
   - Intelligent notification system for completed background processes
   - Memory-efficient process cleanup

3. **Command History Architecture**:
   - Circular buffer implementation for O(1) insertion and retrieval
   - File I/O with automatic persistence to `history.txt`
   - Duplicate command filtering algorithm
   - Execute-from-history functionality with full command reprocessing

4. **Advanced File Search Algorithm**:
   - Recursive directory traversal with optimal memory usage
   - Pattern matching with flag support
   - File vs directory discrimination and filtering

## Setup Instructions

### Prerequisites
- Linux/Unix operating system with bash shell
- GCC (GNU Compiler Collection) installed
- Standard C development libraries
- Git for version control (optional)

### Installation & Compilation
```bash
# Clone or download the repository
git clone <repository-url>
cd C-Shell-Implementation

# Compile the shell
make

# Or compile manually
gcc -g main.c prompt.c bgfghandling.c pastevents.c printdetails.c printdirectorycontent.c printprocinfo.c seek.c trimspaces.c -o cshell

# Run the custom shell
./cshell
```

### Testing & Verification
```bash
# After compilation, run the shell and test basic commands:
./cshell

# Example usage:
peek -la                    # List current directory with details
warp /tmp                   # Navigate to temp directory
ls &                        # Run ls in background
proclore                    # View current shell process info
pastevents                  # View command history
seek README.md              # Find README.md file recursively
```

### Expected Output
- Custom prompt displaying user@system:directory format
- All built-in commands should function as described
- Background processes should execute with proper notification
- History should persist between sessions

## Technical Demonstrations

### Systems Programming Concepts
- **Process Management**: Direct interaction with fork/exec/wait system calls
- **File Operations**: Advanced file I/O, directory traversal, and `/proc` filesystem interaction
- **Memory Management**: Proper memory allocation, string handling, and resource cleanup
- **System APIs**: Comprehensive use of Linux/Unix system calls and libraries

### Advanced Programming Techniques
- **Error Handling**: Comprehensive error checking with appropriate user feedback
- **Modular Design**: Clean separation of concerns with well-defined interfaces
- **Performance Optimization**: Efficient algorithms with minimal resource usage
- **Code Maintainability**: Well-structured, documented code with consistent naming

### Security Considerations
- Input validation and sanitization
- Safe string operations to prevent buffer overflows
- Proper memory management to prevent leaks
- Robust error handling to prevent crashes

## Use Cases & Applications

### Educational Purpose
- Demonstrates core operating system concepts
- Provides hands-on experience with Unix/Linux system calls
- Excellent learning resource for systems programming

### Professional Portfolio
- Showcases advanced C programming skills
- Demonstrates understanding of complex software architecture
- Proves capability to handle intricate systems programming tasks

## Author
**C Swaroop**  
Email: cswaroop2004@gmail.com  
GitHub: https://github.com/SwarC7

