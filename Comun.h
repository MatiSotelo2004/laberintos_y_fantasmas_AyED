#ifndef COMUN_H_INCLUDED
#define COMUN_H_INCLUDED
#include "coordenadas.h"
#include "configuracionTablero.h"
#include "jugador.h"
#include "objetos.h"
#include "tablero.h"
#include "macros.h"
#include "colaDinamica.h"
#include "HistorialPartidas.h"
#include "menu.h"
int esMovimientoValido(const tTablero *tablero, const tCoordenadas *posActual, char movimiento);
tCoordenadas fantasmaObtenerSiguienteMovimiento(const tTablero *tablero, const tCoordenadas *posActual, const tCoordenadas *posJugador);
void actualizarMovimientosTableroDesdeCola(tCola *colaMovimientos, tTablero *tablero, tJugador *jugador, tPosObjeto *objetos);
void pedirString(const char *mensaje, char *dest,unsigned tamMax);
void copiarNombreArchivo(void *a, void *b);
void seterHistorialJugador(void *a, void *b);
#endif // COMUN_H_INCLUDED
