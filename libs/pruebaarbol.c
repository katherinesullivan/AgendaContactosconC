#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_NOMBRE 32

int main () {
    Arbol arbol = arbol_crear();
    for (int i = 0; i < 5; i++) {
        printf("Ingrese un nombre:\n>");
        char* str1 = malloc (sizeof(char)*MAX_NOMBRE);
        fgets(str1, MAX_NOMBRE-1, stdin);
        arbol = arbol_insertar(arbol, str1, i, 1);
    }
    char* str = malloc (sizeof(char)*MAX_NOMBRE);
    printf("Ingrese un nombre a eliminar\n");
    fgets(str, MAX_NOMBRE-1, stdin);
    arbol = arbol_eliminar(arbol, str, 0, 1);
    free(str);
    arbol_imprimir_inorder(arbol, 1);
    arbol_destruir(arbol);
    return 0;
}

// Acordarse de pedir memoria para guardar las edad así despues tiene sentido el liberarlas.