#include "interprete.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NOMBRE 32
#define MAX_APELLIDO 32
#define MAX_CLAVE MAX_NOMBRE+MAX_APELLIDO

int interpretar(TablaHash ** dicc, int* accion) {
    printf("\n Seleccione una acción\n >");
    scanf("%d\n", accion);
    int nro_accion = *accion;

    switch (nro_accion) {

        /* Buscar */
        case 1:
            printf("Ingrese nombre:\n");
            char* nombre = malloc(sizeof(char)*MAX_NOMBRE);
            scanf("%s\n", nombre);
            printf("Ingrese apellido:\n");
            char* apellido = malloc(sizeof(char)*MAX_APELLIDO);
            scanf("%s\n", apellido);
            char* clave = malloc(sizeof(char)*MAX_CLAVE);
            sprintf(clave, "%s%s", nombre, apellido);
            Contacto contacto = tablahash_buscar(*dicc, clave, 0);
            if (contacto) contacto_imprimir(contacto);
            else printf("No existe contacto con tal nombre y apellido\n");
            free(nombre);
            free(apellido);
            free(clave);
            return 1;
            

    }

