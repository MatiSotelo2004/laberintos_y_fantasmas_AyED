#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TODO_OK 0
#define SIN_MEM -1
#define  EXISTE 1

typedef struct sNodoArbol{
    void *dato;
    unsigned tamDato;
    struct sNodoArbol *izq;
    struct sNodoArbol *der;
}tNodoArbol;
typedef tNodoArbol* tArbol;

typedef void (*Accion) (void *a, void *b);
typedef int (*Cmp)(const void *a, const void *b);

void crearArbol(tArbol*p);
void destruirArbol(tArbol*p);
int insertarArbolBinNoR(tArbol*p, const void*dato, unsigned tamDato, int (*cmp)(const void*, const void*));
int insertarArbolBinConR(tArbol*p, const void*dato, unsigned tamDato, int (*cmp)(const void*, const void*));
int compararInt(const void*x, const void*y);
void postOrden(tArbol*p, void *extra, Accion accion);
void preOrden(tArbol*p, void *extra, Accion accion);
void inOrder(tArbol*p, void *extra, Accion accion);
void printInt(void*x);
int cantHojas(tArbol*p);
int cantNoHojas(tArbol*p);
int arbolAltura(const tArbol *ar);
int arbolNivel(const tArbol *ar);
void arbolAccionHastaNivel(const tArbol *ar, int nivel, void *extra, int incluyeNivel, Accion accion);
void arbolAccionEnNivel(const tArbol *ar, int nivel, void *extra,Accion accion);
void arbolAccionDespuesNivel(const tArbol *ar, int nivel, void *extra, int incluyeNivel, Accion accion);
void arbolDestruirAPartirDeNivel(tArbol *ar, int nivel);
tArbol *arbolBuscar(tArbol *ar, const void *key, Cmp cmp);
tArbol *arbolBuscarMayor(tArbol *ar);
tArbol *arbolBuscarMenor(tArbol *ar);
int arbolEliminarNodo(tArbol *ar, const void *key, Cmp cmp);
void arbolEliminarRaiz(tArbol *ar);

#endif // ARBOL_H_INCLUDED
