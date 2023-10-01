/*
 * packet.h
 *
 *  Created on: Sep 21, 2023
 *      Author: diegogilbert
 */

#ifndef PACKET_H_
#define PACKET_H_
#include <string.h>

typedef enum { IN_IN, IN_OUT, OUT_IN } Direction;
typedef enum { IGMP, TCP, UDP } Protocol;
typedef unsigned int Count;

typedef struct Packet {
    long long timestamp;
    Direction direction;
    char sourceIP[16];
    char destIP[16];
    Protocol protocol;
    unsigned int port;
    Count bytes;
} Packet;

typedef int (*CompareFunc)(Packet*, Packet*);

Packet* createPackets(int N);
Direction countDirections(Packet* packets, int N, int* c1, int* c2, int* c3);
void insertionSort(Packet* packets, int N, CompareFunc compare1, CompareFunc compare2);
void insertionSort1(Packet* packets, int N, CompareFunc compare1, CompareFunc compare2);

#endif /* PACKET_H_ */
