#ifndef TABLERO_V2_H_INCLUDED
#define TABLERO_V2_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "macros.h"
#include "coordenadas.h"
#include"pilad.h"

#define PARED '#'
#define CAMINO '.'
#define ENTRADA 'e'
#define SALIDA 's'

#define CANTCAM 4

typedef struct
{
    /*
     filas: 20
    columnas: 40
    vida_inicial: 2
    fantasmas: 4
    premios: 5
    vida_extra: 6
    */
    tCoordenadas tamTablero;
    unsigned cantVidaInicial;
    unsigned cantFant;
    unsigned cantPremio;
    unsigned cantVidaExtra;
    unsigned filas;
    unsigned columnas;
}tConfigTablero;

typedef struct
{
    unsigned fila;
    int columna;
}tCordenadas;

typedef struct
{
    unsigned cantidad;
    tCordenadas vecino[4];
}tVecinos;

typedef struct
{
    char **mat; //apunta al inicio del laberinto
    unsigned filasTotales; //filas totales del laberinto
    unsigned columnasTotales; //columnas totales del laberinto
    tCordenadas entrada; //cordenadas de la entrada
    tCordenadas salida; //cordenadas de la salida
    tCordenadas actual; //cordenadas de la casilla en la que estoy parado
    tVecinos vecinos; //cordenadas y cantidad de los vecinos de la casilla actual
}tLaberinto;

typedef struct
{
    char **tablero;
    int ejeX;
    int ejeY;
}tTablero;


int cargarConfig(tConfigTablero *config, const char *nomArch);
int inicializarTablero(tLaberinto *tab, tConfigTablero *config);

void mostrarLab(tLaberinto*);
void llenarLabParedes(tLaberinto*);
void cantidadVecinos(tLaberinto*);
void generarLab(tLaberinto*);

void destruirTablero(tLaberinto*tab);

void caminosRandom(tLaberinto*);

#endif // TABLERO_V2_H_INCLUDED
