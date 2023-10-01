#include <stdio.h>
#include <stdlib.h>
#include "packet.h"
#include <string.h>

int main() {
    // Crear un array de 8 paquetes
    int N = 8;
    Packet* packets = createPackets(N);

    // Asignar algunos valores de dirección manualmente para la prueba
    packets[0].direction = IN_IN;
    packets[1].direction = IN_OUT;
    packets[2].direction = OUT_IN;
    packets[3].direction = IN_IN;
    packets[4].direction = IN_OUT;
    packets[5].direction = OUT_IN;
    packets[6].direction = IN_IN;
    packets[7].direction = OUT_IN;

    // Contadores para cada dirección
    int c1, c2, c3;

    // Llamar a la función countDirections
    Direction mostFrequentDirection = countDirections(packets, N, &c1, &c2, &c3);

    // Imprimir los resultados
    printf("Conteo de IN_IN: %d\n", c1);
    printf("Conteo de IN_OUT: %d\n", c2);
    printf("Conteo de OUT_IN: %d\n", c3);
    printf("Direccion mas frecuente: ");
    
    switch(mostFrequentDirection) {
        case IN_IN:
            printf("IN_IN\n");
            break;
        case IN_OUT:
            printf("IN_OUT\n");
            break;
        case OUT_IN:
            printf("OUT_IN\n");
            break;
    }

    // Liberar la memoria del array de paquetes
    free(packets);

    return 0;
}
