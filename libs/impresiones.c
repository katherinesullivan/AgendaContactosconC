#include <stdio.h>
#include "impresiones.h"

/**
 * Imprime el menú de acciones
 */
void print_menu_acciones() {
  printf("Menú de acciones:\n");

  printf("1. Buscar\n");
  printf("2. Agregar\n");
  printf("3. Eliminar\n");
  printf("4. Editar\n");
  printf("5. Cargar\n");
  printf("6. Guardar\n");
  printf("7. Deshacer\n");
  printf("8. Rehacer\n");
  printf("9. AND\n");
  printf("10. OR\n");
  printf("11. Guardar ordenado\n");
  printf("12. Buscar por suma de edades\n");
  printf("13. Salir\n");
}

/**
 * Imprime un mensaje para la salida
 */
void print_salida() {
  printf("Cerrando programa\n");
}

/**
 * Función para la impresión de solicitudes al usuario
 */
void print_solicitud(int tipo) {

  if (tipo == 0) {
    printf("\nSeleccione una acción:\n>");
    return;
  }

  if (tipo == 1) {
    printf("Ingrese nombre:\n>");
    return;
  }

  if (tipo == 2) {
    printf("Ingrese apellido:\n>");
    return;
  }

  if (tipo == 3) {
    printf("Ingrese edad:\n>");
    return;
  }

  if (tipo == 4) {
    printf("Ingrese teléfono:\n>");
    return;
  }

  if (tipo == 5) {
    printf("Ingrese nueva edad:\n>");
    return;
  }

  if (tipo == 6) {
    printf("Ingrese nuevo teléfono:\n>");
    return;
  }

  if (tipo == 7) {
    printf("Ingrese un nombre a buscar:\n>");
    return;
  }

  if (tipo == 8) {
    printf("Ingrese un apellido a buscar:\n>");
    return;
  }

  if (tipo == 9) {
    printf("Ingrese una edad a buscar:\n>");
    return;
  }

  if (tipo == 10) {
    printf("Ingrese un teléfono a buscar:\n>");
    return;
  }

  if (tipo == 11) {
    printf("Ingrese ruta de entrada:\n>");
    return;
  }

  if (tipo == 12) {
    printf("Ingrese ruta de salida:\n>");
    return;
  }

  if (tipo == 13) {
    printf("Ingrese nombre de atributo:\n>");
    return;
  }

  if (tipo == 14) {
    printf("Ingrese un natural:\n>");
    return;
  }

  else
    printf("Solicitud imposible de imprimir\n");
}

/**
 * Función para imprimir errores
 */
void print_error(int tipo) {
  if (tipo == 1) {
    printf("Selección inválida. ");
    printf("Observe cuáles son los números de acciones permitidas.\n");
    return;
  }

  if (tipo == 2) {
    printf("No se pudo realizar la acción. ");
    printf("No existe contacto con tal nombre y apellido en la agenda.\n");
    return;
  }

  if (tipo == 3) {
    printf("No se puede agregar un contacto con tal nombre y apellido ");
    printf("puesto que ya existe uno así.\n");
    printf("Intente volver a agregarlo con nombre o apellido distintos ");
    printf("o elimine el contacto que ya tiene.\n");
    return;
  }

  if (tipo == 4) {
    printf("No se pudo abrir el archivo.\n");
    return;
  }

  if (tipo == 5) {
    printf("Atributo inválido. ");
    printf("Los atributos permitidos son: ");
    printf("nombre, apellido, edad y telefono.\n");
    return;
  }

  if (tipo == 6) {
    printf("No existe subconjunto de contactos cuyas edades ");
    printf("sumadas den el natural propuesto.\n");
    return;
  }

  if (tipo == 7) {
    printf("Nada por deshacer.\n");
    return;
  }

  if (tipo == 8) {
    printf("Nada por rehacer.\n");
    return;
  }

  else
    printf("Error imposible de imprimir\n");

}
