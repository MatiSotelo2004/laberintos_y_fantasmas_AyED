#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED
#include "coordenadas.h"
#include "macros.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>

#define MAX_TAM_NOMBRE_JUGADOR 512
#define MENSAJE_PEDIR_NOMBRE "Ingrese el nombre del jugador: "
#define CANT_PUNTAJE_POR_PREMIO_TABLERO 1
#define CANT_PUNTAJE_POR_GANAR 3

typedef struct
{
    int vidas;
    char nombre[MAX_TAM_NOMBRE_JUGADOR];
    unsigned cantMovimientos;
    tCoordenadas posicionActual;
    unsigned puntaje;
    char modo; //
}tJugador;

void jugadorInicializar(tJugador *jugador, const tCoordenadas *posicionInicial, unsigned vidasInicial, const char *nombre);
int jugadorEsGanador(const tJugador *jugador, const tCoordenadas *salida);
char jugadorPedirMovimiento(void);
tCoordenadas jugadorCoordenadas(const tJugador *j);
void jugadorReemplazarCoordenadas(tJugador *jugador, const tCoordenadas *dst);
const tCoordenadas* jugadorCoordenadasPuntero(const tJugador *j);
void jugadorMover(tJugador *j, const tCoordenadas *dst);
void jugadorSumarPuntaje(tJugador *j, unsigned cantidad);
void jugadorSumarVida(tJugador *j);
void jugadorRestarVida(tJugador *j);
int jugadorCantVidas(const tJugador *j);
int jugadorSumarCantidadDeMovimiento(tJugador *j);

#endif // JUGADOR_H_INCLUDED
