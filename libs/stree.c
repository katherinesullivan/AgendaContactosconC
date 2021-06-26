#include <stdlib.h>
#include <stdio.h>
#include "stree.h"

STree stree_crear() {
    return NULL;
}

void stree_destruir(STree tree) {
    if (tree != NULL){
        stree_destruir(tree->izq);
        stree_destruir(tree->der);
        free(tree);
    }
}

STree stree_nuevo_nodo(int idx) {
    STree nuevo_nodo = malloc(sizeof(STNodo));

    nuevo_nodo->idx = idx;
    nuevo_nodo->izq = NULL;
    nuevo_nodo->der = NULL;

    return nuevo_nodo;
}

STree stree_insertar(STree tree, int idx) {
    if (tree == NULL) return(stree_nuevo_nodo(idx)); 

    if (idx < tree->idx) 
        tree->izq = stree_insertar(tree->izq, idx);
    else if (idx > tree->idx) 
        tree->der = stree_insertar(tree->der, idx);
    else return tree;
}

void stree_imprimir(STree tree) {
    if (tree != NULL) {
        stree_imprimir(tree->izq);
        printf("Idx: %d\n", tree->idx);
        stree_imprimir(tree->der);
    }
}
