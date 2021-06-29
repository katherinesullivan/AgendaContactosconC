#include "andor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>

#define MAX_STR 32
#define N 3

Argumento* argumento_crear(Arbol arbol, int tipo, SList* lista, void* dato) {
    Argumento* arg = malloc(sizeof(Argumento));
    arg->arbol = arbol;
    arg->tipo = tipo;
    arg->lista = lista;
    arg->dato = dato;
    return arg;
}

void* rutina(void* arg) {
    Argumento* arg1 = (Argumento*)arg;
    arbol_buscar(arg1->arbol, arg1->lista, arg1->dato, arg1->tipo, 0);
}

void and_function(Arbol arbol_edad, Arbol arbol_nombre, Arbol arbol_apellido, Arbol arbol_tel, int func) {
    int nombre_band = 0;
    int apellido_band = 0;
    int tel_band = 0;
    int edad_band = 0;

    char* nombre = malloc(sizeof(char)*MAX_STR);
    printf("Seleccione un nombre a buscar\n>");
    fgets(nombre, MAX_STR-1, stdin);
    nombre[strlen(nombre)-1] = '\0';
    if (strcmp(nombre, "") != 0) {
        nombre_band = 1;
    }

    char* apellido = malloc(sizeof(char)*MAX_STR);
    printf("Seleccione un apellido a buscar\n>");
    fgets(apellido, MAX_STR-1, stdin);
    apellido[strlen(apellido)-1] = '\0';
    if (strcmp(apellido, "") != 0) {
        apellido_band = 1;
    }

    char* edad_str = malloc(sizeof(char)*10);
    printf("Seleccione una edad a buscar\n>");
    fgets(edad_str, 10-1, stdin);
    if (strcmp(edad_str, "") != 0) {
        edad_band = 1;
    }
    int* edad_pointer = malloc(sizeof(int));
    *edad_pointer = atoi(edad_str);
    if (!edad_band) {
        free(edad_pointer);
    }
    free(edad_str);

    char* tel = malloc(sizeof(char)*MAX_STR);
    printf("Seleccione un teléfono a buscar\n>");
    fgets(tel, MAX_STR-1, stdin);
    tel[strlen(tel)-1] = '\0';
    if (strcmp(tel, "") != 0) {
        tel_band = 1;
    }


    // Como se realizan en paralelo creo todas las listas 
    pthread_t hilos[4];

    SList lista_nombre = slist_crear();
    Argumento* argumento_nombre = argumento_crear(arbol_nombre, 1, &lista_nombre, nombre);
    assert(! pthread_create(&hilos[0], NULL, rutina, (void*)argumento_nombre));

    SList lista_apellido = slist_crear();
    Argumento* argumento_apellido = argumento_crear(arbol_apellido, 1, &lista_apellido, apellido);
    assert(! pthread_create(&hilos[1], NULL, rutina, (void*)argumento_apellido));

    SList lista_edad = slist_crear();
    Argumento* argumento_edad = argumento_crear(arbol_edad, 2, &lista_edad, edad_pointer); 
    assert(! pthread_create(&hilos[2], NULL, rutina, (void*)argumento_edad));

    SList lista_tel = slist_crear();
    Argumento* argumento_tel = argumento_crear(arbol_tel, 1, &lista_tel, tel);
    assert(! pthread_create(&hilos[3], NULL, rutina, (void*)argumento_tel));

    for (int i = 0; i < 4; i++) {
        assert(! pthread_join(hilos[i], NULL));
    }
    free(argumento_nombre);
    free(argumento_apellido);
    free(argumento_edad);
    free(argumento_tel);

    // Funcion and
    if (func == 1) {
        if (!nombre_band) {
            lista_nombre = slist_cant_max(lista_nombre);
        }

        if (!apellido_band) {
            lista_apellido = slist_cant_max(lista_apellido);
        }

        if (!edad_band) {
            lista_edad = slist_cant_max(lista_edad);
        }

        if (!tel_band) {
            lista_tel = slist_cant_max(lista_tel);
        }

        SList lista_comparar = slist_mas_chica(lista_nombre, lista_apellido, lista_edad, lista_tel);

        int* bands = malloc(sizeof(int)*4);
        bands[0] = nombre_band;
        bands[1] = apellido_band;
        bands[2] = edad_band;
        bands[3] = tel_band;

        int edad = *edad_pointer;

        //imprimir_datos_correctos(bands, lista_comparar, nombre, apellido, edad, tel);
        free(bands);

        printf("Lista nombre:");
        slist_imprimir(lista_nombre);

        printf("Lista apellido:");
        slist_imprimir(lista_apellido);

        printf("Lista edad:");
        slist_imprimir(lista_edad);

        printf("Lista tel:");
        slist_imprimir(lista_tel);


        slist_imprimir(lista_comparar);
    }

    // Función or
    if (func == 2) {
        STree tree = stree_crear();
        SList iter = lista_nombre;
        while (iter != NULL) {
            tree = stree_insertar(tree, iter->dato);
            iter = iter->sig;
        }
        iter = lista_apellido;
        while (iter != NULL) {
            tree = stree_insertar(tree, iter->dato);
            iter = iter->sig;
        }
        iter = lista_edad;
        while (iter != NULL) {
            tree = stree_insertar(tree, iter->dato);
            iter = iter->sig;
        }
        iter = lista_tel;
        while (iter != NULL) {
            tree = stree_insertar(tree, iter->dato);
            iter = iter->sig;
        }
        stree_imprimir(tree);
        stree_destruir(tree);
    }

    slist_destruir(lista_nombre);
    slist_destruir(lista_apellido);
    slist_destruir(lista_edad);
    slist_destruir(lista_tel);

    free(nombre);
    free(apellido);
    free(tel);
    free(edad_pointer);

    /*SList lista = slist_crear();
    int nro = 1;
    arbol_buscar(arbol, &lista, &nro, 2, 0);
    slist_imprimir(lista);*/
}

int main () {
    Arbol arbol_edad = arbol_crear();
    for (int i = 0; i < N; i++) {
        printf("Ingrese una edad:\n>");
        char* str1 = malloc(sizeof(char)*10);
        fgets(str1, 9, stdin);
        int dato1 = atoi(str1);
        int* dato1_pointer = malloc(sizeof(int));
        dato1_pointer[0] = dato1;
        arbol_edad = arbol_insertar(arbol_edad, dato1_pointer, i, 2);
        free(str1);
    }
    arbol_imprimir_inorder(arbol_edad, 2);

    Arbol arbol_nombre = arbol_crear();
    for (int i = 0; i < N; i++) {
        printf("Ingrese un nombre:\n>");
        char* str1 = malloc(sizeof(char)*MAX_STR);
        fgets(str1, MAX_STR-1, stdin);
        str1[strlen(str1)-1] = '\0';
        arbol_nombre = arbol_insertar(arbol_nombre, str1, i, 1);
    }
    arbol_imprimir_inorder(arbol_nombre, 1);

    Arbol arbol_apellido = arbol_crear();
    for (int i = 0; i < N; i++) {
        printf("Ingrese un apellido:\n>");
        char* str1 = malloc(sizeof(char)*MAX_STR);
        fgets(str1, MAX_STR-1, stdin);
        str1[strlen(str1)-1] = '\0';
        arbol_apellido = arbol_insertar(arbol_apellido, str1, i, 1);
    }
    arbol_imprimir_inorder(arbol_apellido, 1);

    Arbol arbol_tel = arbol_crear();
    for (int i = 0; i < N; i++) {
        printf("Ingrese un teléfono:\n>");
        char* str1 = malloc(sizeof(char)*MAX_STR);
        fgets(str1, MAX_STR-1, stdin);
        str1[strlen(str1)-1] = '\0';
        arbol_tel = arbol_insertar(arbol_tel, str1, i, 1);
    }
    arbol_imprimir_inorder(arbol_tel, 1);

    printf("Elija 1=and 2=or\n>");
    char* opcion = malloc(sizeof(char)*7);
    fgets(opcion, 6, stdin);
    int op_int = atoi(opcion);
    free(opcion);

    if (op_int == 1) {
        and_function(arbol_edad, arbol_nombre, arbol_apellido, arbol_tel, 1);
    }

    else if (op_int == 2) {
        and_function(arbol_edad, arbol_nombre, arbol_apellido, arbol_tel, 2);
    }

    else printf("Opcion desconocida\n");

    arbol_destruir(arbol_nombre, 1);
    arbol_destruir(arbol_apellido, 1);
    arbol_destruir(arbol_edad, 2);
    arbol_destruir(arbol_tel, 1);

    return 0;
}
