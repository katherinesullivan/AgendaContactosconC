#ifndef __ACCIONES_H__
#define __ACCIONES_H__

#include <stddef.h>

/* LIBRERÍA PARA LA IMPLEMENTACIÓN DE DESHACER Y REHACER */

/* ------ Estructuras ------ */

typedef struct {
  int tipo; // 1 agregar - 2 eliminar - 3 editar 
  char* nombre; 
  char* apellido; 
  char* tel;
  int edad;
} Accion;

typedef struct _AccNodo {
  Accion* dato;
  struct _AccNodo* sig;
  struct _AccNodo* ant;
} AccNodo;

typedef struct {
  AccNodo* head;
  AccNodo* tail;
  int elems; // indica la cantidad de elementos presentes
  int cap; // indica el N
} AccList;

/* ------ Inicialización ------ */

AccList* acciones_init(int tamano);

/* ------ Agregado ------ */

Accion* accion_nueva(int tipo, char* nombre, char* apellido, char* tel, int edad);

void acciones_agregar(AccList* lista, int tipo, char* nombre, char* apellido, char* tel, int edad);

/* ------ Destrucción ------ */

void acciones_destruir(AccList* lista);

void accion_destruir(Accion* accion);

/* ------ Eliminación ------ */

void acciones_eliminar_incio(AccList* lista);

void acciones_eliminar_final(AccList* lista);

/* ------ Impresión ------ */

void imprimir_accion(Accion* acc);

void imprimir_acciones(AccList* list);

#endif                          /* __ACCIONES_H__ */