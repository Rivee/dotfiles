#include <err.h>
#include <errno.h>
#include <ifaddrs.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include <stropts.h>
#include <sys/socket.h>
#include <linux/wireless.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <linux/limits.h>

#include <sys/statvfs.h>
#include <math.h>

#include <unistd.h>

#include <time.h>

char *ipv4(const char* interface);
char* get_essid(const char *interface);
char *get_rssi(const char *interface);
int is_up(const char *interface);
char* get_disk_free(const char *path);
int eth_is_up(char *interface);
char *get_state(char *battery);
char* get_perc_all();
char* get_output_batt_all();
char* get_load();
char* get_time();
