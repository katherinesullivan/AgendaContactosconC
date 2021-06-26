#include <stdio.h>
#include "stree.h"

int main() {
    STree tree = stree_crear();
    for (int i = 0; i<10; i++) {
        printf("Ingrese un número:\n");
        int nro = 0;
        scanf("%d", &nro);
        tree = stree_insertar(tree, nro);
    }
    stree_imprimir(tree);
    stree_destruir(tree);
    return 0;
}