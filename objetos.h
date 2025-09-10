#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED
#include "coordenadas.h"
#include "configuracionTablero.h"
#include "macros.h"

typedef struct
{
    tCoordenadas entrada;
    tCoordenadas *premio;
    tCoordenadas *paredes;
    tCoordenadas *vidas;
    tCoordenadas *fantasma;
}tPosObjeto;

int objetosCrear(tPosObjeto *objetos, const tConfigTablero *config, const tCoordenadas *jugadorInicio);
void objetosDestruir(tPosObjeto *objetos);
tCoordenadas posicionAleatoriaObtener(const tCoordenadas *limite);
tCoordenadas* objetoParedesObtenerPunteroCoordenadas(const tPosObjeto *objeto);
tCoordenadas* objetoPremioObtenerPunteroCoordenadas(const tPosObjeto *objeto);
tCoordenadas* objetoVidasObtenerPunteroCoordenadas(const tPosObjeto *objeto);
tCoordenadas* objetoFantasmasObtenerPunteroCoordenadas(const tPosObjeto *objeto);
tCoordenadas objetoFantasmasObtenerCoordenadas(const tPosObjeto *objeto, unsigned pos);

#endif // OBJETOS_H_INCLUDED
