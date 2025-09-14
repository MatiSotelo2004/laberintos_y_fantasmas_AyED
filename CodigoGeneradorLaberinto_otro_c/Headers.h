#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILASMAXIMAS 41
#define COLUMNASMAXIMAS 41
#define TAMVEC 100

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
    tCordenadas vec[TAMVEC];
    unsigned tope;
}tHistorial;

//typedef struct
//{
//    tCordenadas dato;
//    struct sNodo *siguiente;
//}tNodo;
//
//typedef tNodo* tPila;

typedef struct
{
    char mat[FILASMAXIMAS][COLUMNASMAXIMAS]; //apunta al inicio del laberinto
    unsigned filasTotales; //filas totales del laberinto
    unsigned columnasTotales; //columnas totales del laberinto
    tCordenadas entrada; //cordenadas de la entrada
    tCordenadas salida; //cordenadas de la salida
    tCordenadas actual; //cordenadas de la casilla en la que estoy parado
    tVecinos vecinos; //cordenadas y cantidad de los vecinos de la casilla actual
    tHistorial historial; //Guarda el Historial de las casillas recorridas. APLICAR PILA DINAMICA, ME DIO FIACA
}tLaberinto;

#endif // HEADERS_H_INCLUDED
