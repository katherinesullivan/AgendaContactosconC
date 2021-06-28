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

int interpretar(TablaHash ** agenda, char *accion) {
  print_solicitud(0);
  fgets(accion, MAX_NRO, stdin);
  int nro_accion = atoi(accion);

  if (nro_accion == 1) {
    buscar(agenda);
    return 1;
  }

  if (nro_accion == 2) {
    agregar(agenda);            // y los árboles
    return 1;
  }

  if (nro_accion == 3) {
    eliminar(agenda);           // y los árboles
    return 1;
  }

  if (nro_accion == 4) {
    editar(agenda);             // y los árboles
    return 1;
  }

  if (nro_accion == 5) {
    cargar(agenda);
    return 1;
  }

  if (nro_accion == 6) {
    guardar(agenda);
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
    prettyprint_th(*agenda);
    tablahash_destruir(*agenda);
    return 0;
  }

  else {
    print_error(1);
    return 1;
  }
}


/************************** Acciones ********************************/

void buscar(TablaHash ** agenda) {
  buscar_eliminar_editar(agenda, 1);
}

void eliminar(TablaHash ** agenda) {
  buscar_eliminar_editar(agenda, 2);
}

void editar(TablaHash ** agenda) {
  buscar_eliminar_editar(agenda, 3);
}

void editar_aux(TablaHash ** agenda, char *clave) {
  print_solicitud(5);
  char *edad_str = malloc(sizeof(char) * MAX_NRO);
  fgets(edad_str, MAX_NRO - 1, stdin);
  int edad = atoi(edad_str);
  free(edad_str);

  print_solicitud(6);
  char *tel = malloc(sizeof(char) * MAX_TEL);
  fgets(tel, MAX_TEL - 1, stdin);
  tel[strlen(tel) - 1] = '\0';

  // HACER CAMBIOS EN ARBOLES TMB
  void *rdo = tablahash_editar(*agenda, clave, edad, tel);

  // Podría borrar pq si entro acá es pq ya me fije que estuviese
  if (rdo == NULL) {
    free(tel);
    print_error(2);
  }
}

void buscar_eliminar_editar(TablaHash ** agenda, int opcion) {
  if ((*agenda)->numElems == (*agenda)->capacidad) {
    print_aviso_capacidad(1);
    return;
  }

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
  if (contacto) {
    if (opcion == 1)
      contacto_imprimir(contacto);
    else if (opcion == 2)
      tablahash_eliminar(*agenda, clave);       // modificar para que tmb haga eliminacion en los árboles
    else if (opcion == 3)
      editar_aux(agenda, clave);
    else
      printf("Opción inválida");
  } else
    print_error(2);

  free(nombre);
  free(apellido);
  free(clave);
}

void agregar(TablaHash ** agenda) {
  if ((*agenda)->numElems == (*agenda)->capacidad) {
    print_aviso_capacidad(1);
    return;
  }

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

  if (tablahash_buscar(*agenda, clave, 1)) {
    print_error(3);
    free(nombre);
    free(apellido);
    free(clave);
    return;
  }

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

  *agenda = tablahash_insertar(*agenda, clave, contacto);

}

void and(TablaHash ** agenda) {
  and_or(agenda, 1);
}

void or(TablaHash ** agenda) {
  and_or(agenda, 2);
}

void and_or(TablaHash ** agenda, int funcion) {
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

  int *bands = malloc(sizeof(int) * 4);
  bands[0] = nombre_band;
  bands[1] = apellido_band;
  bands[2] = edad_band;
  bands[3] = tel_band;

  andor(agenda, bands, nombre, apellido, edad_pointer, tel, funcion);

  free(bands);

  free(nombre);
  free(apellido);
  free(tel);
  free(edad_pointer);
}

void cargar(TablaHash ** agenda) {
  if ((*agenda)->numElems == (*agenda)->capacidad) {
    print_aviso_capacidad(1);
    return;
  }

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
  int i = 0;
  int band = 1;

  while (!feof(fp) && band) {

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
    i++;

    if ((*agenda)->numElems == (*agenda)->capacidad) {
      printf("Se pudieron cargar los primeros %d contactos\n", i);
      print_aviso_capacidad(1);
      band = 0;
    }
  }

  free(filename);
  fclose(fp);
}

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

void guardar_ordenado(TablaHash ** agenda) {
  print_solicitud(12);
  char *filename = malloc(sizeof(char) * MAX_FILE);
  fgets(filename, MAX_FILE - 1, stdin);
  filename[strlen(filename) - 1] = '\0';

  print_solicitud(13);
  char *atributo = malloc(sizeof(char) * MAX_ATR);
  fgets(atributo, MAX_ATR - 1, stdin);
  atributo[strlen(atributo) - 1] = '\0';
  printf("%s", atributo);

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

/*int contar_lineas (FILE *fp) {
  int count = 0;
  char c;
  // Recorro el archivo caracter por caracter contando líneas
  for (c = getc(fp); c != EOF; c = getc(fp)) {
    if (c == '\n') {
      count++;
    }
  }
  // Una vez llegado al end of file, hago que el puntero al archivo 
  // vuelva a estar al principio del mismo
  rewind(fp);

  // Y devuelvo el contador
  return count;
}*/

void buscar_suma_edades(TablaHash ** agenda) {
  char *suma_str = malloc(sizeof(char) * MAX_NRO);
  print_solicitud(14);
  fgets(suma_str, MAX_NRO - 1, stdin);
  int suma = atoi(suma_str);

  int n = (*agenda)->numElems;

  int *array_edades = calloc(n, sizeof(int));
  int *array_indices = calloc(n, sizeof(int));
  printf("suma = %d\n", suma);
  int *id = malloc(sizeof(int));
  *id = 0;

  arbol_a_arrays((*agenda)->arbol_edad, array_edades, array_indices, id);

  for (int i = 0; i < n; i++) {
    printf("array_edades[%d]: %d\n", i, array_edades[i]);
    printf("array_indices[%d]: %d\n", i, array_indices[i]);
  }


  sbcjto_edad(array_edades, n, suma, array_indices, agenda);

  free(id);
  free(array_indices);
  free(array_edades);
  free(suma_str);
}

void sbcjto_edad(int *array_edades, int n, int sum, int *array_indices,
                 TablaHash ** agenda) {
  // The value of subset[i][j] will be true if
  // there is a subset of array_edades[0..j-1] with sum
  // equal to i
  int **subset = malloc(sizeof(int *) * (n + 1));
  for (int i = 0; i <= n; i++) {
    subset[i] = calloc(sum + 1, sizeof(int));
  }
  //int subset[n + 1][sum + 1];

  // If sum is 0, then answer is true
  for (int i = 0; i <= n; i++) {
    subset[i][0] = 1;
  }

  // If sum is not 0 and array_edades is empty,
  // then answer is false
  for (int i = 1; i <= sum; i++) {
    subset[0][i] = 0;
  }

  // Fill the subset table in botton up manner
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

  int band = 1;

  if (!subset[n][sum]) {
    print_error(6);
    band = 0;
  }
  // uncomment this code to print table
  printf("   0   1   2   3   4   5   6   7   8   9\n");
  printf("-----------------------------------------\n");
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= sum; j++)
      printf("%4d", subset[i][j]);
    printf("\n");
  }

  if (band) {
    int new_sum = sum;
    int i = n;
    /*for (;i > 0; i--) {
       printf("i is equal to %d\n", i);
       if (!subset[i-1][new_sum]) {
       printf("%d\n", array_edades[i-1]);
       new_sum = new_sum - array_edades[i-1];
       }
       } */
    while (i > 0 && (new_sum != 0)) {
      if (!subset[i - 1][new_sum]) {
        printf("%d\n", array_edades[i - 1]);
        printf("En indice: %d\n", array_indices[i - 1]);
        int idx = array_indices[i - 1];
        contacto_imprimir((*agenda)->tabla[idx].dato);
        new_sum = new_sum - array_edades[i - 1];
      }
      i--;
    }
    if (new_sum < 0) {
      printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
    }
  }

  for (int i = 0; i <= n; i++) {
    free(subset[i]);
  }
  free(subset);

  //return subset[n][sum];
}


/************************** Impresiones ********************************/

void print_salida() {
  printf("Cerrando programa\n");
}

void print_aviso_capacidad(int tipo) {
  if (tipo == 1) {
    printf("Agenda llena. No fue posible realizar la acción solicitada. ");
    printf("Guarde sus datos e inicie una nueva agenda ");
    printf("con mayor capacidad y cargue sus datos actuales.\n");
  } else if (tipo == 2) {
    printf("Su agenda está llegando a un nivel crítico en su capacidad. ");
    printf("Esto ralentiza sus operaciones. Considere guardar sus datos ");
    printf("en un archivo e inicializar una nueva agenda con mayor ");
    printf("capacidad donde los puede cargar automáticamente.\n");
  }
}

void print_solicitud(int tipo) {

  if (tipo == 0) {
    printf("\nSeleccione una acción:\n>");
    return;
  }

  if (tipo == 1) {
    printf("Ingrese nombre:\n>");
    return;
  }

  if (tipo == 2) {
    printf("Ingrese apellido:\n>");
    return;
  }

  if (tipo == 3) {
    printf("Ingrese edad:\n>");
    return;
  }

  if (tipo == 4) {
    printf("Ingrese teléfono:\n>");
    return;
  }

  if (tipo == 5) {
    printf("Ingrese nueva edad:\n>");
    return;
  }

  if (tipo == 6) {
    printf("Ingrese nuevo teléfono:\n>");
    return;
  }

  if (tipo == 7) {
    printf("Ingrese un nombre a buscar:\n>");
    return;
  }

  if (tipo == 8) {
    printf("Ingrese un apellido a buscar:\n>");
    return;
  }

  if (tipo == 9) {
    printf("Ingrese una edad a buscar:\n>");
    return;
  }

  if (tipo == 10) {
    printf("Ingrese un teléfono a buscar:\n>");
    return;
  }

  if (tipo == 11) {
    printf("Ingrese ruta de entrada:\n>");
    return;
  }

  if (tipo == 12) {
    printf("Ingrese ruta de salida:\n>");
    return;
  }

  if (tipo == 13) {
    printf("Ingrese nombre de atributo:\n>");
    return;
  }

  if (tipo == 14) {
    printf("Ingrese un natural:\n>");
    return;
  }

  else
    printf("Solicitud imposible de imprimir\n");
}

void print_error(int tipo) {
  if (tipo == 1) {
    printf("Selección inválida. ");
    printf("Observe cuáles son los números de acciones permitidas.\n");
    return;
  }

  if (tipo == 2) {
    printf("No existe contacto con tal nombre y apellido en la agenda.\n");
    return;
  }

  if (tipo == 3) {
    printf("No se puede agregar un contacto con tal nombre y apellido ");
    printf("puesto que ya existe uno así.\n");
    printf("Intente volver a agregarlo con nombre o apellido distintos ");
    printf("o elimine el contacto que ya tiene.\n");
    return;
  }

  if (tipo == 4) {
    printf("No se pudo abrir el archivo.\n");
    return;
  }

  if (tipo == 5) {
    printf("Atributo inválido. ");
    printf("Los atributos permitidos son: ");
    printf("nombre, apellido, edad y telefono.\n");
    return;
  }

  if (tipo == 6) {
    printf("No existe subconjunto de contactos cuyas edades ");
    printf("sumadas den el natural propuesto.\n");
    return;
  }

  else
    printf("Error imposible de imprimir\n");

}
