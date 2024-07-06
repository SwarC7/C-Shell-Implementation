[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/76mHqLr5)

## How to Run
Run the makefile (or just do gcc 

## Overview
This project involves building a custom shell in C, similar to the Unix shell, with functionalities including basic system commands, process management, file operations, and networking. The shell supports a range of features from command execution to process control and file manipulation.

## Features

- **Command Execution:** Execute system commands in both foreground and background modes.
- **Command History:** Maintain and manage a history of commands.
- **File Operations:** File listing with flags, directory navigation, and searching.
- **Process Management:** View process details, manage background and foreground processes, send signals.
- **I/O Redirection and Pipes:** Redirect input/output streams and chain commands using pipes.
- **Networking:** Fetch man pages from the internet.
- **Custom Commands:** Implement additional features like `neonate` for timed command execution.


# Assumptions
Proclore cannot access information from root processes and gives 
"Permission denied" such as the init process.
Proclore can only access information from user processes and display them.
Foreground and background process handling is only dealt for bash commands implemented using exec()
if no flags are mentioned as arguements to seek command then seek searches for both files as well as directories.
Invalid commands are saved on to pastevents.
Exiting the shell is done using ctrl+C
