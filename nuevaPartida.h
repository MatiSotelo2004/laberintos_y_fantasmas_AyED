#ifndef NUEVAPARTIDA_H_INCLUDED
#define NUEVAPARTIDA_H_INCLUDED
#include "tablero.h"
#include "jugador.h"
#include "colaDinamica.h"
#include "coordenadas.h"
#include "configuracionTablero.h"
#include "objetos.h"
#include "Portal.h"

int nuevaPartida(tConfigTablero *configTablero, tJugador *jugador,const char *nomJugador);
void mostrarChar();
tCoordenadas fantasmaObtenerSiguienteMovimiento(const tTablero *tablero, const tCoordenadas *posFantasma, const tCoordenadas *posJugador);
int crearPortalEnTablero(tPortal *portal, tTablero *tablero);
void actualizarMovimientosTableroDesdeCola(tCola *colaMovimientos, tTablero *tablero, tJugador *jugador, tPosObjeto *objetos, const tPortal *portal);

#endif // NUEVAPARTIDA_H_INCLUDED
