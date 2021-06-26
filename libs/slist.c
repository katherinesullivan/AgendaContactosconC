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

SList slist_cant_max(SList lista) {
  SList nuevo_nodo = malloc(sizeof(SNodo));
  nuevo_nodo->dato = 0;
  nuevo_nodo->sig = lista;
  nuevo_nodo->cant = INT_MAX;
}

void slist_imprimir(SList lista) {
  printf("--------SLIST:%d------------\n",slist_cant(lista));
  if (lista != NULL) {
    SList nodo = lista;
    while(nodo != NULL) {
      printf("%d\n", nodo->dato);
      nodo = nodo->sig;
    }
  }
}

SList slist_mas_chica(SList lista1, SList lista2, SList lista3, SList lista4) {
  int cant1 = slist_cant(lista1);
  int cant2 = slist_cant(lista2);
  int cant3 = slist_cant(lista3);
  int cant4 = slist_cant(lista4);
  if (cant1 < cant2){
    if (cant1 < cant3){
      return (cant1 < cant4 ? lista1 : lista4);
    }
    else {
      return (cant3 < cant4 ? lista3 : lista4);
    }
  }
  else {
    if (cant2 < cant3) {
      return (cant2 < cant4 ? lista2 : lista4);
    }
    else {
      return (cant3 < cant4 ? lista3 : lista4);
    }
  }
}

/*int main() {
  SList lista1 = slist_crear();
  SList lista2 = slist_crear();
  SList lista3 = slist_crear();
  SList lista4 = slist_crear();
  slist_agregar_inicio(lista1, 1);
  slist_agregar_inicio(lista1, 1);
  slist_agregar_inicio(lista1, 1);
  slist_agregar_inicio(lista2, 1);
  slist_agregar_inicio(lista2, 1);
  slist_agregar_inicio(lista3, 1);
  slist_imprimir(slist_mas_chica(lista4, lista1, lista2, lista3));
  return 0;
}*/