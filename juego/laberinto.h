#ifndef LABERINTO_H_INCLUDED
#define LABERINTO_H_INCLUDED

#include "../estructuras/tda_lista_doble.h"

#include "tablero.h"

#define NO_VALIDO 0
#define SI_VALIDO 1
#define SALTO_CELDA 2
#define SALTO_EXTRA 1
#define MAX_DESPLAZAMIENTOS 4
#define MAX_PAREDES_VECINAS 4
#define MAX_ALEATORIOS 40
#define DENSIDAD 0.1
#define BORDE_SUPERIOR 0
#define BORDE_IZQUIERDO 0
#define BORDE_INFERIOR(y) ((y) - 1)
#define BORDE_DERECHO(x) ((x) - 1)
#define PRIMER_INTERIOR_FILA (BORDE_SUPERIOR + 1)
#define PRIMER_INTERIOR_COL (BORDE_IZQUIERDO + 1)
#define ULTIMO_INTERIOR_FILA(y) ((y) - 2)
#define ULTIMO_INTERIOR_COL(x) ((x) - 2)

typedef int (*Validacion)(tTablero* laberinto,int fila,int columna);


void generarLaberinto(tTablero* laberinto);

void generarEntradaLab(tTablero* laberinto);
void generarSalidaLab(tTablero* laberinto);
void posicionarActualEnSalidaLab(tTablero* laberinto);
void generarCaminoPrincipalLab(tTablero* laberinto, tpila* historial,tLista* futurosCaminos);
void generarCaminosExtrasLab(tTablero* laberinto,tLista* futurosCaminos);
void generarAberturasDeCaminosLab(tTablero* laberinto);


void trazarCaminoHastaDondeLlegueExtraLab(tTablero* laberinto,tCoordenadas camino);
int esExtraValidoExtraLab(tTablero* laberinto,int fila,int columna);
void conectarConCaminoPrincipalExtra(tTablero* laberinto);
void calcularExtrasDisponiblesExtraLab(tTablero* laberinto,int salto,Validacion valido);
void trazarCaminosExtrasLab(tTablero* laberinto);





void calcularVecinosDisponiblesPrincipalLab(tTablero* laberinto);
int esVecinoValidoPrincipalLab(const tTablero* laberinto, int fila, int columna);
void trazarCaminoHaciaVecinoPrincipalLab(tTablero* laberinto);
tCoordenadas calcularCeldaIntermediaLab(const tCoordenadas* origen, const tCoordenadas* destino);

int esAberturaValidaLab(const tTablero* laberinto,int fila,int columna);
void contarParedesVecinas(const tTablero* laberinto,tCoordenadas actual,int* paredesVecinas);


int cmpVecino(const void* a,const void* b);

#endif // LABERINTO_H_INCLUDED
