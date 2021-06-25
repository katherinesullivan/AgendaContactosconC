#include "slist.h"
#include <stdlib.h>
#include <stdio.h>

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista) {
  SList nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_cant(SList lista) {
  if (lista == NULL) return 0;
  return lista->cant;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SList nuevo_nodo = malloc(sizeof(SNodo));
  nuevo_nodo->dato = dato;
  nuevo_nodo->sig = lista;
  nuevo_nodo->cant = slist_cant(lista)+1;
  return nuevo_nodo;
}

void slist_imprimir(SList lista) {
  if (lista != NULL) {
    SList nodo = lista;
    printf("--------SLIST: %d elementos----------\n", lista->cant);
    while(nodo != NULL) {
      printf("%d\n", nodo->dato);
      nodo = lista->sig;
    }
  }
  else printf("--------SLIST: 0 elementos----------\n");
}