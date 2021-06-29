#ifndef __STREE_H__
#define __STREE_H__

#include <stddef.h>
#include "slist.h"

typedef struct _STNodo {
  int idx;                      // Índice en donde se encuentra el contacto
  struct _STNodo *izq;          // Subárbol izquierdo
  struct _STNodo *der;          // Subárbol derecho
  int alt;
} STNodo;

typedef STNodo *STree;

int mayor(int a, int b);

int stree_alt(STree tree);

int stree_get_balance(STree N);

STree stree_der_rotate(STree y);

STree stree_izq_rotate(STree x);

STree stree_balancear(STree nodo, int balance);

STree stree_crear();

void stree_destruir(STree tree);

STree stree_nuevo_nodo(int idx);

STree stree_insertar(STree tree, int idx);

//void stree_imprimir(TablaHash* agenda, STree tree);

#endif                          /* __STREE_H__ */
