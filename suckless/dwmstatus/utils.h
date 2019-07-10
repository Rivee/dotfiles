#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE

#define BEGINS_WITH(s1, s2) (strncmp(s1, s2, strlen(s2)) == 0)


FILE* open_file(char *path);
char* readline(FILE *file, size_t *size);
