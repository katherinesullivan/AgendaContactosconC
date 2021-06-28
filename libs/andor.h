#ifndef __ANDOR_H__
#define __ANDOR_H__

#include <stddef.h>
#include "arbol.h"
#include "stree.h"
#include "tablahash.h"

typedef struct {
  Arbol arbol;
  int tipo;
  SList *lista;
  void *dato;
} Argumento;

Argumento *argumento_crear(Arbol arbol, int tipo, SList * lista, void *dato);

void *rutina(void *arg);

void andor(TablaHash ** agenda, int *bands, char *nombre, char *apellido,
           int *edad_pointer, char *tel, int funcion);

void imprimir_datos_correctos(TablaHash * agenda, int *bands,
                              SList lista_comparar, char *nombre,
                              char *apellido, int edad, char *tel);

void imprimir_todos(TablaHash * agenda, SList lista_nombre,
                    SList lista_apellido, SList lista_edad, SList lista_tel);

void stree_imprimir(TablaHash * agenda, STree tree);

#endif                          /* __ANDOR_H__ */
