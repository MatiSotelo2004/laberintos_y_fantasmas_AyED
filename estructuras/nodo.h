#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TODO_OK 0
#define MIN(a,b) (((a)<(b))?(a):(b))
#define SIN_MEMORIA -1

typedef struct sNodo{
    void* dato;
    unsigned tam;
    struct sNodo* sig;
}tNodo;

typedef int Duplicado;
typedef void (*AccionLista)(const void* a);
typedef int (*Filtro)(const void* a);
typedef int (*Cmp)(const void* a,const void* b);
typedef void (*Act)(void*a,const void*b);
typedef void (*Accion) (void *a, void *b);

#endif // NODO_H_INCLUDED
