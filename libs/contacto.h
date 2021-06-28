#ifndef __CONTACTO_H__
#define __CONTACTO_H__

#include <stddef.h>

struct _Contact {
  char *nombre;
  char *apellido;
  unsigned edad;
  char *telefono;
} Contact;

typedef struct _Contact *Contacto;

Contacto contacto_crear(char *nombre, char *apellido, unsigned edad,
                        char *telefono);

void contacto_destruir(Contacto contacto);

void contacto_imprimir(Contacto contacto);

void contacto_imprimir_file(Contacto contacto, FILE * fp);

#endif                          /* __CONTACTO_H__ */
