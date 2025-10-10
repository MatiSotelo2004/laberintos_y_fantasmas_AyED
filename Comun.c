#include "Comun.h"

tCoordenadas fantasmaObtenerSiguienteMovimiento(const tTablero *tablero, const tCoordenadas *posFantasma, const tCoordenadas *posJugador)
{
    tCoordenadas* disponibles = tableroObtenerMovimientoPosible(tablero,posFantasma);
    tCoordenadas mejor;
    mejor.x = posFantasma->x;
    mejor.y = posFantasma->y;

    for(int i = 0; i < 8; i++) //8 es la maxima cantidad de movimientos disponibles para el fantasma.
        //si no queremos que el fantasma se mueva en diagonal, basta con reemplazar el 8 por un 4
    {
        if((disponibles+i)->x != COORDENADA_NO_DISPONIBLE && (disponibles+i)->y != COORDENADA_NO_DISPONIBLE)
        {
            if(obtenerDistancia(disponibles+i,posJugador) <= obtenerDistancia(&mejor,posJugador))
            {
                mejor.x = (disponibles+i)->x;
                mejor.y = (disponibles+i)->y;
            }
        }
    }

    free(disponibles);
    return mejor;
}

void actualizarMovimientosTableroDesdeCola(tCola *colaMovimientos, tTablero *tablero, tJugador *jugador)
{
    //se sabe que siempre, los primeros en salir de la cola son los fantasmas
    tCoordenadas movimiento;
    while(!colaVacia(colaMovimientos))
    {
        sacarCola(colaMovimientos,&movimiento,sizeof(tCoordenadas));
        tableroColocarObjeto(tablero,&movimiento,CARACTER_FANTASMA);
    }

    tableroColocarObjeto(tablero,&movimiento,CARACTER_JUGADOR);
    jugadorMover(jugador,&movimiento);
}
