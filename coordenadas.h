#ifndef COORDENADAS_H_INCLUDED
#define COORDENADAS_H_INCLUDED

#define MOVIMIENTO_ARRIBA 'w'
#define MOVIMIENTO_IZQUIERDA 'a'
#define MOVIMIENTO_ABAJO 's'
#define MOVIMIENTO_DERECHA 'd'

typedef struct
{
    int x;
    int y;
}tCoordenadas;

double obtenerDistancia(const tCoordenadas *c1 , const tCoordenadas *c2);
void coordenadasCopiar(const tCoordenadas *orig, tCoordenadas *dst);
int coordenadasSonIguales(const tCoordenadas *c1, const tCoordenadas *c2);
void coordenadaEjecutarMovimiento(tCoordenadas *cord, char movimiento);


#endif // COORDENADAS_H_INCLUDED
