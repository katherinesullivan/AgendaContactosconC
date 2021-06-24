#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__

#include <stddef.h>
#include "tablahash.h"
#include "contacto.h"

/* Función que maneja la parte interactiva del programa */
int interpretar(TablaHash** dicc, char* accion);

/* Funciones relativas a las acciones del intérprete */

void buscar(TablaHash** dicc);

void eliminar(TablaHash** dicc);

void buscar_o_eliminar(TablaHash** dicc, int opcion);

void agregar(TablaHash** dicc);

/* Funciones relativas a la impresión de mensajes del intérprete */

void print_salida();

void print_solicitud(int tipo);

void print_error(int tipo);




#endif                          /* __INTERPRETE_H__ */