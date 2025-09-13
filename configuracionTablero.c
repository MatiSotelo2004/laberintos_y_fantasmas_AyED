#include "configuracionTablero.h"

int configuracionTableroCargar(tConfigTablero *config, const char *nomArch)
{
    char buffer[TAM_BUFFER];
    char *aux;
    unsigned iterador = 0;
    int numAux;
    FILE *fp = fopen(nomArch, "rt");
    if(!fp)
        return ARCHIVO_ERROR;

    /*
     Un ejemplo del archivo de texto que describe laberinto con los siguientes valores en los
    par�metros iniciales:
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

        /*
        #define PARAMETRO_FILA_UBICACION 0
        #define PARAMETRO_COLUMNA_UBICACION 1
        #define PARAMETRO_VIDAS_INICIO_UBICACION 2
        #define PARAMETRO_CANT_FANTASMAS_UBICACION 3
        #define PARAMETRO_CANT_PREMIOS_UBICACION 4
        #define PARAMETRO_CANT_VIDAS_EXTRA_UBICACION 5
        */
        if(iterador == PARAMETRO_FILA_UBICACION)
        {
            config->tamTablero.x = numAux;
        }
        if(iterador == PARAMETRO_COLUMNA_UBICACION)
        {
            config->tamTablero.y = numAux;
        }
        if(iterador == PARAMETRO_VIDAS_INICIO_UBICACION)
        {
            config->cantVidaInicial = numAux;
        }
        if(iterador == PARAMETRO_CANT_FANTASMAS_UBICACION)
        {
            config->cantFant = numAux;
        }
        if(iterador == PARAMETRO_CANT_PREMIOS_UBICACION)
        {
            config->cantPremio = numAux;
        }
        if(iterador == PARAMETRO_CANT_VIDAS_EXTRA_UBICACION)
        {
            config->cantVidaExtra = numAux;
        }
        iterador++;
    }

    OBTENER_NUM_ALEATORIO(0, MAX_CANT_PAREDES, config->cantParedes);
    fclose(fp);
    return  TODO_OK;

}

int configuracionTableroObtenerCantidadParedes(const tConfigTablero *config)
{
   return config->cantParedes;
}

int configuracionTableroObtenerCantidadPremios(const tConfigTablero *config)
{
   return config->cantPremio;
}

int configuracionTableroObtenerCantidadVidasInicial(const tConfigTablero *config)
{
   return config->cantVidaInicial;
}

int configuracionTableroObtenerCantidadVidasExtra(const tConfigTablero *config)
{
   return config->cantVidaExtra;
}

int configuracionTableroObtenerCantidadFantasmas(const tConfigTablero *config)
{
   return config->cantFant;
}
