/*
 * main.c
 *  Created on: 29/09/2023
 *
 *  Autores:
 *      Santiago López  744857
 *       -
 *       -
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "packet.h"

Direction countDirections(Packet *packets, int n, int *pInt, int *pInt1, int *pInt2);

int main() {

    int N = 100;
    Packet* packets = createPackets(N);
    int c1, c2, c3;

    Direction mostFrequentDirection = countDirections(packets, N, &c1, &c2, &c3);

    printf("IN_IN: %d\n", c1);
    printf("IN_OUT: %d\n", c2);
    printf("OUT_IN: %d\n", c3);
    printf("Most frequent direction: %s\n", (mostFrequentDirection == IN_IN) ? "IN_IN" : (mostFrequentDirection == IN_OUT) ? "IN_OUT" : "OUT-OUT");
}

Direction countDirections(Packet *packets, int n, int *pc1, int *pc2, int *pc3) {
    int c1 = 0, c2 = 0, c3 = 0;
    Direction mostFrequentDirection = IN_IN;

    for(int i=0; i<n; i++){
        if(packets->direction == IN_IN){
            c1++;
        }else if(packets->direction == IN_OUT){
            c2++;
        }
        else if(packets->direction == OUT_IN){
            c3++;
        }
        packets++;
    }

    if (c1 >= c2 && c1 >= c3) {
        mostFrequentDirection = IN_IN;
    } else if (c2 >= c1 && c2 >= c3) {
        mostFrequentDirection = IN_OUT;
    } else if (c3 >= c1 && c3 >= c2) {
        mostFrequentDirection = OUT_IN;
    }

    *pc1 = c1;
    *pc2 = c2;
    *pc3 = c3;

    return mostFrequentDirection;


}
