#ifndef __ANDOR_H__
#define __ANDOR_H__

#include <stddef.h>
#include "stree.h"
#include "tablahash.h"

/**
 * Estructura para el argumento a pasarle a la rutina 
 */
typedef struct {
  Arbol arbol;
  int tipo;
  SList *lista;
  void *dato;
} Argumento;

/**
 * Crea un argumento para pasarle a la rutina 
 */
Argumento *argumento_crear(Arbol arbol, int tipo, SList * lista, void *dato);

/**
 * Rutina para los hilos. Busca los datos en el árbol
 * y los añade a la lista
 */
void *rutina(void *arg);

/**
 * Función principal del módulo.
 * Busca en paralelo los datos pasados en los árboles de la agenda y
 * luego en base a si está siendo llamada por and o or llama a las
 * funciones que mostrarán los datos por pantalla.
 */
void andor(TablaHash ** agenda, int *bands, char *nombre, char *apellido,
           int *edad_pointer, char *tel, int funcion);

/**
 * Recorre la lista pasada y verifica que los contactos de la
 * tabla de hash en los índices de la lista posean los datos pasados por
 * parámetro (si no son "") y en caso de que lo hagan los imprime.
 * Funcionalidad and. 
 */
void imprimir_datos_correctos(TablaHash * agenda, int *bands,
                              SList lista_comparar, char *nombre,
                              char *apellido, int edad, char *tel);

/**
 * Añade todos los elementos de las listas pasadas a un árbol (para revisar 
 * que no haya repetidos) y luego los imprime.
 * Funcionalidad or.
 */
void imprimir_todos(TablaHash * agenda, SList lista_nombre,
                    SList lista_apellido, SList lista_edad, SList lista_tel);

/**
 * Función para imprimir un árbol de los creados por
 * la función anterior
 */
void imprimir_arbol_or(TablaHash * agenda, STree tree);

#endif                          /* __ANDOR_H__ */
