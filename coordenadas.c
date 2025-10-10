#include "coordenadas.h"

unsigned obtenerDistancia(const tCoordenadas *c1 , const tCoordenadas *c2)
{
    return sqrt((c2->x - c1->x) * (c2->x-c1->x) + (c2->y - c1->y) *  (c2->y - c1->y));
}

void coordenadasRestarX(tCoordenadas *coords)
{
    coords->x--;
}

void coordenadasSumarX(tCoordenadas *coords)
{
    coords->x++;
}

void coordenadasSumarY(tCoordenadas *coords)
{
    coords->y++;
}

void coordenadasRestarY(tCoordenadas *coords)
{
    coords->y--;
}

void coordenadasCopiar(const tCoordenadas *orig, tCoordenadas *dst)
{
    dst->x = orig->x;
    dst->y = orig->y;
}

int coordenadasSonIguales(const tCoordenadas *c1, const tCoordenadas *c2)
{
    return c1->x == c2->x && c1->y == c2->y;
}

void coordenadaEjecutarMovimiento(tCoordenadas *cord, char movimiento)
{
    switch(movimiento)
    {
        case MOVIMIENTO_ABAJO: cord->x--;
            break;
        case MOVIMIENTO_ARRIBA: cord->x++;
            break;
        case MOVIMIENTO_DERECHA: cord->y++;
            break;
        case MOVIMIENTO_IZQUIERDA: cord->y--;
            break;
    }
}

void coordenadasMovimientoRecomendado(const tCoordenadas *puntoA, const tCoordenadas *puntoB, tCoordenadas *dst)
{
    double menorDistancia;
    double distanciaEnXArriba = DISTANCIA(dst->x+1,puntoB->x,puntoA->y,puntoB->y);
    double distanciaEnXAbajo = DISTANCIA(dst->x-1,puntoB->x,puntoA->y,puntoB->y);
    double distanciaEnYDerecha = DISTANCIA(dst->x,puntoB->x,puntoA->y+1,puntoB->y);
    double distanciaEnYIzquierda = DISTANCIA(dst->x,puntoB->x,puntoA->y-1,puntoB->y);
    
    dst->y = puntoA->y;
    if(distanciaEnXArriba < distanciaEnXAbajo)
    {
        menorDistancia = distanciaEnXArriba;
        dst->x = puntoA->x + 1;
    }else
    {
        menorDistancia = distanciaEnXAbajo;
        dst->x = puntoA->x - 1;
    }

    if(distanciaEnYDerecha < menorDistancia || distanciaEnYIzquierda < menorDistancia)
    {
        dst->x = puntoA->x;
        if(distanciaEnYDerecha < distanciaEnYIzquierda)
            dst->y = puntoA->y+1;
        else
            dst->y = puntoA->y-1;
    }
}
