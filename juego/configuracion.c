#include "configuracion.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cargarConfiguracion(tConfiguracion *config, const char *nomArch)
{
    char buffer[TAM_BUFFER];
    char *aux;
    unsigned iterador = 0;
    int numAux;
    FILE *fp = fopen(nomArch, "rt");
    if(!fp)
        return CONFIGURACION_ERROR;

    /*
     Un ejemplo del archivo de texto que describe laberinto con los siguientes valores en los
    parametros iniciales:
    � filas: 10
    � columnas: 10
    � vidas_inicio: 3.
    � maximo_numero_fantasmas: 2
    � maximo_numero_premios: 1
    � maximo_vidas_extra: 1
    */

    while(fgets(buffer,TAM_BUFFER,fp))
    {
        aux = strrchr(buffer, '\n');
        *aux = '\0';

        while(!ES_NUMERO(*aux))
            aux--;

        while(ES_NUMERO(*(aux-1)))
            aux--;

        numAux = atoi(aux);

        switch(iterador)
        {
            case PARAMETRO_FILA_UBICACION:
                config->tamTablero.x = numAux;
                break;
            case PARAMETRO_COLUMNA_UBICACION:
                config->tamTablero.y = numAux;
                break;
            case PARAMETRO_VIDAS_INICIO_UBICACION:
                config->cantVidasInicial = numAux;
                break;
            case PARAMETRO_CANT_FANTASMAS_UBICACION:
                config->cantFantasmas = numAux;
                break;
            case PARAMETRO_CANT_PREMIOS_UBICACION:
                config->cantPremios = numAux;
                break;
            case PARAMETRO_CANT_VIDAS_EXTRA_UBICACION:
                config->cantVidasExtra = numAux;
                break;
        }

        iterador++;
    }

    fclose(fp);
    return  CONFIGURACION_OK;

}


unsigned obtenerCantVidasExtra(const tConfiguracion* config){
    return config->cantVidasExtra;
}
unsigned obtenerCantPremos(const tConfiguracion* config){
    return config->cantPremios;
}
unsigned obtenerCantFantasmas(const tConfiguracion* config){
    return config->cantFantasmas;
}
unsigned obtenerCantVidasInicial(const tConfiguracion* config){
    return config->cantVidasInicial;
}
tCoordenadas obtenerTamTablero(const tConfiguracion* config){
    return config->tamTablero;
}
