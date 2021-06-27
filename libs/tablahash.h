#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include <stddef.h>
#include <stdio.h>
#include "contacto.h"
#include "arbol.h"

/**
 * Tipo de las funciones hash a ser consideradas por las tablas hash.
 */
typedef unsigned (*FuncionHash) (char *clave);

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  char *clave;
  Contacto dato;
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
  Arbol arbol_nombre;
  Arbol arbol_apellido;
  Arbol arbol_edad;
  Arbol arbol_tel;
} TablaHash;

/**
 * Estructura que representa un argumento para los hilos creados
 * para insertar o eliminar en los árboles.
 */
typedef struct {
  Arbol* arbol;
  void* dato;
  int idx;
  int tipo;
} ArgHilo;

/*
 * Crea una nueva tabla hash vacía con la capacidad dada.
 */
TablaHash *tablahash_crear(unsigned capacidad, FuncionHash hash,
                           FuncionHash hash2);

/*
 * Inserta el dato en la tabla asociado a la clave dada.
 */
void tablahash_insertar(TablaHash * tabla, char *clave, Contacto dato);

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

void prettyprint_th(TablaHash* th);

void* tablahash_editar(TablaHash * tabla, char *clave, int edad, char* tel);

void tablahash_imprimir_file(TablaHash* tabla, FILE* fp);

void inorder_aux(TablaHash* tabla, Arbol arbol, FILE *fp);

void tablahash_imprimir_inorder_nombre(TablaHash* tabla, FILE* fp);

void tablahash_imprimir_inorder_apellido(TablaHash* tabla, FILE* fp);

void tablahash_imprimir_inorder_edad(TablaHash* tabla, FILE* fp);

void tablahash_imprimir_inorder_tel(TablaHash* tabla, FILE* fp);

ArgHilo* tablahash_arg_crear(Arbol* arbol, void* dato, int idx, int tipo);

void* rutina_insertar(void* arg);

void* rutina_eliminar(void* arg);

void parallel_insertar_eliminar(TablaHash* tabla, int idx, int funcion);

#endif                          /* __TABLAHASH_H__ */
