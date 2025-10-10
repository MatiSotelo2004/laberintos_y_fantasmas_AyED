#include "objetos.h"
#include "coordenadas.h"

int objetosCrear(tPosObjeto *objetos, const tConfigTablero *config, const tCoordenadas *jugadorInicio)
{
    if(config->cantParedes > 0)
    {
        objetos->paredes = (tCoordenadas *)malloc(config->cantParedes * sizeof(tCoordenadas));
        if(!objetos->paredes)
            return TABLERO_SIN_MEM;
    }else
        objetos->paredes = NULL;

    if(config->cantPremio > 0)
    {
        objetos->premio = (tCoordenadas *)malloc(config->cantPremio * sizeof(tCoordenadas));
        if(!objetos->premio)
        {
            if(config->cantParedes > 0)
                free(objetos->paredes);

            return TABLERO_SIN_MEM;
        }
    }else
        objetos->premio = NULL;

    if(config->cantVidaExtra > 0)
    {
        objetos->vidas = (tCoordenadas *)malloc(config->cantVidaExtra * sizeof(tCoordenadas));
        if(!objetos->vidas)
        {
            if(config->cantParedes > 0)
                free(objetos->paredes);
            if(config->cantPremio > 0)
                free(objetos->premio);

            return TABLERO_SIN_MEM;
        }
    }else
        objetos->vidas = NULL;

    if(config->cantFant > 0)
    {
        objetos->fantasma = (tCoordenadas*)malloc(sizeof(tCoordenadas) * config->cantFant);
        if(!objetos->fantasma)
        {
            if(config->cantParedes > 0)
                free(objetos->paredes);
            if(config->cantPremio > 0)
                free(objetos->premio);
            if(config->cantVidaExtra > 0)
                free(objetos->vidas);

            return TABLERO_SIN_MEM;
        }

    }else
        objetos->fantasma = NULL;

    return TODO_OK;
}

void objetosDestruir(tPosObjeto *objetos)
{
    if(objetos->premio)
        free(objetos->premio);
    if(objetos->paredes)
        free(objetos->paredes);
    if(objetos->vidas)
        free(objetos->vidas);
    if(objetos->fantasma)
        free(objetos->fantasma);
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

tCoordenadas* objetoFantasmasObtenerPunteroCoordenadas(const tPosObjeto *objeto,unsigned pos)
{
    return (objeto->fantasma)+pos;
}

tCoordenadas objetoFantasmasObtenerCoordenadas(const tPosObjeto *objeto, unsigned pos)
{
    return *((objeto->fantasma)+pos);
}
