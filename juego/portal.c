#include "portal.h"

void portalInicializar(tPortal *portal, const tCoordenadas *entrada, const tCoordenadas *salida)
{
    portal->entrada = *entrada;
    portal->salida = *salida;
    portal->simbolo = CARACTER_PORTAL;
}

void portalTeletransportar(const tPortal *portal, tCoordenadas *jugador)
{
    if(portal->entrada.x == jugador->x && portal->entrada.y == jugador->y)
    {
        jugador->y = portal->salida.y;
        jugador->x = portal->salida.x - 1;
    }else
    {
        jugador->y = portal->entrada.y;
        jugador->x = portal->entrada.x + 1;
    }
}
