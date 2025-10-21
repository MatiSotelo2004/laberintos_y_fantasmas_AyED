#ifndef COLAD_H
#define COLAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_COLA 100
#define TODO_OK 0
#define ERROR 1

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

typedef struct sNodo
{
    void *dato;
    unsigned tamDato;
    struct sNodo *sig;
} tNodo;

typedef struct
{
    tNodo *pri;
    tNodo *ult;
}tCola;

void crearCola(tCola *cola);
int encolarCola(tCola *cola, const void *dato, unsigned tamDato);
int descolarCola(tCola *cola, void *dato, unsigned tamDato);
int colaLlena(const tCola *cola, unsigned tamDato);
int colaVacia(const tCola *cola);
int verPrimero(const tCola *cola, void *dato, unsigned tamDato);
void destruirCola(tCola *cola);

#endif //COLAD_H