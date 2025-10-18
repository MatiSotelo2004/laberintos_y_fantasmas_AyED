#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "macros.h"
#include "coordenadas.h"
#include "configuracionTablero.h"
#include "pilad.h"
#define VALOR_MINIMO 5
#define MAX_VECINOS 4
#define OBTENER_NUM_ALEATORIO(MIN,MAX,DST) \
    ((DST) = (rand() % ((MAX) - (MIN))) + (MIN))


typedef void (*Accion)(void *elem, void *extra);

typedef struct
{
    unsigned cantidad;
    tCoordenadas vecino[MAX_VECINOS];
}tVecinos;

typedef struct
{
    char **tablero; //apunta al inicio del laberinto
    tCoordenadas limite; //filas y columnas totales del laberinto
    tCoordenadas entrada; //cordenadas de la entrada
    tCoordenadas salida; //cordenadas de la salida
    tCoordenadas actual; //cordenadas de la casilla en la que estoy parado
    tVecinos vecinos;
}tTablero;



int obtenerNumeroAleatorio(int mini, int maxi);
int posicionEstaDisponible(char **tablero, int fila, int columna);
//////////////////////////////////////////////////////////////////
///
int tableroCrear(tTablero *tablero, const tConfigTablero *config);
void tableroDestruir(tTablero *tablero);
void tableroDibujarParedes(tTablero *tablero);
void tableroInicializar(tTablero *tablero, char caracter);
void tableroImprimir(const tTablero *tablero, FILE *fp, Accion mostrar);
int tableroPosicionEstaDisponible(const tTablero *tablero, const tCoordenadas *coords);
void tableroColocarObjetosAleatorio(tTablero *tablero, tCoordenadas *coords, unsigned cantObj, char caracter);
void tableroVerObjeto(const tTablero *tablero, const tCoordenadas *coords, char *dest);
int tableroColocarObjeto(tTablero *tablero, const tCoordenadas *obj, char caracter);





void cantidadVecinos(tTablero* lab);
void generarLab(tTablero* lab);
void caminosRandom(tTablero* lab);
tCoordenadas tableroEntrada(const tTablero *tablero);
tCoordenadas tableroSalida(const tTablero *tablero);
//////////////////////////////////////////////////////////////////
///Nuevas funciones
void colocarEntradaSalida(tTablero* lab);
void generarCaminosPrincipales(tTablero* lab);
void generarCaminosRandom(tTablero* lab, int cantidadCaminos);
void limpiarEntradaSalida(tTablero* lab);
int obtenerNumeroAleatorio(int minimo, int maximo);
int posicionDisponible(const tTablero* lab, int x, int y);

//
int tableroPosicionEstaDisponibleV2(const char** tablero,const tCoordenadas *coords);


#endif // TABLERO_H_INCLUDED
