#ifndef _PASTEVENTS_H
#define _PASTEVENTS_H
#include "headers.h"



void save_history_to_file(const char *filename);
void load_history_from_file(const char *filename);
void add_to_history(const char *command);
void print_history();
void purge_history();
void execute_from_history(int index);

#endif