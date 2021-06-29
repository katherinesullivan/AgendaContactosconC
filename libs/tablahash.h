#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include <stddef.h>
#include <stdio.h>
#include "contacto.h"
#include "arbol.h"

/**
 * Tipo de las funciones hash a ser consideradas por las tablas hash
 */
typedef unsigned (*FuncionHash) (char *clave);

/**
 * Casillas en la que almacenaremos los datos de la tabla hash
 */
typedef struct {
  char *clave;
  Contacto dato;
  int estado;                   // será 0 si esta libre, 1 si está ocupada, 2 si está eliminada
} CasillaHash;

/*
 * Estructura principal que representa la tabla hash
 */
typedef struct {
  CasillaHash *tabla;
  unsigned numElems;
  unsigned capacidad;
  FuncionHash hash;
  FuncionHash hash2;
  Arbol arbol_nombre;
  Arbol arbol_apellido;
  Arbol arbol_edad;
  Arbol arbol_tel;
} TablaHash;

/**
 * Estructura que representa un argumento para los hilos creados
 * para insertar o eliminar en los árboles
 */
typedef struct {
  Arbol *arbol;
  void *dato;
  int idx;
  int tipo;
} ArgHilo;


/**
 * Crea una nueva tabla hash vacía con la capacidad dada
 */
TablaHash *tablahash_crear(unsigned capacidad, FuncionHash hash,
                           FuncionHash hash2);

/**
 * Inserta el dato en la tabla asociado a la clave dada
 */
TablaHash *tablahash_insertar(TablaHash * tabla, char *clave, Contacto dato);

/**
 * Crea una nueva tabla de hash con los elementos de la 
 * tabla dada y con su capacidad aumentada al doble
 */
TablaHash *tablahash_agrandar(TablaHash * tabla);

/**
 * Busca el dato en la tabla asociado a la clave dada.
 * Si solover es 0, en caso de que esté presente devuelve un puntero al mismo, 
 * en caso contrario devuelve NULL.
 * Si solover es 1, devuelve NULL si no está presente, y un puntero
 * a su clave si lo está
 */
void *tablahash_buscar(TablaHash * tabla, char *clave, int solover);

/**
 * Elimina el dato en la tabla asociado a la clave dada,
 * en caso de que este haya estado presente
 */
void tablahash_eliminar(TablaHash * tabla, char *clave);

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash * tabla);

/**
 * Función para editar el elemento de la Tabla Hash con la clave dada,
 * en caso de que este esté presente en la misma
 */
void *tablahash_editar(TablaHash * tabla, char *clave, int edad, char *tel);

/**
 * Función que imprime los elementos de la una Tabla Hash en un archivo
 */
void tablahash_imprimir_file(TablaHash * tabla, FILE * fp);

/**
 * Imprime la Tabla Hash en un archivo siguiendo el orden de los nombres
 */
void tablahash_imprimir_inorder_nombre(TablaHash * tabla, FILE * fp);

/**
 * Imprime la Tabla Hash en un archivo siguiendo el orden de los apellidos
 */
void tablahash_imprimir_inorder_apellido(TablaHash * tabla, FILE * fp);

/**
 * Imprime la Tabla Hash en un archivo siguiendo el orden de las edades
 */
void tablahash_imprimir_inorder_edad(TablaHash * tabla, FILE * fp);

/**
 * Imprime la Tabla Hash en un archivo siguiendo el orden de los teléfonos
 */
void tablahash_imprimir_inorder_tel(TablaHash * tabla, FILE * fp);

/**
 * Función auxiliar para la impresión en orden
 */
void inorder_aux(TablaHash * tabla, Arbol arbol, FILE * fp);

/**
 * Rutina para la función destruir con árboles de tipo 1
 */
void *rutina_destruir_1(void *arbol);

/**
 * Rutina para la función destruir con árboles de tipo 2
 */
void *rutina_destruir_2(void *arbol);

/**
 * Función para paralelizar la destrucción de los árboles
 */
void paralell_destruir_arboles(TablaHash * tabla);

/**
 * Función para la creación de los argumentos de las rutinas
 */
ArgHilo *tablahash_arg_crear(Arbol * arbol, void *dato, int idx, int tipo);

/**
 * Rutina para la función insertar
 */
void *rutina_insertar(void *arg);

/**
 * Rutina para la función eliminar
 */
void *rutina_eliminar(void *arg);

/**
 * Función para paralelizar inserción y eliminación en los árboles
 */
void parallel_insertar_eliminar(TablaHash * tabla, int idx, int funcion);

/**
 * Función de utlidad para imprimir una Tabla Hash
 */
void prettyprint_th(TablaHash * th);

#endif                          /* __TABLAHASH_H__ */
