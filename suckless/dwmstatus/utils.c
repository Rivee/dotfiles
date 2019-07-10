#include "utils.h"




FILE* open_file(char *path)
{
    FILE* file = fopen(path, "r");
    if (!file)
        return NULL;
    return file;
}


char* readline(FILE *file, size_t *size)
{
    if (!file) {
        return NULL;
    }
    char *line = NULL;
    size_t s = 0;
    *size = getline(&line, &s, file); 
    if (*size == -1)
        return NULL;
    return line;
}
