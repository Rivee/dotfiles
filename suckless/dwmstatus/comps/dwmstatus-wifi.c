#include "../comps.h"

char *get_essid(const char *interface)
{
	char *id = calloc(IW_ESSID_MAX_SIZE, sizeof(char));

	struct iwreq wreq;
	memset(&wreq, 0, sizeof(struct iwreq));

	strcpy(wreq.ifr_name, interface);

	wreq.u.essid.length = IW_ESSID_MAX_SIZE + 1;

	int sockid;
	if ((sockid = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		err(1, "Fail to create socket : %s \n", strerror(errno));
		return NULL;
	}

	wreq.u.essid.pointer = (caddr_t *)id;
	wreq.u.essid.flags = 0;

	if (ioctl(sockid, SIOCGIWESSID, &wreq) == -1) {
		err(1, "Fail ioctl  : %s \n", strerror(errno));
		return NULL;
	}

	close(sockid);

	return (char *)wreq.u.essid.pointer;
}

char *get_rssi(const char *interface)
{
	FILE *file = 0;
	if (!(file = fopen("/proc/net/wireless", "r"))) {
		err(1, "Fail fopen  : %s \n", strerror(errno));
		return NULL;
	}

	char buff[100] = { 0 };
	char *data;

	do {
		if (!(fgets(buff, 100, file))) {
			err(1, "Fail fgetc  : %s \n", strerror(errno));
			return NULL;
		}
	} while (!(data = strstr(buff, interface)));

	data += strlen(interface) + 1;

	int link = 0;
	sscanf(data, " %*d   %d  %*d  %*d\t\t  %*d\t   ", &link);
	char *res = calloc(sizeof(int) * 2, sizeof(char));
	sprintf(res, "%d", (int)((float)link * 100 / 70));
	fclose(file);
	return res;
}

int is_up(const char *interface)
{
	char path[PATH_MAX] = { 0 };

	sprintf(path, "/sys/class/net/%s/operstate", interface);

	FILE *file = 0;
	if (!(file = fopen(path, "r"))) {
		err(1, "Fail fopen  : %s \n", strerror(errno));
		return -1;
	}

	char st[10] = { 0 };

	if (!(fgets(st, 10, file))) {
		err(1, "Fail fgetc  : %s \n", strerror(errno));
		return -1;
	}

	fclose(file);

	return !strcmp("up\n", st);
}
