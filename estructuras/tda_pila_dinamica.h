#ifndef TDA_PILA_DINAMICA_H
#define TDA_PILA_DINAMICA_E
#include "nodo.h"

#define ERROR_PILA 1

typedef tNodo *tpila;

void crearPila(tpila *pila);
int apilarPila(tpila *pila, const void *dato, unsigned tamDato);
int desapilarPila(tpila *pila, void *dato, unsigned tamDato);
int pilaVacia(const tpila *pila);
int pilaLlena(const tpila *pila, unsigned tamDato);
int verTope(const tpila *pila, void *dato, unsigned tamDato);
void destruirPila(tpila *pila);

#endif // TDA_PILA_DINAMICA_H
