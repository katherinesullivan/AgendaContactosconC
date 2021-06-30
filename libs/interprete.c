#include "interprete.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NOMBRE 32
#define MAX_APELLIDO 32
#define MAX_TEL 32
#define MAX_CLAVE MAX_NOMBRE+MAX_APELLIDO
#define MAX_NRO 9
#define MAX_FILE 50
#define FST_LINE_LEN 31
#define MAX_ATR 32

/************************** Intérprete ********************************/

/**
 * Función principal. 
 * Decide a qué función llamar dependiendo de la entrada del usuario
 */
int interpretar(TablaHash ** agenda, char *accion, AccList * deshacer,
                AccList * rehacer) {
  /*printf("Deshacer:\n");
  imprimir_acciones(deshacer);
  printf("Rehacer:\n");
  imprimir_acciones(rehacer);*/

  print_solicitud(0);
  fgets(accion, MAX_NRO, stdin);
  int nro_accion = atoi(accion);

  if (nro_accion == 1) {
    buscar(agenda, deshacer);
    return 1;
  }

  if (nro_accion == 2) {
    acciones_reestablecer(rehacer);
    agregar(agenda, deshacer);
    return 1;
  }

  if (nro_accion == 3) {
    acciones_reestablecer(rehacer);
    eliminar(agenda, deshacer);
    return 1;
  }

  if (nro_accion == 4) {
    acciones_reestablecer(rehacer);
    editar(agenda, deshacer);
    return 1;
  }

  if (nro_accion == 5) {
    acciones_reestablecer(rehacer);
    cargar(agenda);
    return 1;
  }

  if (nro_accion == 6) {
    guardar(agenda);
    return 1;
  }

  if (nro_accion == 7) {
    if (deshacer->elems == 0)
      print_error(7);
    else
      undo_redo(agenda, deshacer, rehacer);
    return 1;
  }

  if (nro_accion == 8) {
    if (rehacer->elems == 0)
      print_error(8);
    else
      undo_redo(agenda, rehacer, deshacer);
    return 1;
  }

  if (nro_accion == 9) {
    and(agenda);
    return 1;
  }

  if (nro_accion == 10) {
    or(agenda);
    return 1;
  }

  if (nro_accion == 11) {
    guardar_ordenado(agenda);
    return 1;
  }

  if (nro_accion == 12) {
    buscar_suma_edades(agenda);
    return 1;
  }

  if (nro_accion == 13) {
    print_salida();
    //prettyprint_th(*agenda);
    tablahash_destruir(*agenda);
    acciones_destruir(deshacer);
    acciones_destruir(rehacer);
    return 0;
  }

  else {
    print_error(1);
    return 1;
  }
}


/************************** Acciones ********************************/

/**
 * Función para buscar un contacto
 */
void buscar(TablaHash ** agenda, AccList * deshacer) {
  buscar_eliminar_editar(agenda, 1, deshacer);
}

/**
 * Función para eliminar un contacto
 */
void eliminar(TablaHash ** agenda, AccList * deshacer) {
  buscar_eliminar_editar(agenda, 2, deshacer);
}

/**
 * Función para editar un contacto
 */
void editar(TablaHash ** agenda, AccList * deshacer) {
  buscar_eliminar_editar(agenda, 3, deshacer);
}

/**
 * Función que engloba los comportamientos de buscar, eliminar y editar
 */
void buscar_eliminar_editar(TablaHash ** agenda, int opcion, AccList * deshacer) {
  print_solicitud(1);
  char *nombre = malloc(sizeof(char) * MAX_NOMBRE);
  fgets(nombre, MAX_NOMBRE - 1, stdin);
  nombre[strlen(nombre) - 1] = '\0';

  print_solicitud(2);
  char *apellido = malloc(sizeof(char) * MAX_APELLIDO);
  fgets(apellido, MAX_APELLIDO - 1, stdin);
  apellido[strlen(apellido) - 1] = '\0';

  char *clave = malloc(sizeof(char) * MAX_CLAVE);
  sprintf(clave, "%s%s", nombre, apellido);

  Contacto contacto = tablahash_buscar(*agenda, clave, 0);

  // Procedo dependiendo de con qué función la llamé
  if (contacto) {
    if (opcion == 1)
      contacto_imprimir(contacto);
    else if (opcion == 2) {
      // Creo copias de los datos necesarios y añado un elemento a deshacer
      char *nombre_nuevo = malloc(sizeof(char) * MAX_NOMBRE);
      strcpy(nombre_nuevo, nombre);
      char *apellido_nuevo = malloc(sizeof(char) * MAX_APELLIDO);
      strcpy(apellido_nuevo, apellido);
      char *tel_nuevo = malloc(sizeof(char) * MAX_TEL);
      strcpy(tel_nuevo, contacto->telefono);
      int edad = contacto->edad;
      acciones_agregar(deshacer, 1, nombre_nuevo, apellido_nuevo, tel_nuevo,
                       NULL, edad, 0);
      
      tablahash_eliminar(*agenda, clave);
    } else if (opcion == 3) {
      // Paso los datos que cambiarán luego de editar
      char *tel_viejo = malloc(sizeof(char) * MAX_TEL);
      strcpy(tel_viejo, contacto->telefono);
      int edad_vieja = contacto->edad;

      editar_aux(agenda, clave, deshacer, contacto, tel_viejo, edad_vieja);
    }
  } else
    print_error(2);

  free(nombre);
  free(apellido);
  free(clave);
}

/**
 * Función que continúa con editar después de buscar_eliminar_editar
 */
void editar_aux(TablaHash ** agenda, char *clave, AccList * deshacer,
                Contacto contacto, char *tel_viejo, int edad_vieja) {
  print_solicitud(5);
  char *edad_str = malloc(sizeof(char) * MAX_NRO);
  fgets(edad_str, MAX_NRO - 1, stdin);
  int edad = atoi(edad_str);
  free(edad_str);

  print_solicitud(6);
  char *tel = malloc(sizeof(char) * MAX_TEL);
  fgets(tel, MAX_TEL - 1, stdin);
  tel[strlen(tel) - 1] = '\0';

  tablahash_editar(*agenda, clave, edad, tel);

  // Creo copias de los datos necesarios y
  char *nuevo_nombre = malloc(sizeof(char) * MAX_NOMBRE);
  strcpy(nuevo_nombre, contacto->nombre);
  char *nuevo_apellido = malloc(sizeof(char) * MAX_APELLIDO);
  strcpy(nuevo_apellido, contacto->apellido);

  char *nuevo_tel = malloc(sizeof(char) * MAX_TEL);
  strcpy(nuevo_tel, tel);

  // agrego una nueva acción para deshacer
  acciones_agregar(deshacer, 3, nuevo_nombre, nuevo_apellido, tel_viejo,
                   nuevo_tel, edad_vieja, edad);
}

/**
 * Función para agregar un contacto
 */
void agregar(TablaHash ** agenda, AccList * deshacer) {
  print_solicitud(1);
  char *nombre = malloc(sizeof(char) * MAX_NOMBRE);
  fgets(nombre, MAX_NOMBRE - 1, stdin);
  nombre[strlen(nombre) - 1] = '\0';

  print_solicitud(2);
  char *apellido = malloc(sizeof(char) * MAX_APELLIDO);
  fgets(apellido, MAX_APELLIDO - 1, stdin);
  apellido[strlen(apellido) - 1] = '\0';

  char *clave = malloc(sizeof(char) * MAX_CLAVE);
  sprintf(clave, "%s%s", nombre, apellido);

  // Si ya existía un contacto con ese nombre le aviso al usuario
  if (tablahash_buscar(*agenda, clave, 1)) {
    print_error(3);
    free(nombre);
    free(apellido);
    free(clave);
    return;
  }

  // Si no, lo agrego
  print_solicitud(3);
  char *edad_str = malloc(sizeof(char) * MAX_NRO);
  fgets(edad_str, MAX_NRO - 1, stdin);
  int edad = atoi(edad_str);
  free(edad_str);

  print_solicitud(4);
  char *telefono = malloc(sizeof(char) * MAX_TEL);
  fgets(telefono, MAX_TEL - 1, stdin);
  telefono[strlen(telefono) - 1] = '\0';

  Contacto contacto = contacto_crear(nombre, apellido, edad, telefono);

  // Creo copias de los datos necesarios para deshacer
  char *nombre_nuevo = malloc(sizeof(char) * MAX_NOMBRE);
  strcpy(nombre_nuevo, nombre);
  char *apellido_nuevo = malloc(sizeof(char) * MAX_APELLIDO);
  strcpy(apellido_nuevo, apellido);
  char *telefono_nuevo = malloc(sizeof(char) * MAX_TEL);
  strcpy(telefono_nuevo, telefono);

  *agenda = tablahash_insertar(*agenda, clave, contacto);

  // Agrego una nueva acción para deshacer
  acciones_agregar(deshacer, 2, nombre_nuevo, apellido_nuevo, telefono_nuevo,
                   NULL, edad, 0);
}

/**
 * Función que imprime los contactos que cumplen con todas los 
 * atributos ingresados por el usuario
 */
void and(TablaHash ** agenda) {
  and_or(agenda, 1);
}

/**
 * Función que imprime los contactos que cumplen con alguno
 * de los atributos ingresados por el usuario
 */
void or(TablaHash ** agenda) {
  and_or(agenda, 2);
}

/**
 * Función que engloba los comportamientos de and y or
 */
void and_or(TablaHash ** agenda, int funcion) {
  // Las banderas nos servirán para saber si el usuario
  // ingresó como vacío alguno de los atributos
  int nombre_band = 0;
  int apellido_band = 0;
  int tel_band = 0;
  int edad_band = 0;

  char *nombre = malloc(sizeof(char) * MAX_NOMBRE);
  print_solicitud(7);
  fgets(nombre, MAX_NOMBRE - 1, stdin);
  nombre[strlen(nombre) - 1] = '\0';
  if (strcmp(nombre, "") != 0) {
    nombre_band = 1;
  }

  char *apellido = malloc(sizeof(char) * MAX_APELLIDO);
  print_solicitud(8);
  fgets(apellido, MAX_APELLIDO - 1, stdin);
  apellido[strlen(apellido) - 1] = '\0';
  if (strcmp(apellido, "") != 0) {
    apellido_band = 1;
  }

  char *edad_str = malloc(sizeof(char) * MAX_NRO);
  print_solicitud(9);
  fgets(edad_str, MAX_NRO - 1, stdin);
  edad_str[strlen(edad_str) - 1] = '\0';
  if (strcmp(edad_str, "") != 0) {
    edad_band = 1;
  }
  int *edad_pointer = malloc(sizeof(int));
  *edad_pointer = atoi(edad_str);
  free(edad_str);

  char *tel = malloc(sizeof(char) * MAX_TEL);
  print_solicitud(10);
  fgets(tel, MAX_TEL - 1, stdin);
  tel[strlen(tel) - 1] = '\0';
  if (strcmp(tel, "") != 0) {
    tel_band = 1;
  }

  // Creo un puntero para pasar dentro de él todas las banderas
  int *bands = malloc(sizeof(int) * 4);
  bands[0] = nombre_band;
  bands[1] = apellido_band;
  bands[2] = edad_band;
  bands[3] = tel_band;

  // Llamo a la función de andor de la librería homónima
  andor(agenda, bands, nombre, apellido, edad_pointer, tel, funcion);

  free(bands);

  free(nombre);
  free(apellido);
  free(tel);
  free(edad_pointer);
}

/**
 * Función que carga a la agenda los contactos presentes en un archivo
 */
void cargar(TablaHash ** agenda) {
  print_solicitud(11);
  char *filename = malloc(sizeof(char) * MAX_FILE);
  fgets(filename, MAX_FILE - 1, stdin);
  filename[strlen(filename) - 1] = '\0';
  FILE *fp;
  fp = fopen(filename, "r+");
  if (fp == NULL) {
    print_error(4);
    free(filename);
    return;
  }

  char *primeralinea = malloc(sizeof(char) * FST_LINE_LEN);
  fscanf(fp, "%[^\n]\n", primeralinea);
  free(primeralinea);

  // Luego de leer la primera línea recorro todo el archivo 
  // agregando en la agenda los contactos que voy encontrando
  while (!feof(fp)) {
    char *nombre = malloc(sizeof(char) * MAX_NOMBRE);
    char *apellido = malloc(sizeof(char) * MAX_APELLIDO);
    char *edad_str = malloc(sizeof(char) * MAX_NRO);
    char *tel = malloc(sizeof(char) * MAX_TEL);

    fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n", nombre, apellido, edad_str, tel);
    int edad = atoi(edad_str);
    free(edad_str);

    char *clave = malloc(sizeof(char) * MAX_CLAVE);
    sprintf(clave, "%s%s", nombre, apellido);

    if (tablahash_buscar(*agenda, clave, 1)) {
      tablahash_eliminar(*agenda, clave);
    }

    Contacto contacto = contacto_crear(nombre, apellido, edad, tel);

    *agenda = tablahash_insertar(*agenda, clave, contacto);
  }

  free(filename);
  fclose(fp);
}

/**
 * Función que guarda todos los contactos presentes en la agenda 
 * en un archivo
 */
void guardar(TablaHash ** agenda) {
  print_solicitud(12);
  char *filename = malloc(sizeof(char) * MAX_FILE);
  fgets(filename, MAX_FILE - 1, stdin);
  filename[strlen(filename) - 1] = '\0';
  FILE *fp;
  fp = fopen(filename, "w+");
  if (fp == NULL) {
    print_error(4);
    free(filename);
    return;
  }
  fprintf(fp, "nombre,apellido,edad,telefono\n");
  tablahash_imprimir_file(*agenda, fp);

  free(filename);
  fclose(fp);
}

/**
 * Ídem guardar solo que lo hace de manera ordenada según 
 * el atributo ingresado por el usuario
 */
void guardar_ordenado(TablaHash ** agenda) {
  print_solicitud(12);
  char *filename = malloc(sizeof(char) * MAX_FILE);
  fgets(filename, MAX_FILE - 1, stdin);
  filename[strlen(filename) - 1] = '\0';

  print_solicitud(13);
  char *atributo = malloc(sizeof(char) * MAX_ATR);
  fgets(atributo, MAX_ATR - 1, stdin);
  atributo[strlen(atributo) - 1] = '\0';

  FILE *fp;
  fp = fopen(filename, "w+");
  if (fp == NULL) {
    print_error(4);
    free(filename);
    return;
  }

  fprintf(fp, "nombre,apellido,edad,telefono\n");

  if (!strcmp(atributo, "nombre"))
    tablahash_imprimir_inorder_nombre(*agenda, fp);

  else if (!strcmp(atributo, "apellido"))
    tablahash_imprimir_inorder_apellido(*agenda, fp);

  else if (!strcmp(atributo, "edad"))
    tablahash_imprimir_inorder_edad(*agenda, fp);

  else if (!strcmp(atributo, "telefono"))
    tablahash_imprimir_inorder_tel(*agenda, fp);

  else
    print_error(5);

  free(atributo);
  free(filename);
  fclose(fp);
}

/**
 * Imprime (si existe) un subconjunto de contactos tales que sus edades sumadas
 * den el número natural ingresado por el usuario
 */
void buscar_suma_edades(TablaHash ** agenda) {
  char *suma_str = malloc(sizeof(char) * MAX_NRO);
  print_solicitud(14);
  fgets(suma_str, MAX_NRO - 1, stdin);
  int suma = atoi(suma_str);
  //printf("suma = %d\n", suma);

  int n = (*agenda)->numElems;

  int *array_edades = calloc(n, sizeof(int));
  int *array_indices = calloc(n, sizeof(int));
  int *id = malloc(sizeof(int));
  *id = 0;

  // Convierto en arrays los datos que usaré para la búsqueda
  arbol_a_arrays((*agenda)->arbol_edad, array_edades, array_indices, id);

  // Llamo a la función que establece si existe un tal subconjunto
  // y lo imprime
  sbcjto_edad(array_edades, n, suma, array_indices, agenda);

  free(id);
  free(array_indices);
  free(array_edades);
  free(suma_str);
}

/**
 * Arma una tabla para establecer si existe un subconjunto de array_edades
 * que de sum y si esto sucede imprime uno.
 */
void sbcjto_edad(int *array_edades, int n, int sum, int *array_indices,
                 TablaHash ** agenda) {
  // Construyo una tabla subset.
  // El valor de subset[i][j] va a ser 1 si existe un subconjunto
  // de contactos de los que se encuentran en los índices de la tabla de
  // hash indicados por array_indices[0..i-1] tal que la suma de sus 
  // edades de j
  int **subset = malloc(sizeof(int *) * (n + 1));
  for (int i = 0; i <= n; i++) {
    subset[i] = calloc(sum + 1, sizeof(int));
  }

  // Para la columna 0 todas las entradas son 1
  // puesto que siempre existe el conjunto vacío
  for (int i = 0; i <= n; i++) {
    subset[i][0] = 1;
  }

  // Si no estoy en la columna 0, luego con 0
  // elementos no podemos llegar a sumar ninguna edad
  for (int i = 1; i <= sum; i++) {
    subset[0][i] = 0;
  }

  // Lleno el resto de la tabla de manera bottom-up
  // siguiendo el siguiente análisis:
  // 1- si la suma (columna) es más chica que la edad en 
  //    la que estamos (array_edades[fila-1]) me fijo si ya se
  //    pudo obtener esa suma y guardo el dato
  // 2- si lo anterior no sucede chequeo si se pudo obtener esa
  //    suma o si la puedo obtener añadiendo esta edad
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= sum; j++) {
      if (j < array_edades[i - 1]) {
        subset[i][j] = subset[i - 1][j];
      }
      if (j >= array_edades[i - 1]) {
        subset[i][j] = subset[i - 1][j]
            || subset[i - 1][j - array_edades[i - 1]];
      }
    }
  }

  // Una vez completada la tabla compruebo el resultado
  int band = 1;

  if (!subset[n][sum]) {
    print_error(6);
    band = 0;
  }

  // Si se puede obtener un conjunto deseado, imprimo uno
  // haciendo backtracking
  if (band) {
    int new_sum = sum;
    int i = n;
    // Recorro por la longitud de los arrays
    while (i > 0 && (new_sum != 0)) {
      // Si no puedo ignorar la edad porque fue necesaria para la
      // construcción de la new_sum actual la imprimo y establezco
      // la new_sum actual como la anterior menos esta edad necesaria
      if (!subset[i - 1][new_sum]) {
        int idx = array_indices[i - 1];
        contacto_imprimir((*agenda)->tabla[idx].dato);
        new_sum = new_sum - array_edades[i - 1];
      }
      i--;
    }
  }

  for (int i = 0; i <= n; i++) {
    free(subset[i]);
  }
  free(subset);
}

/**
 * Deshace o rehace la última acción de la lista de acciones pasada
 * la elimina de la misma y agrega la acción opuesta a la lista opuesta
 * también pasada
 */
void undo_redo(TablaHash ** agenda, AccList * acclist,
               AccList * opuesta_acclist) {
  Accion *accion = acclist->tail->dato;

  // Si debo agregar 
  if (accion->tipo == 1) {
    // Realizo la inserción
    char *nombre_agg = malloc(sizeof(char) * MAX_NOMBRE);
    strcpy(nombre_agg, accion->nombre);
    char *apellido_agg = malloc(sizeof(char) * MAX_APELLIDO);
    strcpy(apellido_agg, accion->apellido);
    char *tel_agg = malloc(sizeof(char) * MAX_TEL);
    strcpy(tel_agg, accion->tel[0]);

    char *clave_agg = malloc(sizeof(char) * MAX_CLAVE);
    sprintf(clave_agg, "%s%s", nombre_agg, apellido_agg);
    Contacto contacto =
        contacto_crear(nombre_agg, apellido_agg, accion->edad[0], tel_agg);
    *agenda = tablahash_insertar(*agenda, clave_agg, contacto);
  }
  // Si debo eliminar o editar
  else if (accion->tipo == 2 || accion->tipo == 3) {
    char *nombre = malloc(sizeof(char) * MAX_NOMBRE);
    strcpy(nombre, accion->nombre);
    char *apellido = malloc(sizeof(char) * MAX_APELLIDO);
    strcpy(apellido, accion->apellido);

    char *clave = malloc(sizeof(char) * MAX_CLAVE);
    sprintf(clave, "%s%s", nombre, apellido);

    Contacto contacto = tablahash_buscar(*agenda, clave, 0);
    if (contacto) {
      // Elimino o
      if (accion->tipo == 2)
        tablahash_eliminar(*agenda, clave);

      // Edito
      else {
        char *nuevo_tel = malloc(sizeof(char) * MAX_TEL);
        strcpy(nuevo_tel, accion->tel[0]);
        int nueva_edad = accion->edad[0];
        tablahash_editar(*agenda, clave, nueva_edad, nuevo_tel);
      }
    } else
      print_error(2);
    free(nombre);
    free(apellido);
    free(clave);
  }
  // Agrego la acción opuesta a la lista opuesta
  agregar_opuesto_des_re(accion, opuesta_acclist);
  // Elimino la acción de la lista
  acciones_eliminar_final(acclist);
}