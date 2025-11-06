#ifndef CONFIGURACION_H_INCLUDED
#define CONFIGURACION_H_INCLUDED

#include "../coordenadas.h"


#define CONFIGURACION_ERROR 5
#define CONFIGURACION_OK 0
#define TAM_BUFFER 1024
#define PARAMETRO_FILA_UBICACION 0
#define PARAMETRO_COLUMNA_UBICACION 1
#define PARAMETRO_VIDAS_INICIO_UBICACION 2
#define PARAMETRO_CANT_FANTASMAS_UBICACION 3
#define PARAMETRO_CANT_PREMIOS_UBICACION 4
#define PARAMETRO_CANT_VIDAS_EXTRA_UBICACION 5
#define ES_NUMERO(X) ((X) >= '0' && (X) <= '9')

typedef struct
{
    tCoordenadas tamTablero;
    unsigned cantVidasInicial;
    unsigned cantFantasmas;
    unsigned cantPremios;
    unsigned cantVidasExtra;
}tConfiguracion;

int cargarConfiguracion(tConfiguracion *config, const char *nomArch);

unsigned obtenerCantVidasInicial(const tConfiguracion* config);
unsigned obtenerCantVidasExtra(const tConfiguracion* config);
unsigned obtenerCantPremos(const tConfiguracion* config);
unsigned obtenerCantFantasmas(const tConfiguracion* config);
tCoordenadas obtenerTamTablero(const tConfiguracion* config);

#endif // CONFIGURACION_H_INCLUDED
