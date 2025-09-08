#include "objetos.h"
#include "coordenadas.h"

int objetosCrear(tPosObjeto *objetos, const tConfigTablero *config, const tCoordenadas *jugadorInicio)
{
    if(config->cantParedes > 0)
    {
        objetos->paredes = (tCoordenadas *)malloc(config->cantParedes * sizeof(tCoordenadas));
        if(!objetos->paredes)
            return TABLERO_SIN_MEM;
    }

    if(config->cantPremio > 0)
    {
        objetos->premio = (tCoordenadas *)malloc(config->cantPremio * sizeof(tCoordenadas));
        if(!objetos->premio)
            return TABLERO_SIN_MEM;
    }

    if(config->cantVidaExtra > 0)
    {
        objetos->vidas = (tCoordenadas *)malloc(config->cantVidaExtra * sizeof(tCoordenadas));
        if(!objetos->vidas)
            return TABLERO_SIN_MEM;
    }

    objetos->jugador.x = jugadorInicio->x;
    objetos->jugador.y = jugadorInicio->y;

    return TODO_OK;
}

void objetosDestruir(tPosObjeto *objetos)
{
    free(objetos->premio);
    free(objetos->paredes);
    free(objetos->vidas);
}

tCoordenadas posicionAleatoriaObtener(const tCoordenadas *limite)
{
    tCoordenadas coords;
    OBTENER_NUM_ALEATORIO(0, limite->y, coords.y);
    OBTENER_NUM_ALEATORIO(0, limite->x, coords.x);
    return coords;
}

tCoordenadas* objetoParedesObtenerPunteroCoordenadas(const tPosObjeto *objeto)
{
    return objeto->paredes;
}

tCoordenadas* objetoPremioObtenerPunteroCoordenadas(const tPosObjeto *objeto)
{
    return objeto->premio;
}

tCoordenadas* objetoVidasObtenerPunteroCoordenadas(const tPosObjeto *objeto)
{
    return objeto->vidas;
}
