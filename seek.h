#ifndef _SEEK_H
#define _SEEK_H

#include "headers.h"



int is_directory(const char *path);
void seek(const char *target, const char *target_directory, int search_files, int search_directories, int execute_mode);

#endif