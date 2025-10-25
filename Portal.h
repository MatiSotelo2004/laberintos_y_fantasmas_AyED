#ifndef PORTAL_H_INCLUDED
#define PORTAL_H_INCLUDED

#include "coordenadas.h"
#define PORTAL_CREADO_EXITOSO 0

typedef struct
{
   tCoordenadas entrada;
   tCoordenadas salida;
   char simbolo;
}tPortal;

void portalInicializar(tPortal *portal, const tCoordenadas *entrada, const tCoordenadas *salida);
int hayObjetoSobrePortal(const tPortal *portal, const tCoordenadas *obj);
void portalTeletransportar(const tPortal *portal, tCoordenadas *obj);
tCoordenadas* portalPunteroPuntoA(tPortal *p);
tCoordenadas* portalPunteroPuntoB(tPortal *p);

#endif // PORTAL_H_INCLUDED
