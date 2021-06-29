#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__

#include <stddef.h>
#include "andor.h"
#include "acciones.h"
#include "impresiones.h"

/* Función que maneja la parte interactiva del programa */
int interpretar(TablaHash ** dicc, char *accion, AccList * deshacer,
                AccList * rehacer);

/* Funciones relativas a las acciones del intérprete */

void buscar(TablaHash ** dicc, AccList * deshacer);

void eliminar(TablaHash ** dicc, AccList * deshacer);

void editar(TablaHash ** dicc, AccList * deshacer);

void editar_aux(TablaHash ** agenda, char *clave, AccList * deshacer,
                Contacto contacto, char *tel_viejo, int edad_vieja);

void buscar_eliminar_editar(TablaHash ** dicc, int opcion, AccList * deshacer);

void agregar(TablaHash ** dicc, AccList * deshacer);

void undo_redo(TablaHash ** agenda, AccList * acclist,
               AccList * opuesta_acclist);

void and(TablaHash ** agenda);

void or(TablaHash ** agenda);

void and_or(TablaHash ** agenda, int funcion);

void cargar(TablaHash ** agenda);

void guardar(TablaHash ** agenda);

void guardar_ordenado(TablaHash ** agenda);

void buscar_suma_edades(TablaHash ** agenda);

void sbcjto_edad(int *array_edades, int n, int sum, int *array_indices,
                 TablaHash ** agenda);


#endif                          /* __INTERPRETE_H__ */
