#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK 0
#define SIN_MEM -1
#define EXISTE 1
#define LISTA_VACIA 2
#define LISTA_NO_VACIA 3

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

typedef struct sNodoLista
{
    void *dato;
    unsigned tamDato;
    struct sNodoLista *sig;
    struct sNodoLista *ant;
} tNodoLista;

typedef tNodoLista *tLista;

void crearLista(tLista *lista);
int listaVacia(tLista *lista);
int listaInsertarOrdenado(tLista *lista, const void *dato, unsigned tamDato, int (*comparar)(const void *, const void *));
int listaSacarPrimero(tLista *lista, void *dato, unsigned tamDato);
void destruirLista(tLista *lista);


#endif // LISTA_H_INCLUDED
