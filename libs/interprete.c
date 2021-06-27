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

int interpretar(TablaHash ** agenda, char* accion) {
    print_solicitud(0);
    fgets(accion, MAX_NRO, stdin);
    int nro_accion = atoi(accion);

    if (nro_accion == 1) {
        buscar(agenda);
        return 1;
    }

    if (nro_accion == 2) {
        agregar(agenda); // y los árboles
        return 1;
    }

    if (nro_accion == 3) {
        eliminar(agenda); // y los árboles
        return 1;
    }

    if (nro_accion == 4) {
        editar(agenda); // y los árboles
        return 1;
    }

    if (nro_accion == 9) {
        and(agenda);
        return 1;
    }

    if (nro_accion == 10) {
        or(agenda);
        return 1;
    }

    if (nro_accion == 13) {
        print_salida();
        prettyprint_th(*agenda);
        tablahash_destruir(*agenda);
        return 0;
    }

    else {
        print_error(1);
        return 1;
    }
}


/************************** Acciones ********************************/

void buscar(TablaHash** agenda) {
    buscar_eliminar_editar(agenda, 1);
}

void eliminar(TablaHash** agenda) {
    buscar_eliminar_editar(agenda, 2);
}

void editar(TablaHash** agenda) {
    buscar_eliminar_editar(agenda, 3);
}

void editar_aux(TablaHash** agenda, char* clave) {
    print_solicitud(5);
    char* tel = malloc(sizeof(char)*MAX_TEL);
    fgets(tel, MAX_TEL-1, stdin);
    tel[strlen(tel)-1] = '\0';

    print_solicitud(6);
    char* edad_str = malloc(sizeof(char)*MAX_NRO);
    fgets(edad_str, MAX_NRO-1, stdin);
    int edad = atoi(edad_str);
    free(edad_str);

    // HACER CAMBIOS EN ARBOLES TMB
    void* rdo = tablahash_editar(*agenda, clave, edad, tel);

    // Podría borrar pq si entro acá es pq ya me fije que estuviese
    if (rdo == NULL) {
        free(tel);
        print_error(2);
    }
}

void buscar_eliminar_editar(TablaHash** agenda, int opcion)  {
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

    Contacto contacto = tablahash_buscar(*agenda, clave, 0);
    if (contacto) {
        if (opcion == 1) contacto_imprimir(contacto);
        else if (opcion == 2) tablahash_eliminar(*agenda, clave); // modificar para que tmb haga eliminacion en los árboles
        else if (opcion == 3) editar_aux(agenda, clave);
        else printf("Opción inválida");
    }
    else print_error(2);

    free(nombre);
    free(apellido);
    free(clave);
}

void agregar(TablaHash** agenda) { // Y ÁRBOLES

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

    if (tablahash_buscar(*agenda, clave, 1)) {
        print_error(3);
        free(nombre);
        free(apellido);
        free(clave);
        return;
    } 

    print_solicitud(3);
    char* edad_str = malloc(sizeof(char)*MAX_NRO);
    fgets(edad_str, MAX_NRO-1, stdin);
    int edad = atoi(edad_str);
    free(edad_str);

    print_solicitud(4);
    char* telefono = malloc(sizeof(char)*MAX_TEL);
    fgets(telefono, MAX_TEL-1, stdin);
    telefono[strlen(telefono)-1] = '\0';

    Contacto contacto = contacto_crear(nombre, apellido, edad, telefono);

    tablahash_insertar(*agenda, clave, contacto);

    // AGREGAR A LOS ÁRBOLES CON IDX ya que nunca cambio ese cdo agrando la tabla y solo espero que matcheen las claves

}

void and(TablaHash** agenda) {
    and_or(agenda, 1);
}

void or(TablaHash** agenda) {
    and_or(agenda, 2);
}

void and_or(TablaHash** agenda, int funcion) {
    int nombre_band = 0;
    int apellido_band = 0;
    int tel_band = 0;
    int edad_band = 0;

    char* nombre = malloc(sizeof(char)*MAX_NOMBRE);
    print_solicitud(7);
    fgets(nombre, MAX_NOMBRE-1, stdin);
    nombre[strlen(nombre)-1] = '\0';
    if (strcmp(nombre, "") != 0) {
        nombre_band = 1;
    }

    char* apellido = malloc(sizeof(char)*MAX_APELLIDO);
    print_solicitud(8);
    fgets(apellido, MAX_APELLIDO-1, stdin);
    apellido[strlen(apellido)-1] = '\0';
    if (strcmp(apellido, "") != 0) {
        apellido_band = 1;
    }

    char* edad_str = malloc(sizeof(char)*MAX_NRO);
    print_solicitud(9);
    fgets(edad_str, MAX_NRO-1, stdin);
    if (strcmp(edad_str, "") != 0) {
        edad_band = 1;
    }
    int* edad_pointer = malloc(sizeof(int));
    *edad_pointer = atoi(edad_str);
    if (!edad_band) {
        free(edad_pointer);
    }
    free(edad_str);

    char* tel = malloc(sizeof(char)*MAX_TEL);
    print_solicitud(10);
    fgets(tel, MAX_TEL-1, stdin);
    tel[strlen(tel)-1] = '\0';
    if (strcmp(tel, "") != 0) {
        tel_band = 1;
    }

    int* bands = malloc(sizeof(int)*4);
    bands[0] = nombre_band;
    bands[1] = apellido_band;
    bands[2] = edad_band;
    bands[3] = tel_band;

    andor(agenda, bands, nombre, apellido, edad_pointer, tel, funcion);

    free(bands);

    free(nombre);
    free(apellido);
    free(tel);
    free(edad_pointer);
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
        printf("Ingrese nuevo teléfono:\n>");
        return;
    }

    if (tipo == 6) {
        printf("Ingrese nueva edad:\n>");
        return;
    }

    if (tipo == 7) {
        printf("Ingrese un nombre a buscar\n>");
        return;
    }

    if (tipo == 8) {
        printf("Seleccione un apellido a buscar\n>");
        return;
    }

    if (tipo == 9) {
        printf("Seleccione una edad a buscar\n>");
        return;
    }

    if (tipo == 10) {
        printf("Seleccione un teléfono a buscar\n>");
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