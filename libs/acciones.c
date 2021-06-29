#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "acciones.h"

#define MAX_NOMBRE 32
#define MAX_APELLIDO 32
#define MAX_TEL 32

AccList *acciones_init(int tamano) {
  AccList *acciones = malloc(sizeof(AccList));
  acciones->head = NULL;
  acciones->tail = NULL;
  acciones->elems = 0;
  acciones->cap = tamano;
  return acciones;
}

Accion *accion_nueva(int tipo, char *nombre, char *apellido, char *tel1, char* tel2, int edad1, int edad2) {
  Accion *accion = malloc(sizeof(Accion));
  accion->tipo = tipo;
  accion->nombre = nombre;
  accion->apellido = apellido;
  accion->tel = malloc(sizeof(char*)*2);
  accion->tel[0] = tel1;
  accion->tel[1] = tel2;
  accion->edad = malloc(sizeof(int)*2);
  accion->edad[0] = edad1;
  accion->edad[1] = edad2;
  return accion;
}

void acciones_agregar(AccList * lista, int tipo, char *nombre, char *apellido, char *tel1, char* tel2, int edad1, int edad2) {
  if (lista->head == NULL) {
    lista->head = malloc(sizeof(AccNodo));
    lista->head->dato = accion_nueva(tipo, nombre, apellido, tel1, tel2, edad1, edad2);
    lista->head->ant = NULL;
    lista->head->sig = NULL;

    lista->tail = lista->head;
    lista->elems++;
    return;
  }

  if (lista->elems == lista->cap) {
    acciones_eliminar_incio(lista);
  }

  Accion *newaccion = accion_nueva(tipo, nombre, apellido, tel1, tel2, edad1, edad2);
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

void acciones_reestablecer(AccList * lista) {
  if (lista != NULL) {
    int cap = lista->cap;
    AccNodo *head = lista->head;
    while (head != NULL) {
      AccNodo *a_eliminar = head;
      head = a_eliminar->sig;
      accion_destruir(a_eliminar->dato);
      free(a_eliminar);
    }
    lista->head = NULL;
    lista->tail = NULL;
    lista->elems = 0;
    lista->cap = cap;
  }
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
  free(accion->edad);
  free(accion->tel[0]);
  free(accion->tel[1]);
  free(accion->tel);
  free(accion);
}

void acciones_eliminar_incio(AccList * lista) {
  if (lista == NULL) return;
  if (lista->head != NULL) {
    Accion *accion_a_eliminar = lista->head->dato;
    accion_destruir(accion_a_eliminar);

    AccNodo *exhead = lista->head;
    lista->head = exhead->sig;
    lista->head->ant = NULL;
    free(exhead);
    lista->elems--;
  }
}

void acciones_eliminar_final(AccList * lista) {
  if (lista == NULL) return;
  if (lista->head != NULL) {
    if (lista->elems == 1) lista->head = NULL;
    Accion *accion_a_eliminar = lista->tail->dato;
    accion_destruir(accion_a_eliminar);

    AccNodo *extail = lista->tail;
    if (extail->ant == NULL) printf("Nueva tail NULL");
    else {
      printf("Nueva lista tail: ");
      imprimir_accion(extail->ant->dato);
    }
    lista->tail = extail->ant;
    if (lista->tail) lista->tail->sig = NULL;
    free(extail);
    lista->elems--;
  }
}

void agregar_opuesto_des_re(Accion* accion, AccList* acclist) {
  char* nombre_add = malloc(sizeof(char) * MAX_NOMBRE);
  strcpy(nombre_add, accion->nombre);
  char* apellido_add = malloc(sizeof(char) * MAX_APELLIDO);
  strcpy(apellido_add, accion->apellido);
  char* tel_add = malloc(sizeof(char) * MAX_TEL);
  strcpy(tel_add, accion->tel[0]);
  int edad_add = accion->edad[0];

  if (accion->tipo == 1) acciones_agregar(acclist, 2, nombre_add, apellido_add, tel_add, NULL, edad_add, 0);

  else if (accion->tipo == 2) acciones_agregar(acclist, 1, nombre_add, apellido_add, tel_add, NULL, edad_add, 0);

  else if (accion->tipo == 3) {
    char* tel_add2 = malloc(sizeof(char)*MAX_TEL);
    strcpy(tel_add2, accion->tel[1]);
    int edad_add2 = accion->edad[1];
    // Cambiamos de orden las edades y los telefonos para siempre sacar los del principio
    acciones_agregar(acclist, 3, nombre_add, apellido_add, tel_add2, tel_add, edad_add2, edad_add);
  }
}

void imprimir_accion(Accion * acc) {
  printf("{%d: %s,%s,tels:%s,%s,edades:%d,%d}\n", acc->tipo, acc->nombre, acc->apellido, acc->tel[0], acc->tel[1] ,acc->edad[0], acc->edad[1]);
}

void imprimir_acciones(AccList * lista) {
  if (lista != NULL) {
    printf("------------Lista: %d elems------------\n", lista->elems);
    if (lista->head != NULL) {
      AccNodo *head = lista->head;
      while (head != NULL) {
        imprimir_accion(head->dato);
        head = head->sig;
      }
    }
  } else
    printf("--------Lista: NULL--------------\n");
}
