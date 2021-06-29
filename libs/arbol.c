#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbol.h"

#define MAX_STR 32

/**
 * Crea un árbol
 */
Arbol arbol_crear() {
  return NULL;
}

/**
 * Destruye un árbol
 */
void arbol_destruir(Arbol arbol, int tipo_arbol) {
  if (arbol != NULL) {
    arbol_destruir(arbol->izq, tipo_arbol);
    arbol_destruir(arbol->der, tipo_arbol);
    if (tipo_arbol == 2)
      free(arbol->dato);
    free(arbol);
  }
}

/**
 * Función que deuelve el máximo entre dos enteros
 */
int max(int a, int b) {
  return (a > b) ? a : b;
}

/**
 * Devuelve la altura de un árbol
 */
int altura(Arbol arbol) {
  if (arbol == NULL)
    return 0;
  return arbol->alt;
}

/**
 * Crea un nuevo nodo para un árbol
 */
Arbol nuevo_nodo(void *dato, int idx) {
  Arbol nodo = malloc(sizeof(Nodo));

  nodo->dato = dato;
  nodo->idx = idx;
  nodo->izq = NULL;
  nodo->der = NULL;
  nodo->alt = 1;

  return nodo;
}

/**
 * Realiza una rotación a derecha
 */
Arbol der_rotate(Arbol y) {
  Arbol x = y->izq;
  Arbol T2 = x->der;

  x->der = y;
  y->izq = T2;

  y->alt = max(altura(y->izq), altura(y->der)) + 1;
  x->alt = max(altura(x->izq), altura(x->der)) + 1;

  return x;
}

/**
 * Realiza una rotación a izquierda
 */
Arbol izq_rotate(Arbol x) {
  Arbol y = x->der;
  Arbol T2 = y->izq;

  y->izq = x;
  x->der = T2;

  x->alt = max(altura(x->izq), altura(x->der)) + 1;
  y->alt = max(altura(y->izq), altura(y->der)) + 1;

  return y;
}

/**
 * Balancea el árbol pasado como parámetro en caso de ser necesario
 */
Arbol balancear(Arbol nodo, int balance) {
  // izq izq caso
  if (balance > 1 && get_balance(nodo->izq) >= 0)
    return der_rotate(nodo);

  // izq der caso
  if (balance > 1 && get_balance(nodo->izq) < 0) {
    nodo->izq = izq_rotate(nodo->izq);
    return der_rotate(nodo);
  }
  // der der caso
  if (balance < -1 && get_balance(nodo->der) <= 0)
    return izq_rotate(nodo);

  // der izq caso
  if (balance < -1 && get_balance(nodo->der) > 0) {
    nodo->der = der_rotate(nodo->der);
    return izq_rotate(nodo);
  }

  return nodo;
}

/**
 * Obtiene el balance de un nodo 
 */
int get_balance(Arbol nodo) {
  if (nodo == NULL)
    return 0;
  return altura(nodo->izq) - altura(nodo->der);
}

/**
 * Inserta un nuevo nodo formado por los datos pasados como parámetros 
 * al árbol también pasado como parámetro
 */
Arbol arbol_insertar(Arbol nodo, void *dato, int idx, int tipo_arbol) {
  if (nodo == NULL)
    return (nuevo_nodo(dato, idx));

  // No queremos 2 nodos iguales
  if (nodo->idx == idx)
    return nodo;

  // Los árboles de tipo 1 contienen strings como datos
  if (tipo_arbol == 1) {
    char *dato_str = (char *) dato;
    char *nodo_dato_str = (char *) (nodo->dato);

    if (strcmp(dato_str, nodo_dato_str) <= 0)
      nodo->izq = arbol_insertar(nodo->izq, dato, idx, tipo_arbol);

    if (strcmp(dato_str, nodo_dato_str) > 0)
      nodo->der = arbol_insertar(nodo->der, dato, idx, tipo_arbol);
  }

  // Los árboles de tipo 2 contienen int* como datos
  if (tipo_arbol == 2) {
    int dato_int = *(int *) dato;
    int nodo_dato_int = *(int *) nodo->dato;

    if (dato_int <= nodo_dato_int)
      nodo->izq = arbol_insertar(nodo->izq, dato, idx, tipo_arbol);

    else
      nodo->der = arbol_insertar(nodo->der, dato, idx, tipo_arbol);
  }

  nodo->alt = 1 + max(altura(nodo->izq), altura(nodo->der));

  int balance = get_balance(nodo);

  return balancear(nodo, balance);
}

/**
 * Obtiene el nodo de mínimo valor de un árbol
 */
Arbol min_value_nodo(Arbol nodo) {
  Arbol current = nodo;

  while (current->izq != NULL)
    current = current->izq;

  return current;
}

/**
 * Elimina el nodo con los datos pasados como parámetros del árbol 
 * también pasado como parámetro
 */
Arbol arbol_eliminar(Arbol nodo, void *dato, int idx, int tipo_arbol) {
  if (nodo == NULL) {
    return nodo;
  }

  if (idx == nodo->idx) {
    // Estamos en el nodo a eliminar 

    if ((nodo->izq == NULL) || (nodo->der == NULL)) {
      Arbol temp = nodo->izq ? nodo->izq : nodo->der;

      // Si no tiene hijos
      if (temp == NULL) {
        temp = nodo;
        if (tipo_arbol == 2)
          free(nodo->dato);
        free(temp);
        nodo = NULL;
      }
      // Si tiene un hijo
      else {
        if (tipo_arbol == 2)
          free(nodo->dato);
        *nodo = *temp;
        free(temp);
      }
    } else {
      // Si tiene 2 hijos
      Arbol temp = min_value_nodo(nodo->der);

      nodo->idx = temp->idx;

      if (tipo_arbol == 1)
        nodo->dato = temp->dato;

      else if (tipo_arbol == 2) {
        free(nodo->dato);
        int *nuevo_dato = malloc(sizeof(int));
        int temp_dato = *(int *) (temp->dato);
        *nuevo_dato = temp_dato;
        nodo->dato = nuevo_dato;
      }

      nodo->der = arbol_eliminar(nodo->der, temp->dato, temp->idx, tipo_arbol);
    }
  }

  else {
    // Si no estoy en el nodo a eliminar, tengo que ver para donde ir

    // Los árboles de tipo 1 contienen strings como datos
    if (tipo_arbol == 1) {
      char *dato_str = (char *) dato;
      char *nodo_dato_str = (char *) (nodo->dato);

      if (strcmp(dato_str, nodo_dato_str) <= 0)
        nodo->izq = arbol_eliminar(nodo->izq, dato, idx, tipo_arbol);

      if (strcmp(dato_str, nodo_dato_str) > 0)
        nodo->der = arbol_eliminar(nodo->der, dato, idx, tipo_arbol);
    }

    // Los árboles de tipo 2 contienen int* como datos
    if (tipo_arbol == 2) {
      int dato_int = *(int *) dato;
      int nodo_dato_int = *(int *) nodo->dato;

      if (dato_int == nodo_dato_int) {
        nodo->izq = arbol_eliminar(nodo->izq, dato, idx, tipo_arbol);
        nodo->der = arbol_eliminar(nodo->der, dato, idx, tipo_arbol);
      }

      else if (dato_int < nodo_dato_int)
        nodo->izq = arbol_eliminar(nodo->izq, dato, idx, tipo_arbol);

      else
        nodo->der = arbol_eliminar(nodo->der, dato, idx, tipo_arbol);
    }
  }

  // Si el nodo no tenía hijos
  if (nodo == NULL) {
    return NULL;
  }

  nodo->alt = 1 + max(altura(nodo->izq), altura(nodo->der));

  int balance = get_balance(nodo);

  return balancear(nodo, balance);
}

/**
 * Función de utilidad para imprimir un árbol en orden
 */
void arbol_imprimir_inorder(Arbol arbol, int tipo_de_arbol) {
  if (arbol == NULL)
    return;

  arbol_imprimir_inorder(arbol->izq, tipo_de_arbol);

  if (tipo_de_arbol == 1) {
    char *dato_str = (char *) arbol->dato;
    printf("En %d: %s con altura: %d\n", arbol->idx, dato_str, arbol->alt);
  }
  if (tipo_de_arbol == 2) {
    int dato_int = *(int *) (arbol->dato);
    printf("En %d: %d con altura: %d\n", arbol->idx, dato_int, arbol->alt);
  }

  arbol_imprimir_inorder(arbol->der, tipo_de_arbol);
}

/**
 * Función para los árboles de tipo 2.
 * Añade todos los elementos del árbol en los respectivos arrays.
 */
void arbol_a_arrays(Arbol arbol, int *array_edades, int *array_indices, int *i) {
  if (arbol == NULL)
    return;

  arbol_a_arrays(arbol->izq, array_edades, array_indices, i);
  array_edades[*i] = *(int *) arbol->dato;
  array_indices[*i] = arbol->idx;
  *i = *i + 1;
  arbol_a_arrays(arbol->der, array_edades, array_indices, i);
}

/**
 * Busca en un árbol todos los elementos con el dato igual al dato
 * pasado como parámetro y los añade a la lista pasada como parámetro
 */
void arbol_buscar(Arbol arbol, SList * lista, void *dato, int tipo_arbol) {
  if (arbol == NULL)
    return;

  if (tipo_arbol == 1) {
    char *arbol_dato = (char *) (arbol->dato);
    char *dato_str = (char *) dato;
    int rdo = strcmp(dato_str, arbol_dato);

    if (rdo == 0) {
      *lista = slist_agregar_inicio(*lista, arbol->idx);
      arbol_buscar(arbol->izq, lista, dato, tipo_arbol);
      arbol_buscar(arbol->der, lista, dato, tipo_arbol);
    } else if (rdo < 0) {
      arbol_buscar(arbol->izq, lista, dato, tipo_arbol);
    } else {
      arbol_buscar(arbol->der, lista, dato, tipo_arbol);
    }
  }

  else if (tipo_arbol == 2) {
    int dato_int = *(int *) dato;
    int arbol_dato = *(int *) (arbol->dato);

    if (dato_int == arbol_dato) {
      *lista = slist_agregar_inicio(*lista, arbol->idx);
      arbol_buscar(arbol->izq, lista, dato, tipo_arbol);
      arbol_buscar(arbol->der, lista, dato, tipo_arbol);
    } else if (dato_int < arbol_dato) {
      arbol_buscar(arbol->izq, lista, dato, tipo_arbol);
    } else {
      arbol_buscar(arbol->der, lista, dato, tipo_arbol);
    }
  }
}
