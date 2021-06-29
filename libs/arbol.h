#ifndef __ARBOL_H__
#define __ARBOL_H__

#include <stddef.h>
#include "slist.h"

/** 
 * Estructuras del árbol
 */
typedef struct _Nodo {
  void *dato;                   // Dato de contacto sobre el cual se compará
  int idx;                      // Índice en donde se encuentra el contacto
  struct _Nodo *izq;            // Subárbol izquierdo
  struct _Nodo *der;            // Subárbol derecho
  int alt;                      // Altura del nodo
} Nodo;

typedef Nodo *Arbol;

/**
 * Crea un árbol
 */
Arbol arbol_crear();

/**
 * Destruye un árbol
 */
void arbol_destruir(Arbol arbol, int tipo_arbol);

/**
 * Función que deuelve el máximo entre dos enteros
 */
int max(int a, int b);

/**
 * Devuelve la altura de un árbol
 */
int altura(Arbol arbol);

/**
 * Crea un nuevo nodo para un árbol
 */
Arbol nuevo_nodo(void *dato, int idx);

/**
 * Realiza una rotación a derecha
 */
Arbol der_rotate(Arbol y);

/**
 * Realiza una rotación a izquierda
 */
Arbol izq_rotate(Arbol x);

/**
 * Balancea el árbol pasado como parámetro en caso de ser necesario
 */
Arbol balancear(Arbol nodo, int balance);

/**
 * Obtiene el balance de un nodo 
 */
int get_balance(Arbol N);

/**
 * Inserta un nuevo nodo formado por los datos pasados como parámetros 
 * al árbol también pasado como parámetro
 */
Arbol arbol_insertar(Arbol nodo, void *dato, int idx, int tipo_arbol);

/**
 * Obtiene el nodo de mínimo valor de un árbol
 */
Arbol min_value_nodo(Arbol nodo);

/**
 * Elimina el nodo con los datos pasados como parámetros del árbol 
 * también pasado como parámetro
 */
Arbol arbol_eliminar(Arbol nodo, void *dato, int idx, int tipo_arbol);

/**
 * Función de utilidad para imprimir un árbol en orden
 */
void arbol_imprimir_inorder(Arbol arbol, int tipo_de_arbol);

/**
 * Función para los árboles de tipo 2.
 * Añade todos los elementos del árbol en los respectivos arrays.
 */
void arbol_a_arrays(Arbol arbol, int *array_edades, int *array_indices, int *i);

/**
 * Busca en un árbol todos los elementos con el dato igual al dato
 * pasado como parámetro y los añade a la lista pasada como parámetro
 */
void arbol_buscar(Arbol arbol, SList * lista, void *dato, int tipo_arbol);

#endif                          /* __ARBOL_H__ */
