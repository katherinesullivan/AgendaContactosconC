#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

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
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato);


#endif                          /* __SLIST_H__ */