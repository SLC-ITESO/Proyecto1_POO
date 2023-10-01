#include "packet.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Packet* createPackets(int N) {
    Packet* packetArray = (Packet*) malloc(N * sizeof(Packet));
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

Direction countDirections(Packet* packets, int N, int* c1, int* c2, int* c3) {
    *c1 = 0;
    *c2 = 0;
    *c3 = 0;

    for(int i = 0; i < N; i++) {
        switch((packets+i)->direction) {
            case IN_IN:
                (*c1)++;
                break;
            case IN_OUT:
                (*c2)++;
                break;
            case OUT_IN:
                (*c3)++;
                break;
        }
    }

    // Devolver la dirección con mayor frecuencia
    if (*c1 >= *c2 && *c1 >= *c3) {
        return IN_IN;
    } else if (*c2 >= *c1 && *c2 >= *c3) {
        return IN_OUT;
    } else {
        return OUT_IN;
    }
}

int compareBytes(Packet* p1, Packet* p2) {
    return p1->bytes - p2->bytes;
}

int compareIP(Packet* p1, Packet* p2) {
    return strcmp(p1->sourceIP, p2->sourceIP);
}

void insertionSort(Packet* packets, int N, CompareFunc compare1, CompareFunc compare2) {
    int i, j;
    Packet key;
    for (i = 1; i < N; i++) {
        key = packets[i];
        j = i - 1;

        // Mientras j >= 0 y la comparación entre packets[j] y key es > 0
        while (j >= 0 && compare1(&packets[j], &key) > 0) {
            packets[j + 1] = packets[j];
            j = j - 1;
        }

        // Si hay un empate en compare1, usar compare2
        while (j >= 0 && compare1(&packets[j], &key) == 0 && compare2(&packets[j], &key) > 0) {
            packets[j + 1] = packets[j];
            j = j - 1;
        }

        packets[j + 1] = key;
    }
}

void swap(Packet *a, Packet *b) {
    Packet temp = *a;
    *a = *b;
    *b = temp;
}

void insertionSort1(Packet *packets, int N, CompareFunc compare1, CompareFunc compare2) {
    Packet *end = packets + N;
    for (Packet *i = packets + 1; i < end; i++) {
        Packet *j = i;
        Packet key = *i;
        while (j > packets && (compare1(j - 1, &key) > 0 || (compare1(j - 1, &key) == 0 && compare2(j - 1, &key) > 0))) {
            *j = *(j - 1);
            j--;
        }
        *j = key;
    }
}
