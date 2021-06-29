#ifndef __STREE_H__
#define __STREE_H__

#include <stddef.h>
#include "slist.h"

/**
 * Estructura para STree
 */
typedef struct _STNodo {
  int idx;                      // Índice en donde se encuentra el contacto
  struct _STNodo *izq;          // Subárbol izquierdo
  struct _STNodo *der;          // Subárbol derecho
  int alt;
} STNodo;

typedef STNodo *STree;

/**
 * Devuelve el mayor entre dos enteros
 */
int mayor(int a, int b);

/**
 * Devuelve la altura de un STree
 */
int stree_alt(STree tree);

/**
 * Devuelve el balance de un STree
 */
int stree_get_balance(STree N);

/**
 * Realiza una rotación a derecha
 */
STree stree_der_rotate(STree y);

/**
 * Realiza una rotación a izquierda
 */
STree stree_izq_rotate(STree x);

/**
 * En caso de ser necesario balancea un árbol
 */
STree stree_balancear(STree nodo, int balance);

/**
 * Crea un STree vacío
 */
STree stree_crear();

/**
 * Destruye un STree
 */
void stree_destruir(STree tree);

/**
 * Crea un nuevo nodo
 */
STree stree_nuevo_nodo(int idx);

/**
 * Inserta un nuevo elemento a un STree
 */
STree stree_insertar(STree tree, int idx);

#endif                          /* __STREE_H__ */
