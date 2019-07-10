#include "../comps.h"




char* get_time()
{
    time_t t;

    time(&t);
    struct tm *info = localtime(&t);
    char *res = calloc(30, sizeof(char));
    sprintf(res, "%d-%d-%d %02d:%02d:%02d", info->tm_year + 1900, 
            info->tm_mon + 1, info->tm_mday, info->tm_hour, info->tm_min, 
            info->tm_sec);
    return res;
}
