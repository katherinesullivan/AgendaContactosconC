#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>
#include <limits.h>

/**
 * Estructura para listas simplemente enlazdas
 */
typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
  int cant;
} SNodo;

typedef SNodo *SList;

/**
 * Crea una lista simplemente enlazada
 */
SList slist_crear();

/**
 * Destruye una lista simplemente enlazada
 */
void slist_destruir(SList lista);

/**
 * Devuelve la cantidad de elementos de la lista
 */
int slist_cant(SList lista);

/**
 * Agrega un nodo con el dato pasado como parámetro al
 * inicio de una lista
 */
SList slist_agregar_inicio(SList lista, int dato);

/**
 * Setea la cantidad de una lista al máximo int
 */
SList slist_cant_max(SList lista);

/**
 * Imprime una lista simplemente enlazada
 */
void slist_imprimir(SList lista);

/**
 * Dadas 4 listas devuelve aquella cuya cantidad de 
 * elementos es más pequeña
 */
SList slist_mas_chica(SList lista1, SList lista2, SList lista3, SList lista4);


#endif                          /* __SLIST_H__ */
