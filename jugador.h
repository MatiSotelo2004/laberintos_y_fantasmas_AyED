#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED
#include "coordenadas.h"
#include "macros.h"
#include <stdio.h>
#include <conio.h>
#define CAP_INICIAL_VECTOR_MOVIMIENTOS 100

typedef struct
{
    unsigned vidas;
    char *vMovimientos;
    unsigned cantMovimientos;
    tCoordenadas posicionActual;
    unsigned puntaje;
    unsigned capMaxMovimientos;
}tJugador;

int jugadorCrear(tJugador *jugador);
void jugadorDestruir(tJugador *jugador);
void jugadorInicializar(tJugador *jugador, const tCoordenadas *posicionInicial, unsigned vidasInicial);
int jugadorEsGanador(const tJugador *jugador, const tCoordenadas *salida);
char jugadorPedirMovimiento(void);
tCoordenadas jugadorCoordenadas(const tJugador *j);
void jugadorReemplazarCoordenadas(tJugador *jugador, const tCoordenadas *dst);
const tCoordenadas* jugadorCoordenadasPuntero(const tJugador *j);
void jugadorMover(tJugador *j, const tCoordenadas *dst);

#endif // JUGADOR_H_INCLUDED
