#ifndef __ANDOR_H__
#define __ANDOR_H__

#include <stddef.h>
#include "arbol.h"
#include "slist.h"
#include "stree.h"

typedef struct {
    Arbol arbol;
    int tipo;
    SList* lista;
    void* dato;
} Argumento;

Argumento* argumento_crear(Arbol arbol, int tipo, SList* lista, void* dato);

#endif                          /* __ANDOR_H__ */