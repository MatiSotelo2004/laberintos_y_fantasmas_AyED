#ifndef PORTAL_H_INCLUDED
#define PORTAL_H_INCLUDED

#include "../coordenadas.h"

#define PORTAL_CREADO_EXITOSO 0
#define CARACTER_PORTAL 'O'

typedef struct
{
   tCoordenadas entrada;
   tCoordenadas salida;
   char simbolo;
}tPortal;

void portalInicializar(tPortal *portal, const tCoordenadas *entrada, const tCoordenadas *salida);
void portalTeletransportar(const tPortal *portal, tCoordenadas *obj);

#endif // PORTAL_H_INCLUDED
