#include "Portal.h"

void portalInicializar(tPortal *portal, const tCoordenadas *entrada, const tCoordenadas *salida)
{
    portal->entrada = *entrada;
    portal->salida = *salida;
    portal->simbolo = CARACTER_PORTAL;
}

int hayObjetoSobrePortal(const tPortal *portal, const tCoordenadas *obj)
{
    return ((portal->entrada.x == obj->x && portal->entrada.y == obj->y) || (portal->salida.x == obj->x && portal->salida.y == obj->y));
}

void portalTeletransportar(const tPortal *portal, tCoordenadas *obj)
{
    if(portal->entrada.x == obj->x && portal->entrada.y == obj->y)
    {
        obj->x = portal->salida.x;
        obj->y = portal->salida.y - 1;
    }else
    {
        obj->x = portal->entrada.x;
        obj->y = portal->entrada.y + 1;
    }
}

tCoordenadas* portalPunteroPuntoA(tPortal *p)
{
    return &(p->entrada);
}

tCoordenadas* portalPunteroPuntoB(tPortal *p)
{
    return &(p->salida);
}
