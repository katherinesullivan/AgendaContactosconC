#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>
#include <limits.h>

typedef struct _SNodo {
  int dato;
  struct _SNodo* sig;
  int cant;
} SNodo;

typedef SNodo* SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Devuelve la cantidad de elementos de una lista.
 */
int slist_cant(SList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato);

SList slist_cant_max(SList lista);

/**
 * Imprime la lista.
 */
void slist_imprimir(SList lista);

/**
 * Devuelve la lista con menos elementos entre las 4 pasadas.
 */
SList slist_mas_chica(SList lista1, SList lista2, SList lista3, SList lista4);


#endif                          /* __SLIST_H__ */