#ifndef COORDENADAS_H_INCLUDED
#define COORDENADAS_H_INCLUDED
#include <math.h>
#include "macros.h"

#define DISTANCIA(X1,X2,Y1,Y2) (sqrt(((X2)-(X1)) * ((X2)-(X1)) + ((Y2) - (Y1)) * ((Y2) - (Y1))))

typedef struct
{
    unsigned x;
    unsigned y;
}tCoordenadas;

unsigned obtenerDistancia(const tCoordenadas *c1 , const tCoordenadas *c2);
void coordenadasRestarX(tCoordenadas *coords);
void coordenadasSumarX(tCoordenadas *coords);
void coordenadasSumarY(tCoordenadas *coords);
void coordenadasRestarY(tCoordenadas *coords);
void coordenadasCopiar(const tCoordenadas *orig, tCoordenadas *dst);
int coordenadasSonIguales(const tCoordenadas *c1, const tCoordenadas *c2);
void coordenadaEjecutarMovimiento(tCoordenadas *cord, char movimiento);
void coordenadasMovimientoRecomendado(const tCoordenadas *puntoA, const tCoordenadas *puntoB, tCoordenadas *dst);

#endif // COORDENADAS_H_INCLUDED
