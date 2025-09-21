#ifndef GENERARLABERINTO_H_INCLUDED
#define GENERARLABERINTO_H_INCLUDED

#include "Headers.h"

#define FILASTOT 15
#define COLTOT 15
#define CANTCAM 4

#define PARED '#'
#define CAMINO '.'
#define ENTRADA 'e'
#define SALIDA 's'

void mostrarLab(tLaberinto*);
void crearLab(tLaberinto*);
void llenarLabParedes(tLaberinto*);
void cantidadVecinos(tLaberinto*);
void generarLab(tLaberinto*);
void caminosRandom(tLaberinto*);
#endif // GENERARLABERINTO_H_INCLUDED
