#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "contacto.h"

/**
 * Crea un nuevo contacto
 */
Contacto contacto_crear(char *nombre, char *apellido, unsigned edad,
                        char *telefono) {
  Contacto nuevo = malloc(sizeof(Contact));
  assert(nuevo != NULL);

  nuevo->nombre = nombre;

  nuevo->apellido = apellido;

  nuevo->telefono = telefono;

  nuevo->edad = edad;

  return nuevo;
}

/**
 * Destruye un contacto
 */
void contacto_destruir(Contacto contacto) {
  if (contacto) {
    free(contacto->nombre);
    free(contacto->apellido);
    free(contacto->telefono);
    free(contacto);
  }
}

/**
 * Imprime por pantalla un contacto
 */
void contacto_imprimir(Contacto contacto) {
  if (contacto) {
    printf("{%s,%s,%d,%s}\n", contacto->nombre, contacto->apellido,
           contacto->edad, contacto->telefono);
  } else {
    printf("NULL\n");
  }
}

/**
 * Imprime un contacto en un archivo
 */
void contacto_imprimir_file(Contacto contacto, FILE * fp) {
  if (contacto) {
    fprintf(fp, "%s,%s,%d,%s\n", contacto->nombre, contacto->apellido,
            contacto->edad, contacto->telefono);
  }
}
