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

void coordenadasMover(tCoordenadas *coords, tDireccion dir)
{
    switch(dir)
    {
        case IZQUIERDA:
            coords->x--;
            break;
        case DERECHA:
            coords->x++;
            break;
        case ARRIBA:
            coords->y--;
            break;
        case ABAJO:
            coords->y++;
            break;
    }
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
    double distanciaEnXDerecha = DISTANCIA(dst->x+1,puntoB->x,puntoA->y,puntoB->y);
    double distanciaEnXIzquierda = DISTANCIA(dst->x-1,puntoB->x,puntoA->y,puntoB->y);
    double distanciaEnYArriba = DISTANCIA(dst->x,puntoB->x,puntoA->y+1,puntoB->y);
    double distanciaEnYAbajo = DISTANCIA(dst->x,puntoB->x,puntoA->y-1,puntoB->y);

    dst->y = puntoA->y;
    if(distanciaEnXDerecha < distanciaEnXIzquierda)
    {
        menorDistancia = distanciaEnXDerecha;
        dst->x = puntoA->x + 1;
    }else
    {
        menorDistancia = distanciaEnXIzquierda;
        dst->x = puntoA->x - 1;
    }

    if(distanciaEnYArriba < menorDistancia || distanciaEnYAbajo < menorDistancia)
    {
        dst->x = puntoA->x;
        if(distanciaEnYArriba < distanciaEnYAbajo)
            dst->y = puntoA->y+1;
        else
            dst->y = puntoA->y-1;
    }
}
