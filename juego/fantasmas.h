#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include "../coordenadas.h"

#define FANTASMAS_SIN_MEMORIA -3
#define FANTASMAS_OK 0

#define OBTENER_NUM_ALEATORIO(MIN,MAX,DST) \
    ((DST) = (rand() % ((MAX) - (MIN))) + (MIN))

typedef struct
{
    tCoordenadas *fantasma;
}tFantasmas;

int crearFantasmas(tFantasmas *fantasmas,int cantFantasmas);
void destruirFantasmas(tFantasmas *fantasmas);
tCoordenadas posicionAleatoriaObtener(const tCoordenadas *limite);

tCoordenadas* obtenerPunteroFantasmas(const tFantasmas *fantasmas);
tCoordenadas obtenerCoordenadasFantasmas(const tFantasmas *fantasmas, int nroFantasma);
tCoordenadas* obtenerPunteroNroFantasmas(const tFantasmas *fantasmas,int nroFantasma);

#endif // OBJETOS_H_INCLUDED
