#include <stdio.h>
#include <stdlib.h>
#include "interprete.h"

#define N 5

unsigned hash(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 11 * hashval;
  return hashval;
}

unsigned hash2(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 13 * hashval;
  return hashval;
}

int main() {
    int flag = 1;
    int** acciones = init_desh_reh();
    char* accion = malloc(sizeof(char)*10);
    TablaHash* diccionario = tablahash_crear(31, hash, &hash2);
    do {
        flag = interpretar(&diccionario, accion);
    } while (flag);
    free(accion);
    return 0;
}