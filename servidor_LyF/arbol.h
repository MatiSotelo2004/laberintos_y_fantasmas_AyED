#ifndef ARBOL_H
#define ARBOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK 0
#define SIN_MEM 1
#define EXISTE 2

typedef struct sNodoArbol
{
    void *dato;
    unsigned tamDato;
    struct sNodoArbol *izq;
    struct sNodoArbol *der;
} tNodoArbol;
typedef tNodoArbol *tArbol;

void crearArbol(tArbol *p);
void destruirArbol(tArbol *p);
int insertarArbolBin(tArbol *p, const void *dato, unsigned tamDato, int (*cmp)(const void *, const void *));
int buscarArbol(tArbol *p, void *datto, unsigned tamDato, const void *clave);

#endif // ARBOL_H
