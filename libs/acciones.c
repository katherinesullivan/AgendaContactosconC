#include <stdlib.h>
#include <stdio.h>
#include "acciones.h"

AccList *acciones_init(int tamano) {
  AccList *acciones = malloc(sizeof(AccList));
  acciones->head = NULL;
  acciones->tail = NULL;
  acciones->elems = 0;
  acciones->cap = tamano;
  return acciones;
}

Accion *accion_nueva(int tipo, char *nombre, char *apellido, char *tel,
                     int edad) {
  Accion *accion = malloc(sizeof(Accion));
  accion->tipo = tipo;
  accion->nombre = nombre;
  accion->apellido = apellido;
  accion->tel = tel;
  accion->edad = edad;
  return accion;
}

void acciones_agregar(AccList * lista, int tipo, char *nombre, char *apellido,
                      char *tel, int edad) {
  if (lista->head == NULL) {
    lista->head = malloc(sizeof(AccNodo));
    lista->head->dato = accion_nueva(tipo, nombre, apellido, tel, edad);
    lista->head->ant = NULL;
    lista->head->sig = NULL;

    lista->tail = lista->head;
    lista->elems++;
    return;
  }

  if (lista->elems == lista->cap) {
    acciones_eliminar_incio(lista);
  }

  Accion *newaccion = accion_nueva(tipo, nombre, apellido, tel, edad);
  AccNodo *newnodo = malloc(sizeof(AccNodo));

  newnodo->dato = newaccion;
  newnodo->sig = NULL;
  printf("Hola1\n");
  AccNodo *extail = lista->tail;
  printf("Hola2\n");
  newnodo->ant = extail;
  printf("Hola3\n");
  if (extail == NULL)
    printf("Extail es NULL\n");
  extail->sig = newnodo;
  printf("Hola4\n");

  lista->tail = newnodo;
  printf("Hola5\n");
  lista->elems++;
}

void acciones_destruir(AccList * lista) {
  if (lista != NULL) {
    AccNodo *head = lista->head;
    while (head != NULL) {
      AccNodo *a_eliminar = head;
      head = a_eliminar->sig;
      accion_destruir(a_eliminar->dato);
      free(a_eliminar);
    }
    free(lista);
  }
}

void accion_destruir(Accion * accion) {
  free(accion->nombre);
  free(accion->apellido);
  free(accion->tel);
  free(accion);
}

void acciones_eliminar_incio(AccList * lista) {
  Accion *accion_a_eliminar = lista->head->dato;
  accion_destruir(accion_a_eliminar);

  AccNodo *exhead = lista->head;
  lista->head = exhead->sig;
  free(exhead);
  lista->elems--;
}

void acciones_eliminar_final(AccList * lista) {
  Accion *accion_a_eliminar = lista->tail->dato;
  accion_destruir(accion_a_eliminar);

  AccNodo *extail = lista->tail;
  lista->tail = extail->ant;
  free(extail);
  lista->elems--;
}

void imprimir_accion(Accion * acc) {
  printf("{%d: %s,%s,%s,%d}\n", acc->tipo, acc->nombre, acc->apellido, acc->tel,
         acc->edad);
}

void imprimir_acciones(AccList * lista) {
  if (lista != NULL) {
    printf("------------Lista: %d elems------------\n", lista->elems);
    AccNodo *head = lista->head;
    while (head != NULL) {
      imprimir_accion(head->dato);
      head = head->sig;
    }
  } else
    printf("--------Lista: NULL--------------\n");
}
