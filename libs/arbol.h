#ifndef __ARBOL_H__
#define __ARBOL_H__

#include <stddef.h>
#include "slist.h"

typedef struct _Nodo{
    void* dato; // Dato de contacto sobre el cual aplicará la func comparadora
    int idx; // Índice en donde se encuentra el contacto
    struct _Nodo *izq; // Subárbol izquierdo
    struct _Nodo *der; // Subárbol derecho
    int alt;
} Nodo;

typedef Nodo* Arbol;

Arbol arbol_crear();

Arbol arbol_destruir(Arbol arbol);

int max(int a, int b);

int altura(Arbol arbol);

Arbol nuevo_nodo(void* dato, int idx);

Arbol der_rotate(Arbol y);

Arbol izq_rotate(Arbol x);

Arbol balancear (Arbol nodo, int balance);

int get_balance(Arbol N);

Arbol arbol_insertar(Arbol nodo, void* dato, int idx, int tipo_arbol);

Arbol min_value_nodo(Arbol nodo);

Arbol arbol_eliminar(Arbol nodo, void* dato, int idx, int tipo_arbol);

void arbol_imprimir_inorder(Arbol arbol, int tipo_de_arbol);

/**
 * Busca en el arbol y agrega a una lista simplemente enlazada todos aquellos
 * nodos que contengan la clave pasada como parámetro.
 * El argumento found es 1 si ya se encontro al menos un elemento con la clave
 * dada. Esto permite terminar la búsqueda más rápido, pues si ya encontré 
 * un nodo con la clave dada y luego fue a izquierda o derecha y no encontré
 * otro nodo con la clave dada puedo dejar de buscar.
*/
void arbol_buscar(Arbol arbol, SList* lista, void* dato, int tipo_arbol, int found);

#endif                          /* __ARBOL_H__ */