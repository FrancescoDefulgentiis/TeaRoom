#ifndef Files_h
#define Files_h
#include <stdio.h>
#include <stdlib.h>

/*
 Some basic utilities for dealing with files.
 */
unsigned long get_file_size(char *path);
void write_file(char *path, void *data, unsigned long size);
void append_file(char *path, void *data, unsigned long size);
void * read_file(char *path);

#endif 
