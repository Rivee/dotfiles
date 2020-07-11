#include "../comps.h"

char* get_disk_free(const char *path)
{
    struct statvfs stat;

    if (statvfs(path, &stat) < 0) {
        err(1, "Fail statvfs : %s ", strerror(errno));
        return NULL;
    }

    char *res = calloc(30, sizeof(char));

    sprintf(res, "%.1lf",
            (double)(stat.f_bavail * stat.f_frsize) / (1.074 * pow(10, 9)));

    return res;
}
