#ifndef __STREE_H__
#define __STREE_H__

#include <stddef.h>
#include "slist.h"

typedef struct _STNodo{
    int idx; // Índice en donde se encuentra el contacto
    struct _STNodo *izq; // Subárbol izquierdo
    struct _STNodo *der; // Subárbol derecho
} STNodo;

typedef STNodo* STree;

STree stree_crear();

void stree_destruir(STree tree);

STree stree_nuevo_nodo(int idx);

STree stree_insertar(STree tree, int idx);

void stree_imprimir(STree tree);

#endif                          /* __STREE_H__ */