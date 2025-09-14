#ifndef GENERARLABERINTO_H_INCLUDED
#define GENERARLABERINTO_H_INCLUDED

#include "Headers.h"

#define FILASTOT 21
#define COLTOT 21

#define PARED '#'
#define CAMINO '.'
#define ENTRADA 'e'
#define SALIDA 's'

void mostrarLab(tLaberinto*);
void crearLab(tLaberinto*);
void llenarLabParedes(tLaberinto*);
void cantidadVecinos(tLaberinto*);
void generarLab(tLaberinto*);

#endif // GENERARLABERINTO_H_INCLUDED
