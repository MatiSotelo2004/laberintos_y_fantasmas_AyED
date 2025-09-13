#ifndef CONFIGURACIONTABLERO_H_INCLUDED
#define CONFIGURACIONTABLERO_H_INCLUDED
#include "macros.h"
#include "coordenadas.h"
#include <stdio.h>
#include <string.h>

typedef struct
{
    /*
     � filas: n�mero de filas del tablero
    � columnas: n�mero de columnas del tablero
    � vidas_inicio: n�mero de vidas.
    � maximo_numero_fantasmas: n�mero de fantasmas
    � maximo_numero_premios: n�mero de premios
    � maximo_vidas_extra: n�mero de vidas maximo_vidas_extra
    */
    tCoordenadas tamTablero;
    unsigned cantVidaInicial;
    unsigned cantFant;
    unsigned cantPremio;
    unsigned cantVidaExtra;
    unsigned cantParedes; // no cuenta las paredes en los bordes del tablero
}tConfigTablero;

int configuracionTableroCargar(tConfigTablero *config, const char *nomArch);
int configuracionTableroObtenerCantidadVidasExtra(const tConfigTablero *config);
int configuracionTableroObtenerCantidadPremios(const tConfigTablero *config);
int configuracionTableroObtenerCantidadParedes(const tConfigTablero *config);
int configuracionTableroObtenerCantidadFantasmas(const tConfigTablero *config);
int configuracionTableroObtenerCantidadVidasInicial(const tConfigTablero *config);

#endif // CONFIGURACIONTABLERO_H_INCLUDED
