#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "contacto.h"

/**
 * Crea un nuevo contacto.
 */
Contacto contacto_crear(char* nombre, char* apellido, unsigned edad, char* telefono) {
  Contacto nuevo = malloc(sizeof(Contact));
  assert(nuevo != NULL);

  nuevo->nombre = nombre;

  nuevo->apellido = apellido;

  nuevo->telefono = telefono;

  nuevo->edad = edad;

  return nuevo;
}

/**
 * Destruye un contacto.
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
 * Imprime por pantalla un contacto.
 */
void contacto_imprimir(Contacto contacto) {
  if (contacto) {
    printf("{%s,%s,%d,%s}\n", contacto->nombre, contacto->apellido, contacto->edad, contacto->telefono);
  }
  else {
    printf("NULL\n");
  }
}

/*int main() {
    char* nombre = malloc(sizeof(char)*5);
    nombre[0] = 'p';
    nombre[1] = 'e';
    nombre[2] = 'p';
    nombre[3] = 'e';
    nombre[4] = '\0';
    char* apellido = malloc(sizeof(char)*6);
    apellido[0] = 'p';
    apellido[1] = 'e';
    apellido[2] = 'r';
    apellido[3] = 'e';
    apellido[4] = 'z';
    apellido[5] = '\0';
    char* telefono = malloc(sizeof(char)*4);
    telefono[0] = '1';
    telefono[1] = '2';
    telefono[2] = '3';
    telefono[3] = '\0';
    unsigned edad = 3; 
    Contacto p = contacto_crear(nombre, apellido, edad, telefono);
    contacto_imprimir(p);
    contacto_destruir(p);

    return 0;
}*/