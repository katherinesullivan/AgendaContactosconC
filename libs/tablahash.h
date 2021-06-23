#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include <stddef.h>
#include <stdio.h>

/**
 *  Estructura para el tipo de dato de la casilla hash. 
 * */
typedef struct _NodoArbol {
  char *dato;
  struct _NodoArbol *der;
  struct _NodoArbol *izq;
} NodoArbol;

typedef NodoArbol *Arbol;

/**
 * Crea un nodo de Arbol.
*/
Arbol crear_nodo(char *dato);

/**
 *  Función útil para hacer un recorrido inorder tradicional.
 */
void arbol_imprimir_inorder(Arbol arbol);

/**
 * Función que destruye un elemento de la estructura Arbol.
 */
void arbol_destruir(Arbol arbol);

/**
 * Tipo de las funciones hash a ser consideradas por las tablas hash.
 */
typedef unsigned (*FuncionHash) (char *clave);

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  char *clave;
  Arbol dato;
  int estado;   // será 0 si esta libre, 1 si está ocupada, 2 si está eliminada
} CasillaHash;

/*
 * Estructura principal que representa la tabla hash.
 */
typedef struct {
  CasillaHash *tabla;
  unsigned numElems;
  unsigned capacidad;
  FuncionHash hash;
  FuncionHash hash2;
} TablaHash;

/*
 * Crea una nueva tabla hash vacía con la capacidad dada.
 */
TablaHash *tablahash_crear(unsigned capacidad, FuncionHash hash,
                           FuncionHash hash2);

/*
 * Inserta el dato en la tabla asociado a la clave dada.
 */
void tablahash_insertar(TablaHash * tabla, char *clave, Arbol dato);

/*
 * Busca el dato en la tabla asociado a la clave dada.
 * Si solo ver es 0, en caso de que esté presente devuelve un puntero al mismo, 
 * en caso contrario devuelve NULL.
 * Si solover es 1, devuelve NULL si no está presente, y un puntero
 * a su clave si lo está.
 */
void *tablahash_buscar(TablaHash * tabla, char *clave, int solover);

/*
 * Elimina el dato en la tabla asociado a la clave dada,
 * en caso de que este haya estado presente.
 */
void tablahash_eliminar(TablaHash * tabla, char *clave);

/*
 * Agranda una tabla de hash dada, duplicando su capacidad.
 */
TablaHash *tablahash_agrandar(TablaHash * tabla);

/*
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash * tabla);

#endif                          /* __TABLAHASH_H__ */
