#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED
#include "coordenadas.h"
#include "macros.h"
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

#endif // JUGADOR_H_INCLUDED
