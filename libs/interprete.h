#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__

#include <stddef.h>
#include "tablahash.h"
#include "contacto.h"

/* Función que maneja la parte interactiva del programa */
int interpretar(TablaHash** dicc, int* accion);

#endif                          /* __INTERPRETE_H__ */