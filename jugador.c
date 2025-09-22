#include "jugador.h"

int jugadorCrear(tJugador *jugador)
{

    jugador->vMovimientos = (char*)malloc(CAP_INICIAL_VECTOR_MOVIMIENTOS * sizeof(tCoordenadas));
    if(!jugador->vMovimientos)
        return TABLERO_SIN_MEM;
    jugador->capMaxMovimientos = CAP_INICIAL_VECTOR_MOVIMIENTOS;
    return TODO_OK;

}

void jugadorInicializar(tJugador *jugador, const tCoordenadas *posInicial, unsigned cantVidasInicial)
{
    jugador->posicionActual.x = posInicial->x;
    jugador->posicionActual.y = posInicial->y;
    jugador->puntaje = 0;
    jugador->vidas = cantVidasInicial;
    jugador->cantMovimientos = 0;
    jugador->capMaxMovimientos = CAP_INICIAL_VECTOR_MOVIMIENTOS;
}

void jugadorDestruir(tJugador *jugador)
{
    free(jugador->vMovimientos);
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
<<<<<<< Updated upstream
=======
}

void jugadorSumarPuntaje(tJugador *j)
{
    j->puntaje++;
}

void jugadorSumarVida(tJugador *j)
{
    j->vidas++;
}

void jugadorRestarVida(tJugador *j)
{
    j->vidas--;
>>>>>>> Stashed changes
}
