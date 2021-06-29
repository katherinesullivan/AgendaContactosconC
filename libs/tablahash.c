#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include "tablahash.h"
#define MAX_NOMBRE 32
#define MAX_APELLIDO 32
#define MAX_TEL 32
#define MAX_CLAVE MAX_NOMBRE+MAX_APELLIDO

/**
 * Crea una nueva Tabla Hash vacía con la capacidad dada 
 */
TablaHash *tablahash_crear(unsigned capacidad, FuncionHash hash,
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

/**
 * Inserta el dato en la tabla asociado a la clave dada. 
 */
TablaHash *tablahash_insertar(TablaHash * tabla, char *clave, Contacto dato) {
  int done = 0;
  int i = 0;
  unsigned idx;

  while (!done) {
    // Calculamos la posición de la clave dada, de acuerdo a la función hash.
    idx = tabla->hash(clave) + i * tabla->hash2(clave);
    idx = idx % tabla->capacidad;
    if (tabla->tabla[idx].estado == 0 || tabla->tabla[idx].estado == 2) {
      // Si estaba vacío o eliminado el lugar, almacenamos los datos ingresados.
      tabla->tabla[idx].clave = clave;
      tabla->tabla[idx].dato = dato;
      tabla->tabla[idx].estado = 1;

      parallel_insertar_eliminar(tabla, idx, 1);
      done = 1;
    }
    i++;
  }

  // Aumentamos la cantidad de elementos que hay
  tabla->numElems++;

  if (tabla->numElems / tabla->capacidad >= 0.75) {
    tabla = tablahash_agrandar(tabla);
  }

  return tabla;

}

/**
 * Crea una nueva tabla de hash con los elementos de la 
 * tabla dada y con su capacidad aumentada al doble
 */
TablaHash *tablahash_agrandar(TablaHash * tabla) {
  printf("Su agenda estaba llegando a un punto crítico en su capacidad, ");
  printf("por lo tanto estamos duplicandola. ");
  printf("Esto puede demorar unos momentos.\n");
  unsigned cap = tabla->capacidad;
  TablaHash *nueva_tabla = tablahash_crear(cap * 2, tabla->hash, tabla->hash2);

  for (unsigned int idx = 0; idx < cap; idx++) {
    if (tabla->tabla[idx].estado == 1) {
      Contacto dato = tabla->tabla[idx].dato;
      char *clave = tabla->tabla[idx].clave;
      char *nueva_clave = malloc(sizeof(char) * MAX_CLAVE);
      strcpy(nueva_clave, clave);
      char *nuevo_nombre = malloc(sizeof(char) * MAX_NOMBRE);
      strcpy(nuevo_nombre, dato->nombre);
      char *nuevo_apellido = malloc(sizeof(char) * MAX_APELLIDO);
      strcpy(nuevo_apellido, dato->apellido);
      char *nuevo_tel = malloc(sizeof(char) * MAX_TEL);
      strcpy(nuevo_tel, dato->telefono);
      Contacto nuevo_contacto =
          contacto_crear(nuevo_nombre, nuevo_apellido, dato->edad, nuevo_tel);
      tablahash_insertar(nueva_tabla, nueva_clave, nuevo_contacto);
    }
  }
  tablahash_destruir(tabla);

  return nueva_tabla;
}

/**
 * Busca el dato en la tabla asociado a la clave dada. 
 * Si solover es 0, en caso de que esté presente devuelve un puntero al mismo, 
 * en caso contrario devuelve NULL. Si solover es 1, devuelve NULL si no está 
 * presente, y un puntero a su clave si lo está
 */
void *tablahash_buscar(TablaHash * tabla, char *clave, int solover) {
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

/**
 * Elimina el dato en la tabla asociado a la clave dada, 
 * en caso de que este haya estado presente
 */
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

/**
 * Destruye la tabla 
 */
void tablahash_destruir(TablaHash * tabla) {
  for (unsigned int i = 0; i < tabla->capacidad; i++) {
    if (tabla->tabla[i].estado == 1) {
      free(tabla->tabla[i].clave);
      contacto_destruir(tabla->tabla[i].dato);
    }
  }
  paralell_destruir_arboles(tabla);
  free(tabla->tabla);
  free(tabla);
}

/**
 * Función para editar el elemento de la Tabla Hash con la clave dada, 
 * en caso de que este esté presente en la misma
 */
void *tablahash_editar(TablaHash * tabla, char *clave, int edad, char *tel) {
  int done = 0;
  int i = 0;
  unsigned idx;

  while (!done) {
    idx = tabla->hash(clave) + i * tabla->hash2(clave);
    idx = idx % tabla->capacidad;
    if (tabla->tabla[idx].estado == 0) {
      // Si me encunentro con una casilla vacía significa que no
      // está en la tabla el elemento con la clave dada
      done = 1;
      return NULL;
    } else if (tabla->tabla[idx].estado != 2 &&
               strcmp(tabla->tabla[idx].clave, clave) == 0) {
      done = 1;
      
      // Si lo encontré elimino de los árboles los elementos viejos
      char *tel_viejo = tabla->tabla[idx].dato->telefono;
      int edad_vieja = tabla->tabla[idx].dato->edad;

      tabla->arbol_tel = arbol_eliminar(tabla->arbol_tel, tel_viejo, idx, 1);
      tabla->arbol_edad =
          arbol_eliminar(tabla->arbol_edad, &edad_vieja, idx, 2);
      free(tel_viejo);
      
      // Ingreso los nuevo datos 
      tabla->tabla[idx].dato->telefono = tel;
      tabla->tabla[idx].dato->edad = edad;

      // Y agrego a los árboles con los nuevos datos
      tabla->arbol_tel = arbol_insertar(tabla->arbol_tel, tel, idx, 1);
      int *edad_pointer = malloc(sizeof(int));
      *edad_pointer = edad;
      tabla->arbol_edad =
          arbol_insertar(tabla->arbol_edad, edad_pointer, idx, 2);

      return tabla->tabla[idx].dato;
    }
    i++;
  }
  return NULL;
}

/**
 * Función que imprime los elementos de la una Tabla Hash en un archivo
 */
void tablahash_imprimir_file(TablaHash * tabla, FILE * fp) {
  for (unsigned int i = 0; i < tabla->capacidad; i++) {
    if (tabla->tabla[i].estado == 1) {
      contacto_imprimir_file(tabla->tabla[i].dato, fp);
    }
  }
}

/**
 * Imprime la Tabla Hash en un archivo siguiendo el orden de los nombres
 */
void tablahash_imprimir_inorder_nombre(TablaHash * tabla, FILE * fp) {
  Arbol arbol = tabla->arbol_nombre;
  inorder_aux(tabla, arbol, fp);
}

/**
 * Imprime la Tabla Hash en un archivo siguiendo el orden de los apellidos
 */
void tablahash_imprimir_inorder_apellido(TablaHash * tabla, FILE * fp) {
  Arbol arbol = tabla->arbol_apellido;
  inorder_aux(tabla, arbol, fp);
}

/**
 * Imprime la Tabla Hash en un archivo siguiendo el orden de las edades
 */
void tablahash_imprimir_inorder_edad(TablaHash * tabla, FILE * fp) {
  Arbol arbol = tabla->arbol_edad;
  inorder_aux(tabla, arbol, fp);
}

/**
 * Imprime la Tabla Hash en un archivo siguiendo el orden de los teléfonos
 */
void tablahash_imprimir_inorder_tel(TablaHash * tabla, FILE * fp) {
  Arbol arbol = tabla->arbol_tel;
  inorder_aux(tabla, arbol, fp);
}

/**
 * Función auxiliar para la impresión en orden
 */
void inorder_aux(TablaHash * tabla, Arbol arbol, FILE * fp) {
  if (arbol == NULL)
    return;

  inorder_aux(tabla, arbol->izq, fp);
  contacto_imprimir_file(tabla->tabla[arbol->idx].dato, fp);
  inorder_aux(tabla, arbol->der, fp);
}

/**
 * Rutina para la función destruir con árboles de tipo 1
 */
void *rutina_destruir_1(void *arbol) {
  Arbol arbol1 = (Arbol) arbol;
  arbol_destruir(arbol1, 1);
  return arbol1;
}

/**
 * Rutina para la función destruir con árboles de tipo 2
 */
void *rutina_destruir_2(void *arbol) {
  Arbol arbol2 = (Arbol) arbol;
  arbol_destruir(arbol2, 2);
  return arbol2;
}

/**
 * Función para paralelizar la destrucción de los árboles
 */
void paralell_destruir_arboles(TablaHash * tabla) {
  Arbol arbol_nombre = tabla->arbol_nombre;
  Arbol arbol_apellido = tabla->arbol_apellido;
  Arbol arbol_edad = tabla->arbol_edad;
  Arbol arbol_tel = tabla->arbol_tel;

  pthread_t hilos[4];

  assert(!pthread_create
         (&hilos[0], NULL, rutina_destruir_1, (void *) arbol_nombre));
  assert(!pthread_create
         (&hilos[2], NULL, rutina_destruir_1, (void *) arbol_apellido));
  assert(!pthread_create
         (&hilos[1], NULL, rutina_destruir_2, (void *) arbol_edad));
  assert(!pthread_create
         (&hilos[3], NULL, rutina_destruir_1, (void *) arbol_tel));

  for (int i = 0; i < 4; i++) {
    assert(!pthread_join(hilos[i], NULL));
  }

}

/**
 * Función para la creación de los argumentos de las rutinas
 */
ArgHilo *tablahash_arg_crear(Arbol * arbol, void *dato, int idx, int tipo) {
  ArgHilo *arg = malloc(sizeof(ArgHilo));
  arg->arbol = arbol;
  arg->dato = dato;
  arg->idx = idx;
  arg->tipo = tipo;
  return arg;
}

/**
 * Rutina para la función insertar
 */
void *rutina_insertar(void *arg) {
  ArgHilo *arg1 = (ArgHilo *) arg;
  Arbol *arbol = arg1->arbol;
  void *dato = arg1->dato;
  int idx = arg1->idx;
  int tipo = arg1->tipo;
  *arbol = arbol_insertar(*arbol, dato, idx, tipo);
  return arbol;
}

/**
 * Rutina para la función eliminar
 */
void *rutina_eliminar(void *arg) {
  ArgHilo *arg1 = (ArgHilo *) arg;
  Arbol *arbol = arg1->arbol;
  void *dato = arg1->dato;
  int idx = arg1->idx;
  int tipo = arg1->tipo;
  *arbol = arbol_eliminar(*arbol, dato, idx, tipo);
  return arbol;
}

/**
 * Función para paralelizar inserción y eliminación en los árboles
 */
void parallel_insertar_eliminar(TablaHash * tabla, int idx, int funcion) {
  Contacto dato = tabla->tabla[idx].dato;

  pthread_t hilos[4];
  ArgHilo *arg_nombre =
      tablahash_arg_crear(&tabla->arbol_nombre, dato->nombre, idx, 1);
  ArgHilo *arg_apellido =
      tablahash_arg_crear(&tabla->arbol_apellido, dato->apellido, idx, 1);
  ArgHilo *arg_edad;
  if (funcion == 1) {
    int *edad_pointer = malloc(sizeof(int));
    *edad_pointer = dato->edad;
    arg_edad = tablahash_arg_crear(&tabla->arbol_edad, edad_pointer, idx, 2);
  } else
    arg_edad = tablahash_arg_crear(&tabla->arbol_edad, &dato->edad, idx, 2);
  ArgHilo *arg_tel =
      tablahash_arg_crear(&tabla->arbol_tel, dato->telefono, idx, 1);

  if (funcion == 1) {
    assert(!pthread_create
           (&hilos[0], NULL, rutina_insertar, (void *) arg_nombre));
    assert(!pthread_create
           (&hilos[1], NULL, rutina_insertar, (void *) arg_apellido));
    assert(!pthread_create
           (&hilos[2], NULL, rutina_insertar, (void *) arg_edad));
    assert(!pthread_create(&hilos[3], NULL, rutina_insertar, (void *) arg_tel));
  }

  if (funcion == 2) {
    assert(!pthread_create
           (&hilos[0], NULL, rutina_eliminar, (void *) arg_nombre));
    assert(!pthread_create
           (&hilos[1], NULL, rutina_eliminar, (void *) arg_apellido));
    assert(!pthread_create
           (&hilos[2], NULL, rutina_eliminar, (void *) arg_edad));
    assert(!pthread_create(&hilos[3], NULL, rutina_eliminar, (void *) arg_tel));
  }

  for (int i = 0; i < 4; i++) {
    assert(!pthread_join(hilos[i], NULL));
  }

  free(arg_nombre);
  free(arg_apellido);
  free(arg_edad);
  free(arg_tel);

}

/**
 * Función de utlidad para imprimir una Tabla Hash
 */
void prettyprint_th(TablaHash * th) {
  printf("--- TABLA HASH (%u elemento%s) ---\n", th->numElems,
         (th->numElems == 1) ? "" : "s");
  for (unsigned int i = 0; i < th->capacidad; i++) {
    if (th->tabla[i].clave == NULL || (th->tabla[i].estado == 2))
      puts("NULL");
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
  printf("-------------------------------%s%s\n",
         (th->numElems == 1) ? "" : "-", (th->numElems > 9) ? "-" : "");
}
