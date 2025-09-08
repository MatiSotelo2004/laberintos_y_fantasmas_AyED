#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "macros.h"
#include "coordenadas.h"
#include "configuracionTablero.h"

typedef void (*Accion)(void *elem, void *extra);

typedef struct
{
    char **tablero;
    tCoordenadas limite;
}tTablero;

//////////////////////////////////////////////////////////////////
///
int tableroCrear(tTablero *tablero, const tConfigTablero *config);
void tableroDestruir(tTablero *tablero);
void tableroDibujarParedes(tTablero *tablero);
void tableroInicializar(tTablero *tablero, char caracter);
void tableroImprimir(const tTablero *tablero, FILE *fp, Accion mostrar);
int tableroPosicionEstaDisponible(const tTablero *tablero, const tCoordenadas *coords);
void tableroColocarObjetosAleatorio(tTablero *tablero, tCoordenadas *coords, unsigned cantObj, char caracter);
tCoordenadas tableroEstablecerEntrada(tTablero *tablero);
tCoordenadas tableroEstablecerSalida(tTablero *tablero);
void tableroVerObjeto(const tTablero *tablero, const tCoordenadas *coords, char *dest);
int tableroColocarObjeto(tTablero *tablero, const tCoordenadas *obj, char caracter);
//////////////////////////////////////////////////////////////////
///

#endif // TABLERO_H_INCLUDED
