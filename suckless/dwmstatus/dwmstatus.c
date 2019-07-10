#include "comps.h"

#include <X11/Xlib.h>
#include <stdarg.h>

static Display *dpy;

void setstatus(char *str) 
{
    XStoreName(dpy, DefaultRootWindow(dpy), str);
    XSync(dpy, False);
}

char *smprintf(char *fmt, ...)
{
	va_list fmtargs;
	char *ret;
	int len;

	va_start(fmtargs, fmt);
	len = vsnprintf(NULL, 0, fmt, fmtargs);
	va_end(fmtargs);

	ret = malloc(++len);
	if (ret == NULL) {
		perror("malloc");
		exit(1);
	}

	va_start(fmtargs, fmt);
	vsnprintf(ret, len, fmt, fmtargs);
	va_end(fmtargs);

	return ret;
}

int main()
{

    const char* interface = "wlp3s0";
    const char* inter_local = "enp0s31f6";

	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "dwmstatus: cannot open display.\n");
		return 1;
	}

    int i = 0;
    char *essid = NULL, *ip = NULL, *bat = NULL, *load = NULL, 
         *time = NULL, *disk = NULL, *rssi = NULL;
    char *st = NULL;

	for (;;sleep(1)) {


        if (!(i % 10)) {
            free(rssi);
            free(essid);
            free(ip);
            if (is_up(inter_local)) {
                essid = get_essid(inter_local);
                ip = ipv4(inter_local);
                rssi = get_rssi(inter_local);
            } else if (is_up(interface)){
                essid = get_essid(interface);
                ip = ipv4(interface);
                rssi = get_rssi(interface);
            } else {
                essid = NULL;
                ip = NULL;
                rssi = NULL;
            }
        }

        bat = get_output_batt_all();
        load = get_load();

        if (!(i % 5)) {
            free(disk);
            free(time);
            time = get_time();
            disk = get_disk_free("/");
        }

        if (is_up(interface)) {
            st = smprintf("%s GiB|W: (%s at %s) %s|E: down |%s|%s|%s", disk, 
                    rssi, essid, ip, bat, load, time);
        } else if (is_up(inter_local)) {
            st = smprintf("%s GiB|W: down|E: (%s) %s|%s|%s|%s", disk, 
                    essid, ip, bat, load, time);
        } else {
            st = smprintf("%s GiB|W: down|E: down |%s|%s|%s", disk, bat, load, 
                    time);
        }

		setstatus(st);
        free(bat);
        free(load);
        i++;
	}

	XCloseDisplay(dpy);

	return 0;
}

