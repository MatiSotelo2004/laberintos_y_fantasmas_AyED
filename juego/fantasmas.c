#include "fantasmas.h"
#include <stdlib.h>
int crearFantasmas(tFantasmas *fantasmas, int cantFantasmas)
{
    if(cantFantasmas > 0)
    {
        fantasmas->fantasma = (tCoordenadas*)malloc(sizeof(tCoordenadas) * cantFantasmas);
        if(!fantasmas->fantasma)
        {
            return FANTASMAS_SIN_MEMORIA;
        }
    }else
        fantasmas->fantasma = NULL;
    return FANTASMAS_OK;
}

void destruirFantasmas(tFantasmas *fantasmas)
{
    if(fantasmas->fantasma)
        free(fantasmas->fantasma);
}

tCoordenadas posicionAleatoriaObtener(const tCoordenadas *limite)
{
    tCoordenadas coords;
    OBTENER_NUM_ALEATORIO(0, limite->y, coords.y);
    OBTENER_NUM_ALEATORIO(0, limite->x, coords.x);
    return coords;
}

tCoordenadas* obtenerPunteroFantasmas(const tFantasmas *fantasmas)
{
    return fantasmas->fantasma;
}
tCoordenadas obtenerCoordenadasFantasmas(const tFantasmas *fantasmas, int nroFantasma)
{
    return *((fantasmas->fantasma)+nroFantasma);
}

tCoordenadas* obtenerPunteroNroFantasmas(const tFantasmas *fantasmas,int nroFantasma)
{
    return ((fantasmas->fantasma)+nroFantasma);
}

