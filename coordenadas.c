#include "coordenadas.h"
#include <math.h>

double obtenerDistancia(const tCoordenadas *c1 , const tCoordenadas *c2)
{
    return sqrt((c2->x - c1->x) * (c2->x-c1->x) + (c2->y - c1->y) *  (c2->y - c1->y));
}

void coordenadasCopiar(const tCoordenadas *orig, tCoordenadas *dst)
{
    dst->x = orig->x;
    dst->y = orig->y;
}

int coordenadasSonIguales(const tCoordenadas *c1, const tCoordenadas *c2) ///VALIDADO
{
    return c1->x == c2->x && c1->y == c2->y;
}

void coordenadaEjecutarMovimiento(tCoordenadas *cord, char movimiento) ///VALIDADO
{
    switch(movimiento)
    {
        case MOVIMIENTO_ABAJO: cord->y++;
            break;
        case MOVIMIENTO_ARRIBA: cord->y--;
            break;
        case MOVIMIENTO_DERECHA: cord->x++;
            break;
        case MOVIMIENTO_IZQUIERDA: cord->x--;
            break;
    }
}
