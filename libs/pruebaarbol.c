#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_NOMBRE 32

int main () {
    Arbol arbol = arbol_crear();
    for (int i = 0; i < 12; i++) {
        printf("Ingrese una edad:\n>");
        char* str1 = malloc(sizeof(char)*10);
        fgets(str1, 9, stdin);
        int dato1 = atoi(str1);
        int* dato1_pointer = malloc(sizeof(int));
        dato1_pointer[0] = dato1;
        arbol = arbol_insertar(arbol, dato1_pointer, i, 2);
        free(str1);
    }
    char* str = malloc(sizeof(char)*10);
    printf("Ingrese una edad a eliminar\n");
    fgets(str, 9, stdin);
    int* dato = malloc(sizeof(int));
    dato[0] = atoi(str);
    arbol = arbol_eliminar(arbol, dato, 3, 2);
    free(str);
    free(dato);
    arbol_imprimir_inorder(arbol, 2);
    arbol_destruir(arbol);
    return 0;
}

// Acordarse de pedir memoria para guardar las edad así despues tiene sentido el liberarlas.