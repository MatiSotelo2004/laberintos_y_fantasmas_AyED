#include "jugador.h"

void jugadorInicializar(tJugador *jugador, const tCoordenadas *posInicial, unsigned cantVidasInicial, const char *nombre)
{
    jugador->posicionActual.x = posInicial->x;
    jugador->posicionActual.y = posInicial->y;
    jugador->puntaje = 0;
    jugador->vidas = cantVidasInicial;
    jugador->cantMovimientos = 0;
    strcpy(jugador->nombre,nombre);
}

char jugadorPedirMovimiento()
{
    return _getch();
}

int jugadorEsGanador(const tJugador *jugador, const tCoordenadas *salida)
{
    if(jugador->posicionActual.x == salida->x && jugador->posicionActual.y == salida->y)
        return FIN_JUEGO;

    return !FIN_JUEGO;
}

tCoordenadas jugadorCoordenadas(const tJugador *j)
{
    return j->posicionActual;
}

void jugadorReemplazarCoordenadas(tJugador *jugador, const tCoordenadas *dst)
{
    jugador->posicionActual.x = dst->x;
    jugador->posicionActual.y = dst->y;
}

const tCoordenadas* jugadorCoordenadasPuntero(const tJugador *j)
{
    return &j->posicionActual;
}

void jugadorMover(tJugador *j, const tCoordenadas *dst)
{
    j->posicionActual.x = dst->x;
    j->posicionActual.y = dst->y;
}

void jugadorSumarPuntaje(tJugador *j, unsigned cantidad)
{
    j->puntaje+=cantidad;
}

void jugadorSumarVida(tJugador *j)
{
    j->vidas++;
}

void jugadorRestarVida(tJugador *j)
{
    j->vidas--;
}

int jugadorCantVidas(const tJugador *j)
{
    return j->vidas;
}

int jugadorSumarCantidadDeMovimiento(tJugador *j)
{
    return (j->cantMovimientos+=1);
}
