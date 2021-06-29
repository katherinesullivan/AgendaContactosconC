#include "slist.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Crea una lista simplemente enlazada
 */
SList slist_crear() {
  return NULL;
}

/**
 * Destruye una lista simplemente enlazada
 */
void slist_destruir(SList lista) {
  SList nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

/**
 * Devuelve la cantidad de elementos de la lista
 */
int slist_cant(SList lista) {
  if (lista == NULL)
    return 0;
  return lista->cant;
}

/**
 * Agrega un nodo con el dato pasado como parámetro al
 * inicio de una lista
 */
SList slist_agregar_inicio(SList lista, int dato) {
  SList nuevo_nodo = malloc(sizeof(SNodo));
  nuevo_nodo->dato = dato;
  nuevo_nodo->sig = lista;
  nuevo_nodo->cant = slist_cant(lista) + 1;
  return nuevo_nodo;
}

/**
 * Setea la cantidad de una lista al máximo int
 */
SList slist_cant_max(SList lista) {
  SList nuevo_nodo = malloc(sizeof(SNodo));
  nuevo_nodo->dato = 0;
  nuevo_nodo->sig = lista;
  nuevo_nodo->cant = INT_MAX;
  return nuevo_nodo;
}

/**
 * Imprime una lista simplemente enlazada
 */
void slist_imprimir(SList lista) {
  printf("--------SLIST:%d------------\n", slist_cant(lista));
  if (lista != NULL) {
    SList nodo = lista;
    while (nodo != NULL) {
      printf("%d\n", nodo->dato);
      nodo = nodo->sig;
    }
  }
}

/**
 * Dadas 4 listas devuelve aquella cuya cantidad es más pequeña
 */
SList slist_mas_chica(SList lista1, SList lista2, SList lista3, SList lista4) {
  int cant1 = slist_cant(lista1);
  int cant2 = slist_cant(lista2);
  int cant3 = slist_cant(lista3);
  int cant4 = slist_cant(lista4);
  if (cant1 < cant2) {
    if (cant1 < cant3) {
      return (cant1 < cant4 ? lista1 : lista4);
    } else {
      return (cant3 < cant4 ? lista3 : lista4);
    }
  } else {
    if (cant2 < cant3) {
      return (cant2 < cant4 ? lista2 : lista4);
    } else {
      return (cant3 < cant4 ? lista3 : lista4);
    }
  }
}
