#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED
#include "coordenadas.h"
#include "configuracionTablero.h"
#include "macros.h"

typedef struct
{
    tCoordenadas jugador;
    tCoordenadas entrada;
    tCoordenadas *premio;
    tCoordenadas *paredes;
    tCoordenadas *vidas;
}tPosObjeto;

int objetosCrear(tPosObjeto *objetos, const tConfigTablero *config, const tCoordenadas *jugadorInicio);
void objetosDestruir(tPosObjeto *objetos);
tCoordenadas posicionAleatoriaObtener(const tCoordenadas *limite);
tCoordenadas* objetoParedesObtenerPunteroCoordenadas(const tPosObjeto *objeto);
tCoordenadas* objetoPremioObtenerPunteroCoordenadas(const tPosObjeto *objeto);
tCoordenadas* objetoVidasObtenerPunteroCoordenadas(const tPosObjeto *objeto);

#endif // OBJETOS_H_INCLUDED
