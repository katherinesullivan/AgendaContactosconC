#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbol.h"

#define MAX_STR 32

Arbol arbol_crear() {
    return NULL;
}

Arbol arbol_destruir(Arbol arbol) {
    if (arbol != NULL) {
        arbol_destruir(arbol->izq);
        arbol_destruir(arbol->der);
        free(arbol->dato);
        free(arbol);
    }
}

int max(int a, int b) {
    return (a > b)? a : b;
}

int altura(Arbol arbol) {
    if (arbol == NULL) return 0;
    return arbol->alt;
}

Arbol nuevo_nodo(void* dato, int idx) {
    Arbol nodo = malloc(sizeof(Nodo));

    nodo->dato = dato;
    nodo->idx = idx;
    nodo->izq = NULL;
    nodo->der = NULL;
    nodo->alt = 1;

    return nodo;
}

Arbol der_rotate(Arbol y) {
    Arbol x = y->izq;
    Arbol T2 = x->der;
 
    x->der = y;
    y->izq = T2;
 
    y->alt = max(altura(y->izq), altura(y->der))+1;
    x->alt = max(altura(x->izq), altura(x->der))+1;
 
    return x;
}

Arbol izq_rotate(Arbol x) {
    Arbol y = x->der;
    Arbol T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->alt = max(altura(x->izq), altura(x->der))+1;
    y->alt = max(altura(y->izq), altura(y->der))+1;

    return y;
}

Arbol balancear (Arbol nodo, int balance) {
    // izq izq caso
    if (balance > 1 && get_balance(nodo->izq) >= 0)
        return der_rotate(nodo);
  
    // izq der caso
    if (balance > 1 && get_balance(nodo->izq) < 0) {
        nodo->izq =  izq_rotate(nodo->izq);
        return der_rotate(nodo);
    }
  
    // der der caso
    if (balance < -1 && get_balance(nodo->der) <= 0)
        return izq_rotate(nodo);
  
    // der izq caso
    if (balance < -1 && get_balance(nodo->der) > 0) {
        nodo->der = der_rotate(nodo->der);
        return izq_rotate(nodo);
    }
  
    return nodo;
}

int get_balance(Arbol N) {
    if (N == NULL) return 0;
    return altura(N->izq) - altura(N->der);
}

Arbol arbol_insertar(Arbol nodo, void* dato, int idx, int tipo_arbol) {
    if (nodo == NULL) return(nuevo_nodo(dato, idx));

    // No queremos 2 nodos iguales
    if (nodo->idx == idx) return nodo;

    // Los árboles de tipo 1 contienen strings como datos
    if (tipo_arbol == 1) {
        char* dato_str = (char*)dato;
        char* nodo_dato_str = (char*)(nodo->dato);

        if (strcmp(dato_str, nodo_dato_str) <= 0) 
            nodo->izq = arbol_insertar(nodo->izq, dato, idx, tipo_arbol);

        if (strcmp(dato_str, nodo_dato_str) > 0)
            nodo->der = arbol_insertar(nodo->der, dato, idx, tipo_arbol);
    }

    // Los árboles de tipo 2 contienen int* como datos
    if (tipo_arbol == 2) {
        int dato_int = *(int *)dato;
        int nodo_dato_int = *(int *)nodo->dato;

        if (dato_int <= nodo_dato_int)
            nodo->izq = arbol_insertar(nodo->izq, dato, idx, tipo_arbol);

        else
            nodo->der = arbol_insertar(nodo->der, dato, idx, tipo_arbol);
    }
 
    nodo->alt = 1 + max(altura(nodo->izq), altura(nodo->der));
 
    int balance = get_balance(nodo);

    return balancear(nodo, balance);
}

Arbol min_value_nodo(Arbol nodo) {
    Arbol current = nodo;

    while (current->izq != NULL)
        current = current->izq;
  
    return current;
}

Arbol arbol_eliminar(Arbol nodo, void* dato, int idx, int tipo_arbol) {
    if (nodo == NULL) {
        return nodo;
    }
    char* str = (char*)(nodo->dato);
    
    if (idx == nodo->idx) {
        // Estamos en el nodo a eliminar 

        if((nodo->izq == NULL) || (nodo->der == NULL)) {
            Arbol temp = nodo->izq ? nodo->izq : nodo->der;
  
            // No hijos
            if (temp == NULL) {
                temp = nodo;
                arbol_destruir(nodo);
                nodo = NULL;
            }

            // Un hijo
            else {
                free(nodo->dato);
                *nodo = *temp;
                free(temp);
            }
        }
        else {
            Arbol temp = min_value_nodo(nodo->der);

            nodo->idx = temp->idx;
            free(nodo->dato);
            
            if (tipo_arbol == 1) {
                char* nuevo_dato = malloc(sizeof(char)*MAX_STR);
                strcpy(nuevo_dato, temp->dato);
                nodo->dato = nuevo_dato;
            }

            if (tipo_arbol == 2) {
                int* nuevo_dato = malloc(sizeof(int));
                nuevo_dato = temp->dato;
                nodo->dato = nuevo_dato;
            }
  
            nodo->der = arbol_eliminar(nodo->der, temp->dato, temp->idx, tipo_arbol);
        }
    }

    else {
        // No estoy en el nodo a eliminar y tengo que ver para donde ir

        // Los árboles de tipo 1 contienen strings como datos
        if (tipo_arbol == 1) {
            char* dato_str = (char*)dato;
            char* nodo_dato_str = (char*)(nodo->dato);

            if (strcmp(dato_str, nodo_dato_str) <= 0)
                nodo->izq = arbol_eliminar(nodo->izq, dato, idx, tipo_arbol);

            if (strcmp(dato_str, nodo_dato_str) > 0)
                nodo->der = arbol_eliminar(nodo->der, dato, idx, tipo_arbol);
        }

        // Los árboles de tipo 2 contienen int* como datos
        if (tipo_arbol == 2) {
            int dato_int = *(int *)dato;
            int nodo_dato_int = *(int *)nodo->dato;

            if (dato_int <= nodo_dato_int)
                nodo->izq = arbol_eliminar(nodo->izq, dato, idx, tipo_arbol);

            else
                nodo->der = arbol_eliminar(nodo->der, dato, idx, tipo_arbol);
        }
    }

    // Si el nodo no tenía hijos
    if (nodo == NULL) {
        return nodo;
    }

    nodo->alt = 1 + max(altura(nodo->izq), altura(nodo->der));
  
    int balance = get_balance(nodo);

    return balancear(nodo, balance);
}

void arbol_imprimir_inorder(Arbol arbol, int tipo_de_arbol) {
    if (arbol == NULL) return;

    arbol_imprimir_inorder(arbol->izq, tipo_de_arbol);

    if (tipo_de_arbol == 1) {
        char* dato_str = (char *)arbol->dato;
        printf("En %d: %s con altura: %d\n", arbol->idx, dato_str, arbol->alt);
    }
    if (tipo_de_arbol == 2) {
        int dato_int = *(int *)(arbol->dato);
        printf("En %d: %d con altura: %d\n", arbol->idx, dato_int, arbol->alt);
    }

    arbol_imprimir_inorder(arbol->der, tipo_de_arbol);
}