#include "jugador.h"

int jugadorCrear(tJugador *jugador)
{
    /*
    jugador->vMovimientos = (char*)malloc(CAP_INICIAL_VECTOR_MOVIMIENTOS * sizeof(tCoordenadas));
    if(!jugador->vMovimientos)
        return TABLERO_SIN_MEM;
    jugador->capMaxMovimientos = CAP_INICIAL_VECTOR_MOVIMIENTOS;*/
    return TODO_OK;

}

void jugadorInicializar(tJugador *jugador, const tCoordenadas *posInicial, unsigned cantVidasInicial)
{
    jugador->posicionActual.x = posInicial->x;
    jugador->posicionActual.y = posInicial->y;
    jugador->puntaje = 0;
    jugador->vidas = cantVidasInicial;
}
