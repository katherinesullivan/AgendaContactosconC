#include "andor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>

/**
 * Crea un argumento para pasarle a la rutina 
 */
Argumento *argumento_crear(Arbol arbol, int tipo, SList * lista, void *dato) {
  Argumento *arg = malloc(sizeof(Argumento));
  arg->arbol = arbol;
  arg->tipo = tipo;
  arg->lista = lista;
  arg->dato = dato;
  return arg;
}

/**
 * Rutina para los hilos. Busca los datos en el árbol
 * y los añade a la lista
 */
void *rutina(void *arg) {
  Argumento *arg1 = (Argumento *) arg;
  arbol_buscar(arg1->arbol, arg1->lista, arg1->dato, arg1->tipo);
  return arg;
}

/**
 * Función principal del módulo.
 * Busca en paralelo los datos pasados en los árboles de la agenda y
 * luego en base a si está siendo llamada por and o or llama a las
 * funciones que mostrarán los datos por pantalla.
 */
void andor(TablaHash ** agenda, int *bands, char *nombre, char *apellido,
           int *edad_pointer, char *tel, int funcion) {
  Arbol arbol_nombre = (*agenda)->arbol_nombre;
  Arbol arbol_apellido = (*agenda)->arbol_apellido;
  Arbol arbol_edad = (*agenda)->arbol_edad;
  Arbol arbol_tel = (*agenda)->arbol_tel;

  // Como se realiza en paralelo busco en todas las listas 
  // por lo tanto creo sus hilos y argumentos respectivos
  pthread_t hilos[4];

  SList lista_nombre = slist_crear();
  Argumento *argumento_nombre =
      argumento_crear(arbol_nombre, 1, &lista_nombre, nombre);

  SList lista_apellido = slist_crear();
  Argumento *argumento_apellido =
      argumento_crear(arbol_apellido, 1, &lista_apellido, apellido);

  SList lista_edad = slist_crear();
  Argumento *argumento_edad =
      argumento_crear(arbol_edad, 2, &lista_edad, edad_pointer);

  SList lista_tel = slist_crear();
  Argumento *argumento_tel = argumento_crear(arbol_tel, 1, &lista_tel, tel);

  assert(!pthread_create(&hilos[0], NULL, rutina, (void *) argumento_nombre));
  assert(!pthread_create(&hilos[1], NULL, rutina, (void *) argumento_apellido));
  assert(!pthread_create(&hilos[2], NULL, rutina, (void *) argumento_edad));
  assert(!pthread_create(&hilos[3], NULL, rutina, (void *) argumento_tel));

  for (int i = 0; i < 4; i++) {
    assert(!pthread_join(hilos[i], NULL));
  }

  free(argumento_nombre);
  free(argumento_apellido);
  free(argumento_edad);
  free(argumento_tel);

  if (funcion == 1) {
    // Bands en i resulta 0 si el argumento correspondiente
    // fue pasado como vacío por el usuario

    // No queremos considerar esas listas porque serán vacías
    if (!bands[0]) {
      lista_nombre = slist_cant_max(lista_nombre);
    }
    if (!bands[1]) {
      lista_apellido = slist_cant_max(lista_apellido);
    }
    if (!bands[2]) {
      lista_edad = slist_cant_max(lista_edad);
    }
    if (!bands[3]) {
      lista_tel = slist_cant_max(lista_tel);
    }

    SList lista_comparar =
        slist_mas_chica(lista_nombre, lista_apellido, lista_edad, lista_tel);
    int edad = *edad_pointer;
    imprimir_datos_correctos(*agenda, bands, lista_comparar, nombre, apellido,
                             edad, tel);
  }

  else if (funcion == 2) {
    imprimir_todos(*agenda, lista_nombre, lista_apellido, lista_edad,
                   lista_tel);
  }

  slist_destruir(lista_nombre);
  slist_destruir(lista_apellido);
  slist_destruir(lista_edad);
  slist_destruir(lista_tel);
}

/**
 * Recorre la lista pasada y verifica que los contactos de la
 * tabla de hash en los índices de la lista posean los datos pasados por
 * parámetro (si no son "") y en caso de que lo hagan los imprime.
 * Funcionalidad and. 
 */
void imprimir_datos_correctos(TablaHash * agenda, int *bands,
                              SList lista_comparar, char *nombre,
                              char *apellido, int edad, char *tel) {
  SList iter = lista_comparar;
  slist_imprimir(lista_comparar);
  while (iter != NULL) {
    int suma = 0;
    int idx = iter->dato;
    Contacto contacto = agenda->tabla[idx].dato;
    if (bands[0]) {
      if (!strcmp(contacto->nombre, nombre))
        suma++;
    } else
      suma++;
    if (bands[1]) {
      if (!strcmp(contacto->apellido, apellido))
        suma++;
    } else
      suma++;
    if (bands[2]) {
      unsigned edad_unsigned = edad;
      if (contacto->edad == edad_unsigned)
        suma++;
    } else
      suma++;
    if (bands[3]) {
      if (!strcmp(contacto->telefono, tel))
        suma++;
    } else
      suma++;
    if (suma == 4)
      contacto_imprimir(contacto);
    iter = iter->sig;
  }
}

/**
 * Añade todos los elementos de las listas pasadas a un árbol (para revisar 
 * que no haya repetidos) y luego los imprime.
 * Funcionalidad or.
 */
void imprimir_todos(TablaHash * agenda, SList lista_nombre,
                    SList lista_apellido, SList lista_edad, SList lista_tel) {
  STree tree = stree_crear();
  SList iter = lista_nombre;
  while (iter != NULL) {
    tree = stree_insertar(tree, iter->dato);
    iter = iter->sig;
  }
  iter = lista_apellido;
  while (iter != NULL) {
    tree = stree_insertar(tree, iter->dato);
    iter = iter->sig;
  }
  iter = lista_edad;
  while (iter != NULL) {
    tree = stree_insertar(tree, iter->dato);
    iter = iter->sig;
  }
  iter = lista_tel;
  while (iter != NULL) {
    tree = stree_insertar(tree, iter->dato);
    iter = iter->sig;
  }
  imprimir_arbol_or(agenda, tree);
  stree_destruir(tree);
}

/**
 * Función para imprimir un árbol de los creados por
 * la función anterior
 */
void imprimir_arbol_or(TablaHash * agenda, STree tree) {
  if (tree != NULL) {
    imprimir_arbol_or(agenda, tree->izq);
    int idx = tree->idx;
    contacto_imprimir(agenda->tabla[idx].dato);
    imprimir_arbol_or(agenda, tree->der);
  }
}
