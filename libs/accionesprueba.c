#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acciones.h"

#define N 5
#define MAX_STR 32
#define MAX_NRO 10

// if elems is 0 no se puede hacer o deshacer mas
// agg los cambio que hace deshacer a rehacer
// y viceversa

int main() {
    AccList* deshacer = acciones_init(N);
    AccList* rehacer = acciones_init(N);

    for (int i = 0; i < 7; i++) {
        printf("Ingrese 1, 2 o 3\n>");
        char* tipo_char = malloc(sizeof(char)*MAX_NRO);
        fgets(tipo_char, MAX_NRO-1, stdin);
        int tipo = atoi(tipo_char);
        free(tipo_char);

        printf("Ingrese un nombre\n>");
        char* nombre = malloc(sizeof(char)*MAX_STR);
        fgets(nombre, MAX_STR-1, stdin);
        nombre[strlen(nombre)-1] = '\0';

        printf("Ingrese un apellido\n>");
        char* apellido = malloc(sizeof(char)*MAX_STR);
        fgets(apellido, MAX_STR-1, stdin);
        apellido[strlen(apellido)-1] = '\0';

        printf("Ingrese un telefono\n>");
        char* tel = malloc(sizeof(char)*MAX_STR);
        fgets(tel, MAX_STR-1, stdin);
        tel[strlen(tel)-1] = '\0';

        printf("Ingrese una edad\n>");
        char* edad_str = malloc(sizeof(char)*MAX_NRO);
        fgets(edad_str, MAX_NRO-1, stdin);
        int edad = atoi(edad_str);
        free(edad_str);

        char* nombre1 = malloc(sizeof(char)*MAX_STR);
        strcpy(nombre1,nombre);
        char* apellido1 = malloc(sizeof(char)*MAX_STR);
        strcpy(apellido1,apellido);
        char* tel1 = malloc(sizeof(char)*MAX_STR);
        strcpy(tel1,tel);

        acciones_agregar(deshacer, tipo, nombre, apellido, tel, edad);
        acciones_agregar(rehacer, tipo, nombre1, apellido1, tel1, edad);
    }

    char* prueba = malloc(sizeof(char)*5);
    strcpy(prueba,"99\n");
    int prueba_int = atoi(prueba);
    printf("Esto es la prueba: %d\n", prueba_int);
    free(prueba);

    printf("Deshacer:");
    imprimir_acciones(deshacer);

    printf("\nRehacer:");
    imprimir_acciones(rehacer);

    acciones_destruir(deshacer);
    acciones_destruir(rehacer);

    return 0;
}