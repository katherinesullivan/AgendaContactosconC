#ifndef __IMPRESIONES_H__
#define __IMPRESIONES_H__

#include <stddef.h>

/**
 * Imprime el menú de acciones
 */
void print_menu_acciones();

/**
 * Imprime un mensaje para la salida
 */
void print_salida();

/**
 * Función para la impresión de solicitudes al usuario
 */
void print_solicitud(int tipo);

/**
 * Función para imprimir errores
 */
void print_error(int tipo);

#endif                          /* __IMPRESIONES_H__ */
