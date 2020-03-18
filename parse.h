#ifndef PARSE_H
#define PARSE_H

#include <stdint.h>
#include <stdio.h>
#include <pcap.h>
#include <QString>

#pragma pack(push,1)
typedef struct {
    uint8_t dst_MAC[6];
    uint8_t src_MAC[6];
    uint16_t ether_type;
}Ether;

typedef struct {
    uint16_t hw_type;
    uint16_t p_type;
    uint8_t hw_len;
    uint8_t p_len;
    uint16_t opcode;
    uint8_t sender_mac[6];
    uint32_t sender_ip;
    uint8_t target_mac[6];
    uint32_t target_ip;
}ARP;

typedef struct {
    uint8_t v_l;
    uint8_t tos;
    uint16_t total_len;
    uint16_t id;
    uint16_t flag;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint32_t src_ip;
    uint32_t dst_ip;
}IP;

typedef struct {
    Ether eth;
    ARP arp;
}ARP_Packet;

typedef struct {
    Ether eth;
    IP ip;
}Packet;

struct info{
    QString name;
    QString desc;
    pcap_if_t * dev{nullptr};
    uint32_t ip;
    uint32_t subnetmask;
    uint32_t gateway;
    uint32_t ip_and_mask;
};


#pragma pack(pop)

#endif // PARSE_H
