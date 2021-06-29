#ifndef __ACCIONES_H__
#define __ACCIONES_H__

#include <stddef.h>

/* LIBRERÍA PARA LA IMPLEMENTACIÓN DE DESHACER Y REHACER */

/* ------ Estructuras ------ */

typedef struct {
  int tipo;                     // 1 agregar - 2 eliminar - 3 editar 
  char *nombre;
  char *apellido;
  char **tel;
  int *edad;
} Accion;

typedef struct _AccNodo {
  Accion *dato;
  struct _AccNodo *sig;
  struct _AccNodo *ant;
} AccNodo;

typedef struct {
  AccNodo *head;
  AccNodo *tail;
  int elems;                    // indica la cantidad de elementos presentes
  int cap;                      // indica el N
} AccList;

/**
 * Inicializa una lista de acciones
 */
AccList *acciones_init(int tamano);

/**
 * Crea una acción
 */
Accion *accion_nueva(int tipo, char *nombre, char *apellido, char *tel1,
                     char *tel2, int edad1, int edad2);

/**
 * Crea una acción y la agrega al final de una lista
 */
void acciones_agregar(AccList * lista, int tipo, char *nombre, char *apellido,
                      char *tel1, char *tel2, int edad1, int edad2);

/**
 * Elimina todas las acciones de la lista pero dejándola inicializada
 */
void acciones_reestablecer(AccList * lista);

/**
 * Destruye una lista de acciones
 */
void acciones_destruir(AccList * lista);

/**
 * Destruye una acción
 */
void accion_destruir(Accion * accion);

/**
 * Elimina la primer acción de una lista
 */
void acciones_eliminar_incio(AccList * lista);

/**
 * Elimina la última acción de una lista
 */
void acciones_eliminar_final(AccList * lista);

/**
 * Agrega la acción opuesta a la pasada como argumento a la
 * lista pasada como argumento
 */
void agregar_opuesto_des_re(Accion * accion, AccList * acclist);

/* ------ Funciones de utilidad ------ */

/**
 * Imprime una lista de acciones
 */
void imprimir_accion(Accion * acc);

/**
 * Imprime una lista de acciones
 */
void imprimir_acciones(AccList * list);

#endif                          /* __ACCIONES_H__ */
