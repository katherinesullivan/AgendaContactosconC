#ifndef __CONTACTO_H__
#define __CONTACTO_H__

#include <stddef.h>

/** 
 * Estructura para contacto
 */
struct _Contact {
  char *nombre;
  char *apellido;
  unsigned edad;
  char *telefono;
} Contact;

typedef struct _Contact *Contacto;

/**
 * Crea un nuevo contacto
 */
Contacto contacto_crear(char *nombre, char *apellido, unsigned edad,
                        char *telefono);

/**
 * Destruye un contacto
 */
void contacto_destruir(Contacto contacto);

/**
 * Imprime por pantalla un contacto
 */
void contacto_imprimir(Contacto contacto);

/**
 * Imprime un contacto en un archivo
 */
void contacto_imprimir_file(Contacto contacto, FILE * fp);

#endif                          /* __CONTACTO_H__ */
