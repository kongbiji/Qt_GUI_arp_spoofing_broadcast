#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdint.h>
#include <stdio.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

void print_ip(uint32_t ip){
    printf("%d.%d.%d.%d\n", (ip)&0xFF, (ip>>8)&0xFF, (ip>>16)&0xFF, (ip>>24)&0xFF);
}

void get_ip(char * dev, char * ret_ip){
    struct ifreq ifr;
    char ipstr[40];
    int s;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if (ioctl(s, SIOCGIFADDR, &ifr) < 0) {
        printf("Error");
        exit(1);
    } else {
        inet_ntop(AF_INET, ifr.ifr_addr.sa_data+2,
                  ipstr,sizeof(struct sockaddr));
    }
    uint32_t ip;
    ip = inet_addr(ipstr);
    sprintf(ret_ip,"%d.%d.%d.%d", (ip)&0xFF, (ip>>8)&0xFF, (ip>>16)&0xFF, (ip>>24)&0xFF);
}

void get_subnet(char * dev, char * ret_sub){
    int sock;
    struct ifreq ifr;
    struct sockaddr_in *sin;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)  {
        printf("[-] Error in get_subnet, binding sock\n");
        exit(1);
    }
    strcpy(ifr.ifr_name, dev);

    if (ioctl(sock, SIOCGIFNETMASK, &ifr)< 0){
        printf("[-] Error int get_subnet, ioctl()\n");
        exit(1);
    }
    sin = (struct sockaddr_in*)&ifr.ifr_addr;
    strcpy(ret_sub, inet_ntoa(sin->sin_addr));
}

#endif // FUNCTION_H
