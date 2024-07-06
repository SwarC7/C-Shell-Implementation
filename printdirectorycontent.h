#ifndef _PRINTDIRECTORYCONTENT_H
#define _PRINTDIRECTORYCONTENT_H

#include "headers.h"

int compare_entries(const void *a, const void *b);
void print_directory_contents(const char *path, int show_hidden, int show_details);


#endif