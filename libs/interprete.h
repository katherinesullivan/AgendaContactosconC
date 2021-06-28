#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__

#include <stddef.h>
#include "andor.h"

/* Función que maneja la parte interactiva del programa */
int interpretar(TablaHash** dicc, char* accion);

/* Funciones relativas a las acciones del intérprete */

void buscar(TablaHash** dicc);

void eliminar(TablaHash** dicc);

void editar(TablaHash** dicc);

void editar_aux(TablaHash** dicc, char* clave);

void buscar_eliminar_editar(TablaHash** dicc, int opcion);

void agregar(TablaHash** dicc);

void and(TablaHash** agenda);

void or(TablaHash** agenda);

void and_or(TablaHash** agenda, int funcion);

void cargar(TablaHash** agenda);

void guardar(TablaHash** agenda);

void guardar_ordenado(TablaHash** agenda);

void buscar_suma_edades(TablaHash** agenda);

void sbcjto_edad(int* array_edades, int n, int sum, int* array_indices, TablaHash** agenda);

/* Funciones relativas a la impresión de mensajes del intérprete */

void print_salida();

void print_solicitud(int tipo);

void print_error(int tipo);




#endif                          /* __INTERPRETE_H__ */