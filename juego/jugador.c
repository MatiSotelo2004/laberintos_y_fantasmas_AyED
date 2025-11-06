#include "jugador.h"
#include <stdio.h>

#include <string.h>

void inicializarJugador(tJugador *jugador, const tCoordenadas *posInicial, unsigned cantVidasInicial, const char *nombre)
{
    jugador->posicionActual.x = posInicial->x;
    jugador->posicionActual.y = posInicial->y;
    jugador->puntaje = 0;
    jugador->vidas = cantVidasInicial;
    jugador->cantMovimientos = 0;
    strcpy(jugador->nombre,nombre);
}

void moverJugador(tJugador *jugador, const tCoordenadas *dst)
{
    jugador->posicionActual.x = dst->x;
    jugador->posicionActual.y = dst->y;
}

void sumarPuntajeJugador(tJugador *jugador, unsigned cantidad)
{
    jugador->puntaje+=cantidad;
}

unsigned obtenerPuntajeJugador(const tJugador *jugador)
{
    return jugador->puntaje;
}

void sumarVidaJugador(tJugador *jugador)
{
    jugador->vidas++;
}

void restarVidaJugador(tJugador *jugador)
{
    jugador->vidas--;
}

int obtenerVidasJugador(const tJugador *jugador)
{
    return jugador->vidas;
}

int sumarCantMovimientosJugador(tJugador *jugador)
{
    return (jugador->cantMovimientos+=1);
}


void imprimirJugador(const tJugador *jugador){
    printf("Jugador: %s | Vidas: %d | Puntos: %d | Movimientos: %d\n",jugador->nombre,
                                                                     jugador->vidas,
                                                                     jugador->puntaje,
                                                                     jugador->cantMovimientos);
}


tCoordenadas obtenerCoordenadasJugador(const tJugador *jugador)
{
    return jugador->posicionActual;
}

tCoordenadas* obtenerPunteroJugador(tJugador *jugador)
{
    return &(jugador->posicionActual);
}


void cargarMovimiento(tMovimiento* movimiento,tCoordenadas* posicionJugador,char objeto){
    movimiento->movimiento=*posicionJugador;
    movimiento->objeto=objeto;
}


