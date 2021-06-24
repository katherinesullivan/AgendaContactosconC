#include "interprete.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NOMBRE 32
#define MAX_APELLIDO 32
#define MAX_TEL 32
#define MAX_CLAVE MAX_NOMBRE+MAX_APELLIDO
#define MAX_NRO 9


/************************** Intérprete ********************************/

int interpretar(TablaHash ** dicc, char* accion) {
    print_solicitud(0);
    fgets(accion, MAX_NRO, stdin);
    int nro_accion = atoi(accion);

    if (nro_accion == 1) {
        buscar(dicc);
        return 1;
    }

    if (nro_accion == 2) {
        agregar(dicc); // y los árboles
        return 1;
    }

    if (nro_accion == 3) {
        eliminar(dicc); // y los árboles
        return 1;
    }

    if (nro_accion == 13) {
        print_salida();
        prettyprint_th(*dicc);
        tablahash_destruir(*dicc);
        return 0;
    }

    else {
        print_error(1);
        return 1;
    }
}


/************************** Acciones ********************************/

void buscar(TablaHash** dicc) {
    buscar_o_eliminar(dicc, 1);
}

void eliminar(TablaHash** dicc) {
    buscar_o_eliminar(dicc, 2);
}

void buscar_o_eliminar(TablaHash** dicc, int opcion)  {
    print_solicitud(1);
    char* nombre = malloc(sizeof(char)*MAX_NOMBRE);
    fgets(nombre, MAX_NOMBRE-1, stdin);
    nombre[strlen(nombre)-1] = '\0';

    print_solicitud(2);
    char* apellido = malloc(sizeof(char)*MAX_APELLIDO);
    fgets(apellido, MAX_APELLIDO-1, stdin);
    apellido[strlen(apellido)-1] = '\0';

    char* clave = malloc(sizeof(char)*MAX_CLAVE);
    sprintf(clave, "%s%s", nombre, apellido);

    Contacto contacto = tablahash_buscar(*dicc, clave, 0);
    if (contacto) {
        if (opcion == 1) contacto_imprimir(contacto);
        else if (opcion == 2) tablahash_eliminar(*dicc, clave); // modificar para que tmb haga eliminacion en los árboles
        else printf("Opción inválida");
    }
    else print_error(2);

    free(nombre);
    free(apellido);
    free(clave);
}

void agregar(TablaHash** dicc) { // Y ÁRBOLES

    print_solicitud(1);
    char* nombre = malloc(sizeof(char)*MAX_NOMBRE);
    fgets(nombre, MAX_NOMBRE-1, stdin);
    nombre[strlen(nombre)-1] = '\0';

    print_solicitud(2);
    char* apellido = malloc(sizeof(char)*MAX_APELLIDO);
    fgets(apellido, MAX_APELLIDO-1, stdin);
    apellido[strlen(apellido)-1] = '\0';

    char* clave = malloc(sizeof(char)*MAX_CLAVE);
    sprintf(clave, "%s%s", nombre, apellido);

    if (tablahash_buscar(*dicc, clave, 1)) {
        print_error(3);
        return;
    } 

    print_solicitud(3);
    char* telefono = malloc(sizeof(char)*MAX_TEL);
    fgets(telefono, MAX_TEL-1, stdin);
    telefono[strlen(telefono)-1] = '\0';

    print_solicitud(4);
    char* edad_str = malloc(sizeof(char)*MAX_NRO);
    fgets(edad_str, MAX_NRO-1, stdin);
    int edad = atoi(edad_str);
    free(edad_str);

    Contacto contacto = contacto_crear(nombre, apellido, edad, telefono);

    tablahash_insertar(*dicc, clave, contacto);

    // AGREGAR A LOS ÁRBOLES CON IDX ya que nunca cambio ese cdo agrando la tabla y solo espero que matcheen las claves

}



/************************** Impresiones ********************************/

void print_salida() {
    printf("Cerrando programa\n");
}

void print_solicitud(int tipo) {

    if (tipo == 0) {
        printf("\nSeleccione una acción:\n>");
        return;
    }

    if (tipo == 1) {
        printf("Ingrese nombre:\n");
        return;
    }

    if (tipo == 2) {
        printf("Ingrese apellido:\n");
        return;
    }

    if (tipo == 3) {
        printf("Ingrese teléfono:\n");
        return;
    }

    if (tipo == 4) {
        printf("Ingrese edad:\n");
        return;
    }

    else printf("Solicitud imposible de imprimir\n");
}

void print_error(int tipo) {
    if (tipo == 1) {
        printf("Selección inválida. ");
        printf("Observe cuáles son los números de acciones permitidas.\n");
        return;
    }

    if (tipo == 2) {
        printf("No existe contacto con tal nombre y apellido en la agenda\n");
        return;
    }

    if (tipo == 3) {
        printf("No se puede agregar un contacto con tal nombre y apellido ");
        printf("puesto que ya existe uno así.\n");
        printf("Intente volver a agregarlo con nombre o apellido distintos ");
        printf("o elimine el contacto que ya tiene.\n");
        return;
    }

    else printf("Error imposible de imprimir\n");

}