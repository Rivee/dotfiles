#include "../comps.h"


static char* ip(const char* interface, unsigned short sa_family)
{
    struct ifaddrs *ifaddr;
    if (getifaddrs(&ifaddr) < 0) {
        err(1, "getifaddr : %s ", strerror(errno));
        return NULL;
    }

    struct ifaddrs *ifddr;
    for (ifddr = ifaddr; ifddr != NULL; ifddr = ifddr->ifa_next) {
        if (ifddr->ifa_addr) {
            char *h = calloc(NI_MAXHOST, sizeof(char));
            int s = getnameinfo(ifddr->ifa_addr, sizeof(struct sockaddr_in6), h,
                    NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (!strcmp(ifddr->ifa_name, interface) &&
                    (ifddr->ifa_addr->sa_family == sa_family)) {
                freeifaddrs(ifaddr);
                if (s != 0) {
                    err(1, "getnemeinfo : %s ", strerror(errno));
                    return NULL;
                }
                return h;
            }
        }
    }
    freeifaddrs(ifddr);
    return NULL;
}

char *ipv4(const char* interface)
{
    return ip(interface, AF_INET);
}
