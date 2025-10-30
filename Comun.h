#ifndef COMUN_H_INCLUDED
#define COMUN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "configuracionTablero.h"
#include "jugador.h"
#include "macros.h"
#include "cliente_LyF.h"
#include "menu.h"

void pedirString(const char *mensaje, char *dest,unsigned tamMax);
void copiarNombreArchivo(void *a, void *b);
void seterHistorialJugador(void *a, void *b);
void convertirJugadorAJugadorDat(const tJugador *jug, tJugadorDat *jugDat);
#endif // COMUN_H_INCLUDED
