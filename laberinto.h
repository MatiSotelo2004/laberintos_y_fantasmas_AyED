#ifndef LABERINTO_H_INCLUDED
#define LABERINTO_H_INCLUDED
#include "tablero.h"
#include <stdlib.h>
#include <stdio.h>
#define SALTO_CELDA 2
#define MAX_DESPLAZAMIENTOS 4
#define MAX_ALEATORIOS 40
#define BORDE_SUPERIOR 0
#define BORDE_IZQUIERDO 0
#define BORDE_INFERIOR(y) ((y) - 1)
#define BORDE_DERECHO(x) ((x) - 1)
#define PRIMER_INTERIOR_FILA (BORDE_SUPERIOR + 1)
#define PRIMER_INTERIOR_COL (BORDE_IZQUIERDO + 1)
#define ULTIMO_INTERIOR_FILA(y) ((y) - 2)
#define ULTIMO_INTERIOR_COL(x) ((x) - 2)


void generarLaberinto(tTablero* laberinto);
void generarEntradaLab(tTablero* laberinto);
void generarSalidaLab(tTablero* laberinto);
void inicializarInicioLab(tTablero* laberinto);
void generarCaminoPrincipalLab(tTablero* laberinto, tpila* historial);
void calcularVecinosDisponiblesLab(tTablero* laberinto);
int esVecinoValidoLab(const tTablero* laberinto, int fila, int columna);
void trazarCaminoHaciaVecinoLab(tTablero* laberinto);
tCoordenadas calcularCeldaIntermediaLab(const tCoordenadas* origen, const tCoordenadas* destino);
int esVecinoValidoLab(const tTablero* laberinto, int fila, int columna);
void limpiarSalidaLab(tTablero* lab);
void limpiarEntradaLab(tTablero* lab);
int esPosicionValidaParaCaminoLab(const tTablero* lab, int fila, int columna);
void agregarCaminosAleatoriosLab(tTablero* laberinto, int cantidadDeseada);


void mostrarCharEnPantalla(void *fp, void *elem);


#endif // LABERINTO_H_INCLUDED
