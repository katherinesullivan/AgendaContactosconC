#include <stdlib.h>
#include <stdio.h>
#include "stree.h"

/**
 * Devuelve el mayor entre dos enteros
 */
int mayor(int a, int b) {
  return (a > b) ? a : b;
}

/**
 * Devuelve la altura de un STree
 */
int stree_alt(STree tree) {
  if (tree == NULL)
    return 0;
  return tree->alt;
}

/**
 * Devuelve el balance de un STree
 */
int stree_get_balance(STree tree) {
  if (tree == NULL)
    return 0;
  return stree_alt(tree->izq) - stree_alt(tree->der);
}

/**
 * Realiza una rotación a derecha
 */
STree stree_der_rotate(STree y) {
  STree x = y->izq;
  STree T2 = x->der;

  x->der = y;
  y->izq = T2;

  y->alt = mayor(stree_alt(y->izq), stree_alt(y->der)) + 1;
  x->alt = mayor(stree_alt(x->izq), stree_alt(x->der)) + 1;

  return x;
}

/**
 * Realiza una rotación a izquierda
 */
STree stree_izq_rotate(STree x) {
  STree y = x->der;
  STree T2 = y->izq;

  y->izq = x;
  x->der = T2;

  x->alt = mayor(stree_alt(x->izq), stree_alt(x->der)) + 1;
  y->alt = mayor(stree_alt(y->izq), stree_alt(y->der)) + 1;

  return y;
}

/**
 * En caso de ser necesario balancea un árbol
 */
STree stree_balancear(STree nodo, int balance) {
  // izq izq caso
  if (balance > 1 && stree_get_balance(nodo->izq) >= 0)
    return stree_der_rotate(nodo);

  // izq der caso
  if (balance > 1 && stree_get_balance(nodo->izq) < 0) {
    nodo->izq = stree_izq_rotate(nodo->izq);
    return stree_der_rotate(nodo);
  }
  // der der caso
  if (balance < -1 && stree_get_balance(nodo->der) <= 0)
    return stree_izq_rotate(nodo);

  // der izq caso
  if (balance < -1 && stree_get_balance(nodo->der) > 0) {
    nodo->der = stree_der_rotate(nodo->der);
    return stree_izq_rotate(nodo);
  }

  return nodo;
}

/**
 * Crea un STree vacío
 */
STree stree_crear() {
  return NULL;
}

/**
 * Destruye un STree
 */
void stree_destruir(STree tree) {
  if (tree != NULL) {
    stree_destruir(tree->izq);
    stree_destruir(tree->der);
    free(tree);
  }
}

/**
 * Crea un nuevo nodo
 */
STree stree_nuevo_nodo(int idx) {
  STree nuevo_nodo = malloc(sizeof(STNodo));

  nuevo_nodo->idx = idx;
  nuevo_nodo->izq = NULL;
  nuevo_nodo->der = NULL;
  nuevo_nodo->alt = 1;

  return nuevo_nodo;
}

/**
 * Inserta un nuevo elemento a un STree
 */
STree stree_insertar(STree tree, int idx) {
  if (tree == NULL)
    return (stree_nuevo_nodo(idx));

  if (idx < tree->idx)
    tree->izq = stree_insertar(tree->izq, idx);
  else if (idx > tree->idx)
    tree->der = stree_insertar(tree->der, idx);

  tree->alt = 1 + mayor(stree_alt(tree->izq), stree_alt(tree->der));
  int balance = stree_get_balance(tree);

  return stree_balancear(tree, balance);
}
