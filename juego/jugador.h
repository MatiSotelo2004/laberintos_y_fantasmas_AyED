#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "../coordenadas.h"


#define MAX_TAM_NOMBRE_JUGADOR 512


typedef struct
{
    int vidas;
    char nombre[MAX_TAM_NOMBRE_JUGADOR];
    unsigned cantMovimientos;
    tCoordenadas posicionActual;
    unsigned puntaje;
}tJugador;

typedef struct
{
    tCoordenadas movimiento;
    char objeto;
}tMovimiento;

void inicializarJugador(tJugador *jugador, const tCoordenadas *posicionInicial, unsigned vidasInicial, const char *nombre); ///VALIDADO
void cargarMovimiento(tMovimiento* movimiento,tCoordenadas* posicionJugador,char objeto);

void moverJugador(tJugador *jugador, const tCoordenadas *dst); ///VALIDADO
void sumarPuntajeJugador(tJugador *jugador, unsigned cantidad); ///VALIDADO
void sumarVidaJugador(tJugador *jugador); ///VALIDADO
int sumarCantMovimientosJugador(tJugador *jugador);///VALIDADO
void restarVidaJugador(tJugador *jugador); ///VALIDADO

int obtenerVidasJugador(const tJugador *jugador); ///VALIDADO
unsigned obtenerPuntajeJugador(const tJugador *jugador); ///VALIDADO
tCoordenadas obtenerCoordenadasJugador(const tJugador *jugador);///VALIDADO
tCoordenadas* obtenerPunteroJugador(tJugador *jugador);///VALIDADO

void imprimirJugador(const tJugador *jugador);///VALIDADO
#endif // JUGADOR_H_INCLUDED
