#include "../comps.h"

char *get_load()
{
	double arg[1] = { 0 };
	if (getloadavg(arg, 1) < 0) {
		return NULL;
	}

	char *res = calloc(10, sizeof(char));
	sprintf(res, "%.2f", *arg);
	return res;
}
