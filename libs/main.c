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
  char *accion = malloc(sizeof(char) * 10);
  AccList* deshacer = acciones_init(N);
  AccList* rehacer = acciones_init(N);
  TablaHash *agenda = tablahash_crear(32, hash, &hash2);
  print_menu_acciones();
  do {
    flag = interpretar(&agenda, accion, deshacer, rehacer);
  } while (flag);
  free(accion);
  return 0;
}
