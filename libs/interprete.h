#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__

#include <stddef.h>
#include "andor.h"
#include "acciones.h"
#include "impresiones.h"

/**
 * Función principal. 
 * Decide a qué función llamar dependiendo de la entrada del usuario
 */
int interpretar(TablaHash ** dicc, char *accion, AccList * deshacer,
                AccList * rehacer);

/* Funciones relativas a las acciones del intérprete */

/**
 * Función para buscar un contacto
 */
void buscar(TablaHash ** dicc, AccList * deshacer);

/**
 * Función para eliminar un contacto
 */
void eliminar(TablaHash ** dicc, AccList * deshacer);

/**
 * Función para editar un contacto
 */
void editar(TablaHash ** dicc, AccList * deshacer);

/**
 * Función que engloba los comportamientos de buscar, eliminar y editar
 */
void editar_aux(TablaHash ** agenda, char *clave, AccList * deshacer,
                Contacto contacto, char *tel_viejo, int edad_vieja);

/**
 * Función que continúa con editar después de buscar_eliminar_editar
 */
void buscar_eliminar_editar(TablaHash ** dicc, int opcion, AccList * deshacer);

/**
 * Función para agregar un contacto
 */
void agregar(TablaHash ** dicc, AccList * deshacer);



/**
 * Función que imprime los contactos que cumplen con todas los 
 * atributos ingresados por el usuario
 */
void and(TablaHash ** agenda);

/**
 * Función que imprime los contactos que cumplen con alguno
 * de los atributos ingresados por el usuario
 */
void or(TablaHash ** agenda);

/**
 * Función que engloba los comportamientos de and y or
 */
void and_or(TablaHash ** agenda, int funcion);

/**
 * Función que carga a la agenda los contactos presentes en un archivo
 */
void cargar(TablaHash ** agenda);

/**
 * Función que guarda todos los contactos presentes en la agenda 
 * en un archivo
 */
void guardar(TablaHash ** agenda);

/**
 * Ídem guardar solo que lo hace de manera ordenada según 
 * el atributo ingresado por el usuario
 */
void guardar_ordenado(TablaHash ** agenda);

/**
 * Imprime (si existe) un subconjunto de contactos tales que sus edades sumadas
 * den el número natural ingresado por el usuario
 */
void buscar_suma_edades(TablaHash ** agenda);

/**
 * Arma una tabla para establecer si existe un subconjunto de array_edades
 * que de sum y si esto sucede imprime uno.
 */
void sbcjto_edad(int *array_edades, int n, int sum, int *array_indices,
                 TablaHash ** agenda);
                 
/**
 * Deshace o rehace la última acción de la lista de acciones pasada
 * la elimina de la misma y agrega la acción opuesta a la lista opuesta
 * también pasada
 */
void undo_redo(TablaHash ** agenda, AccList * acclist,
               AccList * opuesta_acclist);

#endif                          /* __INTERPRETE_H__ */
