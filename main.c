/*
 * main.c
 *  Created on: 29/09/2023
 *
 *  Autores:
 *      Santiago LÃ³pez  744857
 *      Ricardo Soberanis 745306
 *      Isaac Vasquez 745369
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "packet.h"

Direction countDirections(Packet *packets, int n, int *pInt, int *pInt1, int *pInt2);

int compareBytes(Packet* p1, Packet* p2);

int compareIP(Packet* p1, Packet* p2);

void insertionSort(Packet* packets, int N, CompareFunc compare1, CompareFunc compare2);

void insertionSort1(Packet* packets, int N, CompareFunc compare1, CompareFunc compare2);

//Reto 3. Define un tipo de dato CompareFunc
typedef int (*CompareFunc)(Packet*, Packet*);

int main() {

    //Reto 2. Crea un arreglo de (al menos) ocho paquetes con datos diversos pero vÃ¡lidos.
    //Invoca al mÃ©todo anterior. Comprueba que los conteos efectuados y la direcciÃ³n devuelta son correctos. 
    int N = 100;
    Packet* packets = createPackets(N);
    int c1, c2, c3;

    Direction mostFrequentDirection = countDirections(packets, N, &c1, &c2, &c3);

    printf("IN_IN: %d\n", c1);
    printf("IN_OUT: %d\n", c2);
    printf("OUT_IN: %d\n", c3);
    printf("Most frequent direction: %s\n", (mostFrequentDirection == IN_IN) ? "IN_IN" : (mostFrequentDirection == IN_OUT) ? "IN_OUT" : "OUT-OUT");

    //Reto 3
    
    Packet packet1 = {100, "192.168.1.1"};
    Packet packet2 = {50, "192.168.1.2"};


    CompareFunc funcPtr;

    funcPtr = compareBytes;

    int result = funcPtr(&packet1, &packet2);
    printf("ComparaciÃ³n por bytes: %d\n", result);

    funcPtr = compareIP;

    result = funcPtr(&packet1, &packet2);
    printf("ComparaciÃ³n por IP: %d\n", result);
}

//Reto 1. Implementa una funciÃ³n llamada countDirections
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

//Reto 3. Define un tipo de dato CompareFunc que se pueda asignar a un apuntador a una funciÃ³n como cualquiera de las siguientes:

int compareBytes(Packet* p1, Packet* p2) {
    return p1->bytes - p2->bytes;
}

int compareIP(Packet* p1, Packet* p2) {
    return strcmp(p1->sourceIP, p2->sourceIP);
}

//Reto 4. Implementa una funciÃ³n llamada insertionSort
void insertionSort(Packet* packets, int N, CompareFunc compare1, CompareFunc compare2) {
    int i, j;
    Packet key;
    for (i = 1; i < N; i++) {
        key = packets[i];
        j = i - 1;

        // Mientras j >= 0 y la comparaciÃ³n entre packets[j] y key es > 0
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

//Reto 5. Implementa una funciÃ³n llamada insertionSort1 que haga exactamente lo mismo que la funciÃ³n anterior, pero en esta versiÃ³n no se podrÃ¡n utilizar â€œcorchetesâ€, sÃ³lo aritmÃ©tica de apuntadores
// Aunque no se usen corchetes, los contadores o Ã­ndices sÃ­ serÃ¡n necesarios.
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