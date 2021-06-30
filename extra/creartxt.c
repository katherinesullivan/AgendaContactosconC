#include <stdio.h>
#include <stdlib.h>

int main () {
    FILE *apellidos;
    apellidos = fopen("apellidos.txt", "r+");
    FILE* nombres;
    nombres = fopen("nombres.txt", "r+");
    FILE* nuevo;
    nuevo = fopen("8entrada.txt", "w+");
    while (!feof(apellidos) && !feof(nombres)) {
        char* nombre = malloc(sizeof(char) *32);
        fscanf(nombres,"%s", nombre);
        char* apellido = malloc(sizeof(char) *32);
        fscanf(apellidos, "%s", apellido);
        int edad = rand() % 100;
        int telefono = rand();
        fprintf(nuevo,"%s,%s,%d,%d\n", nombre, apellido, edad, telefono);
        free(nombre);
        free(apellido);
    }
    fclose(apellidos);
    fclose(nombres);
    fclose(nuevo);
    return 0;
}