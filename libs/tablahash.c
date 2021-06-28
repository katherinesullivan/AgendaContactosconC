#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include "tablahash.h"

/* Crea una nueva tabla Hash vacía con la capacidad dada. */
TablaHash* tablahash_crear(unsigned capacidad, FuncionHash hash,
                           FuncionHash hash2) {
  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash *tabla = malloc(sizeof(TablaHash));
  tabla->hash = hash;
  tabla->capacidad = capacidad;
  tabla->tabla = malloc(sizeof(CasillaHash) * capacidad);
  tabla->numElems = 0;
  tabla->hash2 = hash2;
  tabla->arbol_nombre = arbol_crear();
  tabla->arbol_apellido = arbol_crear();
  tabla->arbol_edad = arbol_crear();
  tabla->arbol_tel = arbol_crear();

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->tabla[idx].clave = NULL;
    tabla->tabla[idx].dato = NULL;
    tabla->tabla[idx].estado = 0;
  }

  return tabla;
}

/* Inserta el dato en la tabla asociado a la clave dada. */
int tablahash_insertar(TablaHash * tabla, char *clave, Contacto dato) {
  if (tabla->numElems == tabla->capacidad) {
    return 0;
  }
  printf("Entre\n");

  int done = 0;
  int i = 0;
  unsigned idx;

  while (!done) {
    // Calculamos la posición de la clave dada, de acuerdo a la función hash.
    idx = tabla->hash(clave) + i * tabla->hash2(clave);
    idx = idx % tabla->capacidad;
    if (tabla->tabla[idx].estado == 0 || tabla->tabla[idx].estado == 2) {
      printf("Encontré indice\n");
      // Si estaba vacío o eliminado el lugar, almacenamos los datos ingresados.
      tabla->tabla[idx].clave = clave;
      tabla->tabla[idx].dato = dato;
      tabla->tabla[idx].estado = 1;

      // VER TEMA MEMORIA

      parallel_insertar_eliminar(tabla, idx, 1);
      /*tabla->arbol_nombre = arbol_insertar(tabla->arbol_nombre, dato->nombre, idx, 1);
      tabla->arbol_apellido = arbol_insertar(tabla->arbol_apellido, dato->apellido, idx, 1);
      tabla->arbol_edad = arbol_insertar(tabla->arbol_edad, edad_pointer, idx, 2);
      tabla->arbol_tel = arbol_insertar(tabla->arbol_tel, dato->telefono, idx, 1);*/
      done = 1;
    }
    i++;
  }

  // Aumentamos la cantidad de elementos que hay
  tabla->numElems++;

  if (tabla->numElems / tabla->capacidad >= 0.85) {
    return 2;
  }

  return 1;
}

/* Busca el dato en la tabla asociado a la clave dada. 
Si solover es 0, en caso de que esté presente devuelve un puntero al mismo, 
en caso contrario devuelve NULL. Si solover es 1, devuelve NULL si no está 
presente, y un puntero a su clave si lo está. */
void *tablahash_buscar(TablaHash * tabla, char *clave, int solover) {
  if (tabla->numElems == tabla->capacidad) {
    printf("No es posible realizar búsquedas. Capacidad completa.\n");
    return;
  }
  int done = 0;
  int i = 0;
  unsigned idx;

  while (!done) {
    idx = tabla->hash(clave) + i * tabla->hash2(clave);
    idx = idx % tabla->capacidad;
    if (tabla->tabla[idx].estado == 0) {
      done = 1;
      return NULL;
    } else if (tabla->tabla[idx].estado != 2 && 
                strcmp(tabla->tabla[idx].clave, clave) == 0) {
      done = 1;
      if (solover) {
        return tabla->tabla[idx].clave;
      }
      return tabla->tabla[idx].dato;
    }
    i++;
  }
  return NULL;
}

/* Elimina el dato en la tabla asociado a la clave dada, 
en caso de que este haya estado presente. */
void tablahash_eliminar(TablaHash * tabla, char *clave) {
  int done = 0;
  int i = 0;
  unsigned idx;

  while (!done) {
    // Calculamos la posición de la clave dada, de acuerdo a la función hash.
    idx = tabla->hash(clave) + i * tabla->hash2(clave);
    idx = idx % tabla->capacidad;
    if (tabla->tabla[idx].estado == 0) {
      // Si llegamos a una casilla vacía es porque no estaba el elemento 
      done = 1;
    } else if (strcmp(tabla->tabla[idx].clave, clave) == 0) {
      // Si lo encontramos, eliminamos y marcamos como eliminado el casillero
      
      parallel_insertar_eliminar(tabla, idx, 2);

      /*tabla->arbol_nombre = arbol_eliminar(tabla->arbol_nombre, dato->nombre, idx, 1);
      tabla->arbol_apellido = arbol_eliminar(tabla->arbol_apellido, dato->apellido, idx, 1);
      tabla->arbol_edad = arbol_eliminar(tabla->arbol_edad, &dato->edad, idx, 2);
      tabla->arbol_tel = arbol_eliminar(tabla->arbol_tel, dato->telefono, idx, 1);*/

      free(tabla->tabla[idx].clave);
      contacto_destruir(tabla->tabla[idx].dato);
      tabla->tabla[idx].estado = 2;
      // Disminuimos el nro de elementos 
      tabla->numElems--;
      done = 1;
    }
    i++;
  }
}

/* Destruye la tabla. */
void tablahash_destruir(TablaHash * tabla) {
  for (unsigned int i = 0; i < tabla->capacidad; i++) {     
    if (tabla->tabla[i].estado == 1) {
      free(tabla->tabla[i].clave);
      contacto_destruir(tabla->tabla[i].dato);
    }
  }
  arbol_destruir(tabla->arbol_nombre, 1);
  arbol_destruir(tabla->arbol_apellido, 1);
  arbol_destruir(tabla->arbol_edad, 2);
  arbol_destruir(tabla->arbol_tel, 1);
  free(tabla->tabla);
  free(tabla);
}

void prettyprint_th(TablaHash* th) {
  printf("--- TABLA HASH (%u elemento%s) ---\n", th->numElems, (th->numElems == 1) ? "" : "s");
  for (unsigned int i = 0; i < th->capacidad; i++) {
    if (th->tabla[i].clave == NULL || (th->tabla[i].estado == 2)) puts("NULL");
    else {
      printf("%s: \n", th->tabla[i].clave);
      contacto_imprimir(th->tabla[i].dato);
    }
  }
  printf("\nArbol nombre\n");
  arbol_imprimir_inorder(th->arbol_nombre, 1);
  printf("\nArbol apellido\n");
  arbol_imprimir_inorder(th->arbol_apellido, 1);
  printf("\nArbol edad\n");
  arbol_imprimir_inorder(th->arbol_edad, 2);
  printf("\nArbol tel\n");
  arbol_imprimir_inorder(th->arbol_tel, 1);
  printf("-------------------------------%s%s\n", (th->numElems == 1) ? "" : "-", (th->numElems > 9) ? "-" : "");
}

void* tablahash_editar(TablaHash* tabla, char *clave, int edad, char* tel) {
  int done = 0;
  int i = 0;
  unsigned idx;

  while (!done) {
    idx = tabla->hash(clave) + i * tabla->hash2(clave);
    idx = idx % tabla->capacidad;
    if (tabla->tabla[idx].estado == 0) {
      done = 1;
      return NULL;
    } else if (tabla->tabla[idx].estado != 2 && 
                strcmp(tabla->tabla[idx].clave, clave) == 0) {
      done = 1;

      // Hacer cambios en arboles
      // ------------------------------------------ VER LO DE DESTRUIR EN ÁRBOLES ---------
      char* tel_viejo = tabla->tabla[idx].dato->telefono;
      int edad_vieja = tabla->tabla[idx].dato->edad;

      tabla->arbol_tel = arbol_eliminar(tabla->arbol_tel, tel_viejo, idx, 1);
      tabla->arbol_edad = arbol_eliminar(tabla->arbol_edad, &edad_vieja, idx, 2);
      free(tel_viejo); 

      tabla->tabla[idx].dato->telefono = tel;
      tabla->tabla[idx].dato->edad = edad;
      tabla->arbol_tel = arbol_insertar(tabla->arbol_tel, tel, idx, 1);
      int* edad_pointer = malloc(sizeof(int));
      *edad_pointer = edad;
      tabla->arbol_edad = arbol_insertar(tabla->arbol_edad, edad_pointer, idx, 2);

      return tabla->tabla[idx].dato;
    }
    i++;
  }
  return NULL;
}

void tablahash_imprimir_file(TablaHash* tabla, FILE* fp) {
  for (unsigned int i = 0; i < tabla->capacidad; i++) {     
    if (tabla->tabla[i].estado == 1) {
      contacto_imprimir_file(tabla->tabla[i].dato, fp);
    }
  }
}

void inorder_aux(TablaHash* tabla, Arbol arbol, FILE *fp) {
  if (arbol == NULL) return;

  inorder_aux(tabla, arbol->izq, fp);
  contacto_imprimir_file(tabla->tabla[arbol->idx].dato, fp);
  inorder_aux(tabla, arbol->der, fp);
}

void tablahash_imprimir_inorder_nombre(TablaHash* tabla, FILE* fp) {
  Arbol arbol = tabla->arbol_nombre;
  inorder_aux(tabla, arbol, fp);
}

void tablahash_imprimir_inorder_apellido(TablaHash* tabla, FILE* fp) {
  Arbol arbol = tabla->arbol_apellido;
  inorder_aux(tabla, arbol, fp);
}

void tablahash_imprimir_inorder_edad(TablaHash* tabla, FILE* fp) {
  Arbol arbol = tabla->arbol_edad;
  inorder_aux(tabla, arbol, fp);
}

void tablahash_imprimir_inorder_tel(TablaHash* tabla, FILE* fp) {
  Arbol arbol = tabla->arbol_tel;
  inorder_aux(tabla, arbol, fp);
}

ArgHilo* tablahash_arg_crear(Arbol* arbol, void* dato, int idx, int tipo) {
  ArgHilo* arg = malloc(sizeof(ArgHilo));
  arg->arbol = arbol;
  arg->dato = dato;
  arg->idx = idx;
  arg->tipo = tipo;
  return arg;
}

void* rutina_insertar(void* arg) {
  ArgHilo* arg1 = (ArgHilo*)arg;
  Arbol* arbol = arg1->arbol;
  void* dato = arg1->dato;
  int idx = arg1->idx;
  int tipo = arg1->tipo;
  *arbol = arbol_insertar(*arbol, dato, idx, tipo);
  return arbol;
}

void* rutina_eliminar(void* arg) {
  ArgHilo* arg1 = (ArgHilo*)arg;
  Arbol* arbol = arg1->arbol;
  void* dato = arg1->dato;
  int idx = arg1->idx;
  int tipo = arg1->tipo;
  *arbol = arbol_eliminar(*arbol, dato, idx, tipo);
  return arbol;
}

void parallel_insertar_eliminar(TablaHash* tabla, int idx, int funcion) {
  Contacto dato = tabla->tabla[idx].dato;

  pthread_t hilos[4];
  ArgHilo* arg_nombre = tablahash_arg_crear(&tabla->arbol_nombre, dato->nombre, idx, 1);
  ArgHilo* arg_apellido = tablahash_arg_crear(&tabla->arbol_apellido, dato->apellido, idx, 1);
  ArgHilo* arg_edad;
  if (funcion == 1) {
    int* edad_pointer = malloc(sizeof(int));
    *edad_pointer = dato->edad;
    arg_edad = tablahash_arg_crear(&tabla->arbol_edad, edad_pointer, idx, 2);
  }
  else arg_edad = tablahash_arg_crear(&tabla->arbol_edad, &dato->edad, idx, 2);
  ArgHilo* arg_tel = tablahash_arg_crear(&tabla->arbol_tel, dato->telefono, idx, 1);

  if (funcion == 1) {
    assert(! pthread_create(&hilos[0], NULL, rutina_insertar, (void*)arg_nombre));
    assert(! pthread_create(&hilos[1], NULL, rutina_insertar, (void*)arg_apellido));    
    assert(! pthread_create(&hilos[2], NULL, rutina_insertar, (void*)arg_edad));
    assert(! pthread_create(&hilos[3], NULL, rutina_insertar, (void*)arg_tel));
  }

  if (funcion == 2) {
    assert(! pthread_create(&hilos[0], NULL, rutina_eliminar, (void*)arg_nombre));
    assert(! pthread_create(&hilos[1], NULL, rutina_eliminar, (void*)arg_apellido));    
    assert(! pthread_create(&hilos[2], NULL, rutina_eliminar, (void*)arg_edad));
    assert(! pthread_create(&hilos[3], NULL, rutina_eliminar, (void*)arg_tel));
  }

  for (int i = 0; i < 4; i++) {
    assert(! pthread_join(hilos[i], NULL));
  }

  free(arg_nombre);
  free(arg_apellido);
  free(arg_edad);
  free(arg_tel);

}