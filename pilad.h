#ifndef PILAD_H
#define PILAD_E

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK 0
#define ERROR 1
#define TAM_PILA 1000

#define MIN(X, Y)((X) < (Y) ? (X) : (Y))

typedef struct sNodo{
    void *dato;
    unsigned tamDato;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tpila;

void crearPila(tpila *pila);
int apilarPila(tpila *pila, const void *dato, unsigned tamDato);
int desapilarPila(tpila *pila, void *dato, unsigned tamDato);
int pilaVacia(const tpila *pila);
int pilaLlena(const tpila *pila, unsigned tamDato);
int verTope(const tpila *pila, void *dato, unsigned tamDato);
void destruirPila(tpila *pila);

#endif // PILAD_H
