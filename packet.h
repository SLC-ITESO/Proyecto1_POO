/*
 * packet.h
 *
 *  Created on: Sep 21, 2023
 *      Author: diegogilbert
 */

#ifndef PACKET_H_
#define PACKET_H_

typedef enum { IN_IN, IN_OUT, OUT_IN } Direction;
typedef enum { IGMP, TCP, UDP } Protocol;
typedef unsigned int Count;

typedef struct {
	long long timestamp;
	Direction direction;
	char sourceIP[16];
	char destIP[16];
	Protocol protocol;
	unsigned int port;
	Count bytes;
} Packet;

Packet* createPackets(int N) {
	Packet* packetArray = malloc(N * sizeof(Packet));
	for (int i = 0; i < N; i++) {
		packetArray[i].timestamp = rand();
		packetArray[i].direction = rand() % 3;
		sprintf(packetArray[i].sourceIP, "%d.%d.%d.%d", rand() % 256, rand() % 256, rand() % 256, rand() % 256);
		sprintf(packetArray[i].destIP, "%d.%d.%d.%d", rand() % 256, rand() % 256, rand() % 256, rand() % 256);
		packetArray[i].protocol = rand() % 3;
		packetArray[i].port = rand() % 65353;
		packetArray[i].bytes = rand() % 65536;
	}
	return packetArray;
}

#endif /* PACKET_H_ */
