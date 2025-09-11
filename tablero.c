#include "tablero.h"
#include "coordenadas.h"
#include <stdlib.h>

tCoordenadas tableroEstablecerEntrada(tTablero *tablero)
{
    int posColumna;
    OBTENER_NUM_ALEATORIO(1, tablero->limite.x - 1,posColumna);
    tablero->tablero[0][posColumna] = CARACTER_ENTRADA;
    tCoordenadas coordenada;
    coordenada.x = 0;
    coordenada.y = posColumna;
    return coordenada;
}

tCoordenadas tableroEstablecerSalida(tTablero *tablero)
{
    int posColumna;
    OBTENER_NUM_ALEATORIO(1, tablero->limite.x - 1,posColumna);
    tablero->tablero[tablero->limite.x-1][posColumna] = CARACTER_SALIDA;
    tCoordenadas coordenada;
    coordenada.x = tablero->limite.x-1;
    coordenada.y = posColumna;
    return coordenada;
}

int tableroCrear(tTablero *tablero, const tConfigTablero *config)
{
    char **i;
    char **j;
    char **fin;
    tablero->tablero = (char**)malloc(config->tamTablero.x * sizeof(char*));
    if(!tablero->tablero)
        return TABLERO_SIN_MEM;

    fin = tablero->tablero + config->tamTablero.x;
    for(i = tablero->tablero; i < fin; i++)
    {
        *i = (char*)malloc(config->tamTablero.y * sizeof(char));
        if(!*i)
        {
            for(j = i - 1; j >= tablero->tablero; j--)
                free(*j);

            free(tablero->tablero);
            return TABLERO_SIN_MEM;
        }
    }
    tablero->limite.x = config->tamTablero.x;
    tablero->limite.y = config->tamTablero.y;

    return TODO_OK;
}

void tableroDestruir(tTablero *tablero)
{
    char **i;
    char **fin = tablero->tablero + tablero->limite.x;
    for(i = tablero->tablero; i < fin; i++)
        free(*i);

    free(tablero->tablero);
}

void tableroDibujarParedes(tTablero *tablero)
{
    int i, num_paredes, fila_random, col_random;

    //DIBUJA LOS LIMITES
    for(i = 0; i < tablero->limite.x; i++)
    {
        tablero->tablero[i][0] = CARACTER_PARED;
        tablero->tablero[i][tablero->limite.y - 1] = CARACTER_PARED;
    }
    for(i = 0; i < tablero->limite.y; i++)
    {
        tablero->tablero[0][i] = CARACTER_PARED;
        tablero->tablero[tablero->limite.x-1][i] = CARACTER_PARED;
    }

    //DIBUJA LOS CAMINOS
    for (i=1; i < tablero->limite.x-1; i++){
        for(int j=1; j<tablero->limite.y-1;j++){
            tablero->tablero[i][j] = LUGAR_VACIO;
        }
    }

    //DIBUJA LAS PAREDES INTERNAS
    num_paredes = (tablero->limite.x * tablero->limite.y) / 8; //CALCULA UN % DE PAREDES QUE VA A TENER

    for (int p = 0; p < num_paredes; p++) {
        int fila_random, col_random;
        i = 0;

        do {
            fila_random = 1 + rand() % (tablero->limite.x - 2);
            col_random = 1 + rand() % (tablero->limite.y - 2);
            i++;
        } while ((tablero->tablero[fila_random][col_random] != LUGAR_VACIO ||
                 // Evitar bloquear la entrada y salida
                 (fila_random == 1 && col_random == 1) ||
                 (fila_random == tablero->limite.x-2 && col_random == tablero->limite.y-2)) &&
                 i < 100);

        if (i < 100) {
            tablero->tablero[fila_random][col_random] = CARACTER_PARED;
        }
    }

}

void tableroInicializar(tTablero *tablero, char caracter)
{
    int i,j;
    for(i = 1; i < tablero->limite.x - 1; i++)
    {
        for(j = 1 ; j < tablero->limite.y - 1; j++)
            tablero->tablero[i][j] = caracter;
    }
}

void tableroImprimir(const tTablero *tablero, FILE* fp, Accion mostrar)
{
    int i,j;
    for(i = 0; i < tablero->limite.x; i++)
    {
        for(j = 0; j < tablero->limite.y; j++)
            mostrar(fp,&tablero->tablero[i][j]);

        puts("");
    }
}

void tableroColocarObjetosAleatorio(tTablero *tablero, tCoordenadas *coords, unsigned cantObj, char caracter)
{
    int i;
    tCoordenadas coordsAleatorias;
    for(i = 0; i < cantObj; i++)
    {
        OBTENER_NUM_ALEATORIO(1,tablero->limite.y-1, coordsAleatorias.y);
        OBTENER_NUM_ALEATORIO(1,tablero->limite.x-1, coordsAleatorias.x);
        while(!POSICION_ESTA_DISPONIBLE(tablero->tablero,coordsAleatorias.x,coordsAleatorias.y))
        {
            OBTENER_NUM_ALEATORIO(1,tablero->limite.y-1, coordsAleatorias.y);
            OBTENER_NUM_ALEATORIO(1,tablero->limite.x-1, coordsAleatorias.x);
        }

        tablero->tablero[coordsAleatorias.x][coordsAleatorias.y] = caracter;
        (coords + i)->x = coordsAleatorias.x;
        (coords + i)->y = coordsAleatorias.y;
    }
}

int tableroPosicionEstaDisponible(const tTablero *tablero, const tCoordenadas *coords)
{
    if(tablero->tablero[coords->x][coords->y] == LUGAR_VACIO)
        return 1;
    return 0;
}

void tableroVerObjeto(const tTablero *tablero, const tCoordenadas *coords, char *dest)
{
    if(coords->x < tablero->limite.x && coords->y < tablero->limite.y)
        *dest = tablero->tablero[coords->x][coords->y];

    dest = NULL;
}

int tableroColocarObjeto(tTablero *tablero, const tCoordenadas *obj, char caracter)
{
    if(obj->x > tablero->limite.x || obj->y > tablero->limite.y)
        return POSICION_NO_DISPONIBLE;

    if(tablero->tablero[obj->x][obj->y] == CARACTER_PARED)
        return POSICION_NO_DISPONIBLE;

    tablero->tablero[obj->x][obj->y] = caracter;
    return TODO_OK;
}
